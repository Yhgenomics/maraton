#include "HTTPSession.h"
#include "stdio.h"
#include "maraton.h"


HTTPSession::HTTPSession( uv_tcp_t* conn )
    : Session::Session( conn )
{ 
    this->handler = new HTTPHandler( this );
    this->handler->router()->response( [&] ( HTTPResponse* rep ) { 
        auto buffer = rep->bytes();
        this->send( buffer.raw(), buffer.length() );
        this->close();
    } );
}

HTTPSession::~HTTPSession()
{
    SAFE_DELETE( this->handler );
}

void HTTPSession::on_recv( int len )
{
    handler->router()->parse( this->recv_buffer_, len );
}

void HTTPSession::run()
{
    return;
}
