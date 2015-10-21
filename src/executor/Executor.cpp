#include "Executor.h"

void Executor::message( nlohmann::basic_json<> json )
{

}

void Executor::send( Message & message )
{
    Buffer b = message.bytes();
    this->session_->send( b.raw(), b.length() );
}
