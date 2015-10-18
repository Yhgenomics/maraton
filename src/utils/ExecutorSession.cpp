#include "ExecutorSession.h"
#include "json.hpp"

ExecutorSession::ExecutorSession(uv_tcp_t * conn)
    : ClusterSession::ClusterSession(conn)
{

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

}
 