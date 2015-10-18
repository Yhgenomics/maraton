#include "SessionManager.h"
#include "maraton.h"

void SessionManager::push( Session * session )
{
    this->sessions_.push_back( session );
}

void SessionManager::remove( Session * session )
{
    vector<Session*>::iterator itr = this->sessions_.begin();

    while ( itr != this->sessions_.end() )
    {
        if ( *itr == session )
        {
            itr = this->sessions_.erase( itr );
            break;
        } 
        else
        {
            itr++;
        }
    }

    SAFE_DELETE( session );
}

void SessionManager::run()
{
    for ( auto s : this->sessions_ )
    {
        s->run();
    }
}
