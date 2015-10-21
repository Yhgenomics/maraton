#include "SessionManager.h"
#include "maraton.h"

void SessionManager::run()
{
    auto elements = Manager<Session>::instances();
    for ( auto s : elements )
    {
        s->run();
    }
}
