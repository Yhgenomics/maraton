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

    std::unique_lock <std::mutex> locker( this->mtx );

    std::vector<Buffer> tmp_v ( this->buffers_.begin(), this->buffers_.end() );
    this->buffers_.clear();

    locker.unlock();

    for ( auto b : tmp_v)
    {
        executor_->message( std::string( b.raw(), b.length() ) );
    } 
}

void ExecutorSession::on_data_recv( const Buffer& buffer )
{ 
    std::unique_lock <std::mutex> locker( this->mtx );

    buffers_.push_back( buffer );
    
}
 