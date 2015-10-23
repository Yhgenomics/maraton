#include "MasterSession.h"

#include <stdio.h>
#include <memory.h>
#include "Master.h"

MasterSession::MasterSession( uv_tcp_t * conn )
    : ClusterSession::ClusterSession( conn )
{
    master_ = new Master( this );
}

MasterSession::~MasterSession()
{
    
}

void MasterSession::run() 
{
    ClusterSession::run(); 

    this->master_->run();
}

void MasterSession::on_data_recv( Buffer* buffer )
{
    master_->message( std::string( buffer->raw(), buffer->length() ) );
}
