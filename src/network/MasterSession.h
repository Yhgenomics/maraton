/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-16 13:21
* Description:
* * * * * * * * * * * * * * * */
#ifndef MASTER_SESSION_H_
#define MASTER_SESSION_H_

#include "Session.h"

#include "maraton.h"
#include "uv.h"

class MasterSession :
    public Session
{ 
public:

    MasterSession( uv_tcp_t * conn );
    ~MasterSession();

    virtual void on_recv( int len ) override;
    virtual void run() override;
    
};

#endif //MASTER_SESSION_H__H_ 