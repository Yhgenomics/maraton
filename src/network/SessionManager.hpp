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

template<class TT>
class SessionManager :
    public Manager<TT>,
    public Singleton<SessionManager<TT>>
{
public:

    void run()
    {
        auto elements = Manager<TT>::instances();
        for ( auto s : elements )
        {
            auto session = static_cast< Session* >( s );
            session->run();
        }
    };
        
    TT* create( uv_tcp_t* conn )
    {
        TT* t = new TT( conn );
        this->push( t );
        return t;
    };

    bool remove( TT*  t )
    {
        return this->pop( t );
    };

    TT* find( int session_id )
    {
        auto elements = Manager<TT>::instances();
        for ( auto s : elements )
        {
            auto session = static_cast< Session* >( s );
            if ( session->id() == session_id )
            {
                return static_cast< TT* >( session );
            }
        }

        return nullptr;
    };

private:

    friend Singleton<SessionManager<TT>>;
};

#endif //!SESSION_MANAGER_H_ 