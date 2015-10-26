#include "maraton.h"
#include "network/UVSockService.h"

#include "SessionManager.hpp"
#include "ExecutorManager.h"
#include <thread>
#include "json.hpp"
#include "ExecutorSession.h"

#include "ExecutorSession.h"
#include "MasterSession.h"
#include "HTTPSession.h"

Buffer test_buffer()
{
    Buffer b;
    auto data = new char[100];
    for ( size_t i = 0; i < 100; i++ )
    {
        data[i] = ( char ) ( i % 255 );
    }
    
    b.raw( data, 100 );

    return b;
}  

#define SERVER
void logic( uv_timer_t* handle )
{
   
#ifdef SERVER
   
    //SessionManager<HTTPSession>::instance()->run();
    SessionManager<ExecutorSession>::instance()->run();
    //ExecutorManager::instance()->run();
#else

    SessionManager<MasterSession*>::instance()->run();

#endif
}

void test_server()
{ 

#ifdef SERVER

    Core::UVSockService service;
    
    service.listen( "0.0.0.0", 90 );
    service.listen( "0.0.0.0", 80 );
   
#else

    Core::UVSockService service;
    service.connect( "127.0.0.1", 90 );

#endif

    //std::thread thr( logic );
    uv_timer_t timer;
    uv_timer_init( service.loop() , &timer );
    uv_timer_start( &timer, logic, 0, 1 );

    SessionManager<ExecutorSession>::instance()->on_create( 
        [] ( Session* session ) { 
            printf( "Session %d callback", session->id() );
        } 
    );


    while ( 1 )
    {
       
        service.run();
       
        //this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }
    
    //thr.join();
}

int main(int argc , char** argv)
{ 
    test_server();
	return 0;
}
