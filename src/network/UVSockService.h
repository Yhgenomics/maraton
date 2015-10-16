#ifndef UV_SOCK_SERVICE_H_
#define UV_SOCK_SERVICE_H_

#include <string>
#include <memory.h>

#include "uv.h"

#include "maraton.h"
#include "MasterSession.h"

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
        uv_loop_t* loop;

    private:
        
        struct sockaddr_in addr_in;
        uv_tcp_t* socket;
    };
}

#endif // !UV_SOCK_SERVICE_H_
