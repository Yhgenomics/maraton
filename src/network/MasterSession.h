/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-16 13:21
* Description:
* * * * * * * * * * * * * * * */

#ifndef MASTER_SESSION_H_
#define MASTER_SESSION_H_

#include "ClusterSession.h"

#include "maraton.h"
#include "uv.h"

class Master;

class MasterSession :
    public ClusterSession
{ 
public:

    MasterSession( uv_tcp_t * conn );
    virtual ~MasterSession() override;

    virtual void run() override;
    
protected:
     
    virtual void on_data_recv( Buffer* buffer ) override; 
    Master* master_;
};

#endif //MASTER_SESSION_H__H_ 