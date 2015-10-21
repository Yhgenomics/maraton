#include "SessionManager.h"
#include "maraton.h"

void SessionManager::run()
{
    for ( auto s : Manager<Session>::instance_ )
    {
        s->run();
    }
}
