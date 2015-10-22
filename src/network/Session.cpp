#include "Session.h"
#include "maraton.h"
#include "uv.h"
#include <memory.h>
#include <thread>
#include <atomic>
#include <mutex>
#include "UVSockService.h"

Session::Session( uv_tcp_t * conn )
{
    recv_buffer_ = new char[this->buffer_len()];
    send_buffer_ = new char[this->buffer_len()];

    send_req_ = new uv_write_t();
    memset( send_req_, 0, sizeof( uv_write_t ) );
    this->conn_ = conn;

    this->id_ = Session::create_session_id();
}

Session::~Session()
{
    SAFE_DELETE( this->recv_buffer_ );
    SAFE_DELETE( this->send_buffer_ );
    SAFE_DELETE( this->conn_ );
    SAFE_DELETE( this->send_req_ );
}
 
void Session::on_recv( const char * data, int len )
{ 

}

void Session::send( const char * data, int len )
{
    uv_buf_t buf;
    int result; 

    buf.base = this->send_buffer_;
    memcpy( this->send_buffer_, data, len );
    buf.len = len;

    while ( 1 ) 
    {
        result = uv_write( send_req_, ( uv_stream_t* )this->conn_, &buf, 1 , Core::UVSockService::uv_write_cb_process );
        if ( result == 0 )
        {
            break;
        }
    }

    //SAFE_DELETE( buf.base );
}

void Session::close()
{
    uv_close( (uv_handle_t*)this->conn_, Core::UVSockService::uv_close_cb_process );
}

int Session::create_session_id()
{
    static int session_id = 10000;
    static std::mutex m_lock;

    m_lock.lock();
    session_id++;
    m_lock.unlock();

    return session_id;
}
