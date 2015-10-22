#include "Executor.h"

void Executor::message( std::string json_str )
{

}

void Executor::send( Message & message )
{
    Buffer b = message.bytes();
    this->session_->send( b.raw(), b.length() );
}
