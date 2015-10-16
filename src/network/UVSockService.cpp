#include "UVSockService.h"
#include "SessionFactory.h"

Core::UVSockService::UVSockService()
{
    this->loop = nullptr;
    this->socket = nullptr;
}

Core::UVSockService::~UVSockService()
{
    SAFE_DELETE( this->socket );
    SAFE_DELETE( this->loop );
}

bool Core::UVSockService::listen(std::string ip, int port )
{
    this->loop = uv_default_loop(); 
    this->socket = ( uv_tcp_t* ) malloc( sizeof( uv_tcp_t ) );

    uv_tcp_init( loop, this->socket );
    uv_ip4_addr( ip.c_str(), port, &addr_in );

    uv_tcp_bind( this->socket, ( const struct sockaddr* )&addr_in, 0 );
    int r = uv_listen( ( uv_stream_t* )  this->socket, 10000 , uv_connection_cb_process );

    this->socket->data = this->loop;
    
    if ( r ) {
        Logger::error( "Can't create port %d", port );
        return false;
    } 

    Logger::sys( "Create port %d successed", port );

    return true;
}

bool Core::UVSockService::connect( std::string ip, int port )
{
    this->socket = ( uv_tcp_t* ) malloc( sizeof( uv_tcp_t ) );
    uv_tcp_init( loop, socket );

    uv_connect_t* connect = ( uv_connect_t* ) malloc( sizeof( uv_connect_t ) );
 
    uv_ip4_addr( ip.c_str(), port, &addr_in );

    this->socket->data = this->loop;

    uv_tcp_connect( connect, socket, ( const struct sockaddr* )&addr_in, uv_connected_cb_process );


    return true;
}

void Core::UVSockService::run()
{
    uv_run( loop, UV_RUN_DEFAULT );
}
 

void uv_connected_cb_process( uv_connect_t * req, int status )
{
    if ( status < 0 )
    {
        Logger::error( "Can't connect to server error:%d", status );
        return;
    }

    
}


static void uv_connection_cb_process( uv_stream_t * server, int status )
{
    if ( status < 0 ) {
        return;
    }

    uv_tcp_t *client = ( uv_tcp_t* ) malloc( sizeof( uv_tcp_t ) );
    uv_tcp_init( ( uv_loop_t* ) server->data, client );

    Session* master_session = SessionFactory::instance()->create( client , SESSIONTYPE::Master );

    client->data = static_cast< void* >( master_session );
    
    if ( uv_accept( server, ( uv_stream_t* ) client ) == 0 ) {
        uv_read_start( ( uv_stream_t* ) client, uv_alloc_cb_process, uv_read_cb_process );
    }
    else {
        uv_close( ( uv_handle_t* ) client, NULL );
    }
}

static void uv_alloc_cb_process( uv_handle_t * handle, size_t suggested_size, uv_buf_t * buf )
{
    Session* session = static_cast<Session*>(handle->data);
    
    buf->base = session->recv_buffer();
    buf->len = session->buffer_len();
}

static void uv_read_cb_process( uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf )
{
    Session* session = static_cast<Session*>( stream->data );

    if ( nread < 0 )
    {

    }

    session->on_recv( nread );

}