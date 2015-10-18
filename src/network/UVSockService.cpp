#include "UVSockService.h"
#include "SessionFactory.h"
#include "SessionManager.h"

Core::UVSockService::UVSockService()
{
    this->loop_ = nullptr;
    this->socket_ = nullptr;
}

Core::UVSockService::~UVSockService()
{
    SAFE_DELETE( this->socket_ );
    SAFE_DELETE( this->loop_ );
}

bool Core::UVSockService::listen( std::string ip, int port )
{
    this->loop_ = uv_default_loop(); 
    this->socket_ = new uv_tcp_t();

    uv_tcp_init( this->loop_, this->socket_ );
    uv_ip4_addr( ip.c_str(), port, &addr_in );

    uv_tcp_bind( this->socket_, ( const struct sockaddr* )&addr_in, 0 );
    int r = uv_listen( ( uv_stream_t* )this->socket_, 10000, Core::UVSockService::uv_connection_cb_process );

    this->socket_->data = this;

    if ( r ) {
        Logger::error( "Can't create port %d", port );
        return false;
    }

    Logger::sys( "Create port %d successed", port );

    return true;
}

bool Core::UVSockService::connect( std::string ip, int port )
{
    this->socket_ = new uv_tcp_t();
    uv_tcp_init( this->loop_, this->socket_ );

    uv_connect_t* connect = ( uv_connect_t* ) malloc( sizeof( uv_connect_t ) );

    uv_ip4_addr( ip.c_str(), port, &addr_in );

    this->socket_->data = this;

    uv_tcp_connect( connect, this->socket_, ( const struct sockaddr* )&addr_in, Core::UVSockService::uv_connected_cb_process );

    return true;
}

void Core::UVSockService::run()
{
    uv_run( this->loop_, UV_RUN_NOWAIT );
}

void Core::UVSockService::session_type( SESSIONTYPE type )
{
    this->session_type_ = type;
}

SESSIONTYPE Core::UVSockService::session_type()
{
    return this->session_type_;
}

void Core::UVSockService::uv_connection_cb_process( uv_stream_t * server, int status )
{

    if ( status < 0 ) {
        return;
    }

    Core::UVSockService * srv = static_cast< Core::UVSockService* >( server->data );

    uv_tcp_t *client = new uv_tcp_t();
    uv_tcp_init( ( uv_loop_t* ) srv->loop(), client );

    Session* session = SessionFactory::instance()->create( client, srv->session_type() );

    SessionManager::instance()->push( session );

    client->data = static_cast< void* >( session );

    if ( uv_accept( server, ( uv_stream_t* ) client ) == 0 ) 
    {
        uv_read_start( ( uv_stream_t* ) client, Core::UVSockService::uv_alloc_cb_process, Core::UVSockService::uv_read_cb_process );
    }
    else 
    {
        uv_close( ( uv_handle_t* ) client, NULL );
    }

}

void Core::UVSockService::uv_connected_cb_process( uv_connect_t * req, int status )
{
    if ( status < 0 )
    {
        Logger::error( "Can't connect to server error:%d", status );
        return;
    }
}

void Core::UVSockService::uv_alloc_cb_process( uv_handle_t * handle, size_t suggested_size, uv_buf_t * buf )
{
    Session* session = static_cast< Session* >( handle->data );

    buf->base = session->recv_buffer();
    buf->len = session->buffer_len();
}

void Core::UVSockService::uv_read_cb_process( uv_stream_t * stream, ssize_t nread, const uv_buf_t * buf )
{
    Session* session = static_cast< Session* >( stream->data );

    if ( nread < 0 )
    {
        return;
    }

    session->on_recv( static_cast< int >( nread ) );
}

void Core::UVSockService::uv_close_cb_process( uv_handle_t * handle )
{
    Session* session = static_cast< Session* >( handle->data );

    SessionManager::instance()->remove( session );
}

