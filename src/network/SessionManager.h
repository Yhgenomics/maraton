/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef SESSION_MANAGER_H_
#define SESSION_MANAGER_H_ 

#include <vector>
#include "Session.h"

#include "maraton.h"

using namespace std;

class SessionManager :
    public Singleton<SessionManager>
{
public:

    void push( Session* session );
    void remove( Session* session );

private:

    friend Singleton<SessionManager>;

    vector<Session*> sessions_;

};

#endif //SESSION_MANAGER_H_ 