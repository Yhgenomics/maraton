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
    auto socket_ = new uv_tcp_t();

    uv_tcp_init( this->loop_, socket_ );
    uv_ip4_addr( ip.c_str(), port, &addr_in );

    uv_tcp_bind( socket_, ( const struct sockaddr* )&addr_in, 0 );
    int result = uv_listen( ( uv_stream_t* )socket_, 
                       10000, 
                       Core::UVSockService::uv_connection_cb_process );

    listen_data* data = new listen_data();

    data->ip = ip;
    data->port = port;
    data->loop = this->loop_;

    socket_->data = data;

    if ( result > 0 )
    {
        Logger::error( "Can't create port %d", port );
        return false;
    }

    Logger::sys( "Create port %d successed", port );

    return true;
}

bool Core::UVSockService::connect( std::string ip, int port )
{
    this->loop_ = uv_default_loop();
    this->socket_ = new uv_tcp_t();

    uv_tcp_init( this->loop_, this->socket_ ); 

    //mem leak
    uv_connect_t* connect = ( uv_connect_t* ) malloc( sizeof( uv_connect_t ) );

    uv_ip4_addr( ip.c_str(), port, &addr_in );

    connect->data = this->socket_;

    this->socket_->data = connect;

    auto result = uv_tcp_connect( connect, this->socket_, ( const struct sockaddr* )&addr_in, Core::UVSockService::uv_connected_cb_process );

    uv_run( this->loop_, UV_RUN_DEFAULT );

    return true;
}

void Core::UVSockService::run()
{
    uv_run( this->loop_, UV_RUN_NOWAIT );
}

void Core::UVSockService::uv_connection_cb_process( uv_stream_t * server, int status )
{

    if ( status < 0 )
    {
        return;
    }

    listen_data* data = static_cast< listen_data* >( server->data );

    uv_tcp_t *client = new uv_tcp_t();
    uv_tcp_init( ( uv_loop_t* ) data->loop, client );

    Session* session = SessionFactory::instance()->create( client, data->port );

    SessionManager::instance()->push( session );

    client->data = static_cast< void* >( session );

    if ( uv_accept( server, ( uv_stream_t* ) client ) == 0 ) 
    {
        uv_read_start( ( uv_stream_t* ) client, 
                       Core::UVSockService::uv_alloc_cb_process, 
                       Core::UVSockService::uv_read_cb_process );
    }
    else 
    {
        uv_close( ( uv_handle_t* ) client, Core::UVSockService::uv_close_cb_process );
    }

}

void Core::UVSockService::uv_connected_cb_process( uv_connect_t * req, int status )
{
    if ( status < 0 )
    {
        Logger::error( "%s", uv_strerror( static_cast< int >( status ) ) );

        auto connect = ( uv_connect_t* ) req->data;

        SAFE_DELETE ( connect );
            
        return;
    }

    uv_tcp_t* client = static_cast< uv_tcp_t* >( req->data );

    Session* session = SessionFactory::instance()->create( client, SESSIONTYPE::MASTER );

    client->data = session;

    uv_read_start( ( uv_stream_t* ) client,
                   Core::UVSockService::uv_alloc_cb_process,
                   Core::UVSockService::uv_read_cb_process );

    SessionManager::instance()->push( session );
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

    if ( static_cast< int >( nread ) < 0 )
    {
        printf( "[%d]%s\r\n", session->id(), uv_strerror( static_cast< int >( nread ) ) );
        uv_read_stop( stream );
        session->close();
        return;
    }

    session->on_recv( buf->base, static_cast< int >( nread ) );
}

void Core::UVSockService::uv_close_cb_process( uv_handle_t * handle )
{
    Session* session = static_cast< Session* >( handle->data );

    SessionManager::instance()->remove( session );

    handle->data = nullptr;
}

void Core::UVSockService::uv_write_cb_process( uv_write_t * req, int status )
{

}

void Core::UVSockService::uv_async_cb_process( uv_async_t * handle )
{

}

