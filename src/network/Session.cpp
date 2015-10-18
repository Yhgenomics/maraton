#include "Session.h"
#include "maraton.h"
#include "uv.h"
#include <memory.h>

#include "UVSockService.h"

Session::Session( uv_tcp_t * conn )
{
    recv_buffer_ = new char[this->buffer_len()];
    send_buffer_ = new char[this->buffer_len()];
    send_req_ = new uv_write_t();
    memset( send_req_, 0, sizeof( uv_write_t ) );
    this->conn = conn;
}

Session::~Session()
{
    SAFE_DELETE( this->recv_buffer_ );
    SAFE_DELETE( this->send_buffer_ );
    SAFE_DELETE( this->conn );
    SAFE_DELETE( this->send_req_ );
}

void Session::send( const char * data, int len )
{
    uv_buf_t buf;
    int r;

    memcpy( this->send_buffer_, data, len );

    buf.base = this->send_buffer_;
    buf.len = len;

    while ( 1 ) {
        r = uv_write( send_req_, ( uv_stream_t* )this->conn, &buf, 1 , NULL );
        if ( r == 0 )
        {
            break;
        }
    }

}

void Session::close()
{
    uv_close( (uv_handle_t*)this->conn , Core::UVSockService::uv_close_cb_process );
}
