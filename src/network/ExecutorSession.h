/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef EXECUTOR_SESSION_H_
#define EXECUTOR_SESSION_H_ 

#include <vector>
#include <mutex>

#include "maraton.h"
#include "ClusterSession.h"
#include "uv.h"

class Executor;

class ExecutorSession :
    public ClusterSession
{
public:

    ExecutorSession(uv_tcp_t* conn);
    virtual ~ExecutorSession() override;

    virtual void run() override;
     
protected: 

    virtual void on_data_recv( const Buffer& buffer ) override;
    Executor* executor_;

private:

    std::vector<Buffer> buffers_;
    std::mutex mtx;
    
};


#endif //EXECUTOR_SESSION_H_ 