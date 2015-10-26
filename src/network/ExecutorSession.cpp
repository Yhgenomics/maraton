#include "ExecutorSession.h"
#include "json.hpp"
#include "ExecutorManager.h"
#include "Executor.h"
#include "json.hpp"
#include <string.h>
#include <memory>
#include "SessionManager.hpp"

ExecutorSession::ExecutorSession(uv_tcp_t * conn)
    : ClusterSession::ClusterSession(conn)
{
    executor_ = new Executor( this );
    //ExecutorManager::instance()->push( executor_ );
}

ExecutorSession::~ExecutorSession()
{
    SAFE_DELETE( executor_ );
}

void ExecutorSession::run()
{ 
    ClusterSession::run();

}
 

void ExecutorSession::message( Message * message )
{
    printf( "Session[%d] Command:%d\r\n", this->id(), message->command() );
}

void ExecutorSession::shutdown()
{
    SessionManager<ExecutorSession>::instance()->remove( this );
}
