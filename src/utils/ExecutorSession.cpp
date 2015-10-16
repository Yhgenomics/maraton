#include "ExecutorSession.h"

ExecutorSession::ExecutorSession(uv_tcp_t * conn)
    : Session::Session(conn)
{

}

ExecutorSession::~ExecutorSession()
{
}

void ExecutorSession::on_recv( int len )
{
}

void ExecutorSession::run()
{
}
