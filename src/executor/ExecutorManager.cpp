#include "ExecutorManager.h"

void ExecutorManager::run()
{
    return;
}

void ExecutorManager::remove( Executor * instance )
{
    Manager<Executor>::remove( instance );
}
