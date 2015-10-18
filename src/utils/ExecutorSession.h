/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef EXECUTOR_SESSION_H_
#define EXECUTOR_SESSION_H_ 

#include "maraton.h"
#include "ClusterSession.h"
#include "uv.h"

class ExecutorSession :
    public ClusterSession
{
public:

    ExecutorSession(uv_tcp_t* conn);
    virtual ~ExecutorSession() override;

    virtual void run() override;
     
protected:
    
    // Í¨¹ý ClusterSession ¼Ì³Ð
    virtual void on_data_recv( const Buffer buffer ) override;

};


#endif //EXECUTOR_SESSION_H_ 