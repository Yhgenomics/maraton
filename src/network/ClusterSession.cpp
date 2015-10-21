#include "ClusterSession.h"

ClusterSession::ClusterSession( uv_tcp_t * conn )
    : Session::Session( conn )
{

}

ClusterSession::~ClusterSession()
{
}

void ClusterSession::on_recv( int len )
{
    circle_buffer_.push( this->recv_buffer_, len );

    switch ( this->read_state_ )
    {
    case ES_READSTATE::FLAG:
    {
        if ( this->try_read_flag() )
        {
            this->read_state_ = ES_READSTATE::HEAD;
        }
    }
    break;
    case ES_READSTATE::HEAD:
    {
        if ( this->try_read_head() )
        {
            this->read_state_ = ES_READSTATE::BODY;
        }
    }
    break;
    case ES_READSTATE::BODY:
    {
        if ( this->try_read_body() )
        {
            this->read_state_ = ES_READSTATE::FLAG;
        }
    }
    break;
    default:
    break;
    }

}

void ClusterSession::run()
{
    return;
}

bool ClusterSession::try_read_flag()
{
    auto data = this->circle_buffer_.pop( 2 );

    if ( data == nullptr )
    {
        return false;
    }

    if ( data[0] == 'Y' && data[2] == 'H' )
    {
        SAFE_DELETE( data );
        return true;
    }

    return false;
}

bool ClusterSession::try_read_head()
{

    //0-1 Compressed Length
    //2-3 Oringal Length
    auto data = this->circle_buffer_.pop( 4 );

    if ( data == nullptr )
    {
        return false;
    }

    this->compressed_length_ = *( unsigned short* ) data;
    data += 2;
    this->oringal_length_ = *( unsigned short* ) data;

    SAFE_DELETE( data );

    return true;
}

bool ClusterSession::try_read_body()
{
    auto data = this->circle_buffer_.pop( this->compressed_length_ );

    if ( data == nullptr )
    {
        return false;
    }

    int oringal_size = 0;

    auto raw_data = this->compressor_.uncompress( data, this->compressed_length_ );

    this->on_data_recv( raw_data );

    SAFE_DELETE( data );

    return true;
}
