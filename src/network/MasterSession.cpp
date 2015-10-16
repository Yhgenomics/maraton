#include "MasterSession.h"

#include <stdio.h>
#include <memory.h>
 
MasterSession::MasterSession( uv_tcp_t * conn )
    :Session::Session( conn )
{

}

MasterSession::~MasterSession()
{
    
}

void MasterSession::on_recv( int len )
{
    printf_s( "Master : %s", this->recv_buffer() );
}

void MasterSession::run()
{
}
