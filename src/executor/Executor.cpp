#include "Executor.h"

void Executor::run()
{
}

void Executor::message( std::string json_str )
{
    printf( "[%d] %s\r\n", this->session_->id(), json_str.c_str() );

    this->send( Message( json_str ) );
}

void Executor::send( Message && message )
{
    Buffer b = message.bytes();
    this->session_->send( b.raw(), b.length() );
}
