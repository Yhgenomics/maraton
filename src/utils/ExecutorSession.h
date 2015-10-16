/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef EXECUTOR_SESSION_H_
#define EXECUTOR_SESSION_H_ 

#include "Session.h"
#include "uv.h"

class ExecutorSession :
    public Session
{
public:
    ExecutorSession(uv_tcp_t* conn);
    ~ExecutorSession();

    // ͨ�� Session �̳�
    virtual void on_recv( int len ) override;

    virtual void run() override;

};


#endif //EXECUTOR_SESSION_H_ 