#include "ExecutorSession.h"
#include "json.hpp"
#include "ExecutorManager.h"
#include "Executor.h"
#include "json.hpp"
#include <string.h>

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

void ExecutorSession::on_data_recv( const Buffer buffer )
{
    auto json = nlohmann::json::parse( std::string( buffer.raw, buffer.length ) );
    executor_->message( json );
}
 