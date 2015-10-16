#include "SessionFactory.h"
#include "MasterSession.h"
#include "ExecutorSession.h"

Session * SessionFactory::create( uv_tcp_t* conn , SESSIONTYPE type )
{
    switch ( type )
    {
    case Master:
        return new MasterSession( conn );
    break;
    case RESTAPI:
    break;
    case EXECUTOR:
        return new ExecutorSession( conn );
    break;
    default:
    break;
    }
    
}

SessionFactory::SessionFactory()
{
}

SessionFactory::~SessionFactory()
{
}
