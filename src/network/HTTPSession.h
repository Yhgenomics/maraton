/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef HTTP_SESSION_H_
#define HTTP_SESSION_H_ 

#include "uv.h"
#include "Session.h"
#include "HTTPRouter.hpp"

class HTTPSession :
    public Session
{
public:

    HTTPSession( uv_tcp_t* conn );
    virtual ~HTTPSession() override;

    // Í¨¹ý Session ¼Ì³Ð
    virtual void on_recv( int len ) override;
    virtual void run() override;

private:

    HTTPRouter* router_;

};


#endif //HTTP_SESSION_H_H_ 