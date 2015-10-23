#include "ExecutorSession.h"
#include "json.hpp"
#include "ExecutorManager.h"
#include "Executor.h"
#include "json.hpp"
#include <string.h>
#include <memory>

ExecutorSession::ExecutorSession(uv_tcp_t * conn)
    : ClusterSession::ClusterSession(conn)
{
    executor_ = new Executor( this );
    ExecutorManager::instance()->push( executor_ );
}

ExecutorSession::~ExecutorSession()
{

}

void ExecutorSession::run()
{ 
    ClusterSession::run();

}

void ExecutorSession::on_data_recv( Buffer* buffer )
{ 
    auto buf = buffer;

    executor_->message( std::string( buf->raw(), buf->length() ) );
}
 