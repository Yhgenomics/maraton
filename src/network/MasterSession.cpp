#include "MasterSession.h"

#include <stdio.h>
#include <memory.h>
 
MasterSession::MasterSession( uv_tcp_t * conn )
    : ClusterSession::ClusterSession( conn )
{

}

MasterSession::~MasterSession()
{
    
}

void MasterSession::run() 
{
    ClusterSession::run();
}

void MasterSession::on_data_recv( const Buffer& buffer )
{

}
