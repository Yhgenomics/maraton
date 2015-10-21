#ifndef CLUSTER_SESSION_H_
#define CLUSTER_SESSION_H_

#include "maraton.h"
#include "Session.h"

class ClusterSession :
    public Session
{
public:
    ClusterSession( uv_tcp_t* conn );
    virtual ~ClusterSession() override;

    // Í¨¹ý Session ¼Ì³Ð
    void on_recv( int len ) override;
    virtual void run() override;

protected:

    virtual void on_data_recv( Buffer buffer) = 0;

private:

    enum ES_READSTATE
    {
        FLAG = 0,
        HEAD,
        BODY
    };

    ES_READSTATE read_state_ = ES_READSTATE::FLAG;

    CircleBuffer circle_buffer_;
    Zlib compressor_;

    int compressed_length_ = 0;
    int oringal_length_ = 0;

    bool try_read_flag();
    bool try_read_head();
    bool try_read_body();

};

#endif // !CLUSTER_SESSION_H_
