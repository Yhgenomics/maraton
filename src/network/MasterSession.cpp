#include "MasterSession.h"

#include <stdio.h>
#include <memory.h>
#include "Master.h"

#include "SessionManager.hpp"

MasterSession::MasterSession( uv_tcp_t * conn )
    : ClusterSession::ClusterSession( conn )
{
    master_ = new Master( this );
}

MasterSession::~MasterSession()
{
    SAFE_DELETE( master_ );
}

void MasterSession::run() 
{
    ClusterSession::run(); 

    //static int time = Timer::tick();

    //if ( ( Timer::tick() - time ) > 200 )
    //{
    //    time = Timer::tick();
    //    Message msg = Message("1.0.0",0xFF,0xDD);
    //    send( &msg );
    //}
}

void MasterSession::close()
{
    SessionManager<MasterSession>::instance()->remove( this );
}

void MasterSession::message( Message * message )
{
    
}

void MasterSession::shutdown()
{
    SessionManager<MasterSession>::instance()->remove( this );
}
 