/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef SESSION_H_
#define SESSION_H_ 

#include "maraton.h"
#include "Macros.h"
#include "uv.h"

enum SESSIONTYPE
{
    MASTER = 0,
    RESTAPI = 80,
    EXECUTOR = 90
};

namespace Core
{
    class UVSockService;
}

class Session
{
public:

    Session( uv_tcp_t* conn);
    virtual ~Session();
    int buffer_len() { return SESSION_BUFFER_SIZE; }
    char* recv_buffer() { return this->recv_buffer_; }
    char* send_buffer() { return this->recv_buffer_; }

    virtual void on_recv( const char* data, int len );
    virtual void run() = 0;

    virtual void send( const char* data, int len );
    virtual void close();

    int id() { return this->id_; };

protected:

    static int create_session_id(); 

    char* recv_buffer_ = nullptr;
    char* send_buffer_ = nullptr;
    
    uv_write_t* send_req_ = nullptr;
    uv_tcp_t * conn_; 

private:

    friend Core::UVSockService; 

    int id_;
};

#endif //SESSION_H_ 