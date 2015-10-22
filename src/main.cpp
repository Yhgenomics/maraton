#include "maraton.h"
#include "network/UVSockService.h"
#include "vld.h"

#include "SessionManager.h"
#include "ExecutorManager.h"
#include <thread>
#include "json.hpp"

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

void test_server()
{
#define SERVER

#ifdef SERVER

    Core::UVSockService service;
    
    service.listen( "0.0.0.0", 90 );
    service.listen( "0.0.0.0", 80 );

#else

    Core::UVSockService client;
    client.session_type( SESSIONTYPE::MASTER );
    client.connect( "127.0.0.1", 90 );

#endif

    while ( 1 )
    {
        service.run();
        SessionManager::instance()->run();
        ExecutorManager::instance()->run();
        this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }

    //thr.join();
}



int main(int argc , char** argv)
{

    nlohmann::basic_json<> json = {
        { "pi", 3.141 },
        { "happy", true },
        { "name", "Nielsr" },
        { "nothing", nullptr },
        { "answer", {
            { "everything", 42 }
        } },
        { "list", { 1, 0, 2 } },
        { "object", {
            { "currency", "USD\r\n" },
            { "value", 42.99 }
        } }
    };

    json["data"] = "abcdefg";

    auto f = json["object"]["value"].get<float>();
    auto s = json["data"].get<std::string>();
    std::string str = json.dump();

    json.parse( "{ \"name\" : \"1231\", \"int32\":1234, \"float\":11.22, \"obj\":{ \"name\":\"123123\"} }" );

    test_server();
	return 0;
}
