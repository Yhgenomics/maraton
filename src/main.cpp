#include "maraton.h"
#include "UVSockService.h"
#include "vld.h"

#include "SessionManager.h"
#include "ExecutorManager.h"
#include <thread>

Buffer test_buffer()
{
    Buffer b;
    b.raw = new char[100];
    for ( size_t i = 0; i < 100; i++ )
    {
        b.raw[i] = ( char ) ( i % 255 );
    }
    b.length = 100;

    return b;
}
void run_http()
{
    
}
void run_server()
{
   
}
void test_server()
{
    Core::UVSockService http;
    http.session_type( SESSIONTYPE::RESTAPI );
    http.listen( "0.0.0.0", 80 );
    
    Core::UVSockService service;
    service.session_type( SESSIONTYPE::EXECUTOR );
    service.listen( "0.0.0.0", 90 );
    

    while ( 1 )
    {
       // srv.run();
       // restAPI.run();
        http.run();
        service.run();

        //ExecutorManager::instance()->run();
        std::this_thread::sleep_for( std::chrono::seconds( 0 ) );

    }
}



int main(int argc , char** argv)
{
    test_server();
	return 0;
}