#include "maraton.h"
#include "UVSockService.h"

int main(int argc , char** argv)
{
    Core::UVSockService srv;
    Core::UVSockService restAPI;


    srv.listen( "0.0.0.0", 90 );

    restAPI.listen( "0.0.0.0", 88 );

    while ( 1 )
    {
        srv.run();
        restAPI.run();
    }

    //executor port
    //Core::UVSockService::instance()->listen( "0.0.0.0", 4449 );
    
    //rest api port
    //Core::UVSockService::instance()->listen( "0.0.0.0", 80 );

    //run service
    //Core::UVSockService::instance()->run();
	return 0;
}