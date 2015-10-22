#include "Master.h"
#include <string.h>

Master::Master( MasterSession * session )
{
    this->session_ = session;
}

void Master::run()
{
    static int lastSend = 0;

    int delta = Timer::tick() - lastSend;

    if ( delta > 10 )
    {
        lastSend = Timer::tick();

        Message msg( "", 500, 0 );
        auto json = msg.data();
        (*json)["data"]["test"] = 0;
        
        std::string str = json->dump();

        this->send( &msg );

    }
}

void Master::message( std::string json_str )
{
}

void Master::send( Message* message )
{
    auto msg_send = message->bytes();
    this->session_->send( msg_send.raw(), msg_send.length() );
}

