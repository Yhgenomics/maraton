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
#include <list>
#include <mutex>


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

    virtual void run() = 0;

    virtual void close();

    int id() { return this->id_; };

protected:

    virtual void on_recv( const char* data, int len ) = 0;
    virtual void send( const char* data, int len );
    virtual void shutdown() {};
    
    static int create_session_id(); 

    char* recv_buffer_ = nullptr;
    
    uv_tcp_t * conn_ = nullptr;
    uv_loop_t* loop_ = nullptr;

    std::mutex mtx;
    std::list<Buffer*> send_data_buffer_;

private:

    friend Core::UVSockService; 

    int id_;
};

#endif //SESSION_H_ 