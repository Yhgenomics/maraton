#include "HTTPSession.h"
#include "stdio.h"
#include "maraton.h"

HTTPSession::HTTPSession( uv_tcp_t* conn )
    : Session::Session( conn )
{ 
    this->router_ = new HTTPRouter();

    this->router_->get( "/", [] ( HTTPRequest* req,HTTPResponse* rep) {

        char data[] = "<body><h1>Hello!!!!</h1></body>";
        rep->content( data, sizeof( data ) );

    } );


    this->router_->response( [this] (HTTPResponse* rep) {

        int len = 0;
        auto data = rep->bytes();
        this->send( data.raw, data.length );
        
        this->close();

    } );
}

HTTPSession::~HTTPSession()
{
    SAFE_DELETE( this->router_ );
}

void HTTPSession::on_recv( int len )
{
    this->router_->parse( this->recv_buffer_, len );
}

void HTTPSession::run()
{

}
