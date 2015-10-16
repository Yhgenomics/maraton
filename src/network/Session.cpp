#include "Session.h"
#include "maraton.h"

 

Session::Session( uv_tcp_t * conn )
{
    recv_buffer_ = new char[this->buffer_len()];
    send_buffer_ = new char[this->buffer_len()];

    this->conn = conn;
}

Session::~Session()
{
    SAFE_DELETE( this->recv_buffer_ );
    SAFE_DELETE( this->send_buffer_ );
}
