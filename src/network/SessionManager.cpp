#include "SessionManager.h"
#include "maraton.h"

template<class TT>
void SessionManager<TT>::run()
{
    auto elements = Manager<TT>::instances();
    for ( auto s : elements )
    {
        s->run();
    }
}

template<class TT>
TT* SessionManager<TT>::create( uv_tcp_t * conn )
{
    TT* t = new TT( conn );
    this->push( t );
    return t;
}

template<class TT>
bool SessionManager<TT>::remove( TT* t )
{
    return this->pop( t );
}
