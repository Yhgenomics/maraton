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
    this->conn = conn;

    this->id_ = Session::create_session_id();
}

Session::~Session()
{
    SAFE_DELETE( this->recv_buffer_ );
    SAFE_DELETE( this->send_buffer_ );
    SAFE_DELETE( this->conn );
    SAFE_DELETE( this->send_req_ );
}
 
void Session::on_recv( const char * data, int len )
{ 

}

void Session::send( char * data, int len )
{
    uv_buf_t buf;
    int result; 

    buf.base = data;
    buf.len = len;

    while ( 1 ) 
    {
        result = uv_write( send_req_, ( uv_stream_t* )this->conn, &buf, 1 , NULL );
        if ( result == 0 )
        {
            break;
        }
    }
}

void Session::close()
{
    uv_close( (uv_handle_t*)this->conn , Core::UVSockService::uv_close_cb_process );
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
