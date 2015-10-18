#ifndef UV_SOCK_SERVICE_H_
#define UV_SOCK_SERVICE_H_

#include <string>
#include <memory.h>

#include "uv.h"

#include "maraton.h"
#include "MasterSession.h"
#include "Session.h"

static void uv_connection_cb_process( uv_stream_t * server, int status );
static void uv_connected_cb_process( uv_connect_t* req, int status );
static void uv_alloc_cb_process( uv_handle_t * handle, size_t suggested_size, uv_buf_t * buf );
static void uv_read_cb_process( uv_stream_t * stream, ssize_t nread, const uv_buf_t * buf );

namespace Core
{
    class UVSockService  
    {
    public:
        UVSockService();
        ~UVSockService();

        UVSockService( UVSockService& ) = delete;
        UVSockService( UVSockService&& ) = delete;
        UVSockService operator = ( UVSockService ) = delete;

        bool listen( std::string ip, int port );
        bool connect( std::string ip, int port );
        void run();

        uv_loop_t* loop() { return this->loop_; };

        void session_type( SESSIONTYPE type );
        SESSIONTYPE session_type();

    protected:

        friend Session;
        static void uv_connection_cb_process( uv_stream_t * server, int status );
        static void uv_connected_cb_process( uv_connect_t* req, int status );
        static void uv_alloc_cb_process( uv_handle_t * handle, size_t suggested_size, uv_buf_t * buf );
        static void uv_read_cb_process( uv_stream_t * stream, ssize_t nread, const uv_buf_t * buf );
        static void uv_shutdown_cb_process( uv_shutdown_t* req, int status );
        static void uv_close_cb_process( uv_handle_t* handle );

    private:
        
        uv_loop_t* loop_;
        struct sockaddr_in addr_in;
        uv_tcp_t* socket_;
        SESSIONTYPE session_type_;

    };
}

#endif // !UV_SOCK_SERVICE_H_
