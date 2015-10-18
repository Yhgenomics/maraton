#include "maraton.h"
#include "UVSockService.h"
#include "SessionManager.h"
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

void test_server()
{
    Core::UVSockService srv;
    Core::UVSockService restAPI;

    srv.session_type( SESSIONTYPE::EXECUTOR );
    srv.listen( "0.0.0.0", 90 );

    restAPI.session_type( SESSIONTYPE::RESTAPI );
    restAPI.listen( "0.0.0.0", 80 );

    while ( 1 )
    {
        srv.run();
        restAPI.run();

        SessionManager::instance()->run();
    }
}

int main(int argc , char** argv)
{
    test_server();
	return 0;
}