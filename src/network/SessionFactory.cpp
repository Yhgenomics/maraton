#include "SessionFactory.h"
#include "MasterSession.h"
#include "ExecutorSession.h"
#include "HTTPSession.h"

Session * SessionFactory::create( uv_tcp_t* conn , SESSIONTYPE type )
{
    switch ( type )
    {
    case MASTER:
        return new MasterSession( conn );
    break;
    case RESTAPI:
        return new HTTPSession( conn );
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
