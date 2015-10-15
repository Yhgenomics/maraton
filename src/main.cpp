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
void logic()
{
    while ( 1 )
    {
        SessionManager::instance()->run();
        ExecutorManager::instance()->run();
    };
}
void test_server()
{
    Core::UVSockService http;
    http.session_type( SESSIONTYPE::RESTAPI );
    http.listen( "0.0.0.0", 80 );
    
    Core::UVSockService service;
    service.session_type( SESSIONTYPE::EXECUTOR );
    service.listen( "0.0.0.0", 90 );

    //auto thr = std::thread( logic );

    while ( 1 )
    {
        http.run();
        service.run();

        SessionManager::instance()->run();
        ExecutorManager::instance()->run();
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
