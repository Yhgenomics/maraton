/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef SESSION_MANAGER_H_
#define SESSION_MANAGER_H_ 

#include "Manager.hpp"
#include "Session.h"
#include "maraton.h"

using namespace std;

class SessionManager :
    public Manager<Session>,
    public Singleton<SessionManager>
{
public:

    void run();

private:
    friend Singleton<SessionManager>;

};

#endif //!SESSION_MANAGER_H_ 