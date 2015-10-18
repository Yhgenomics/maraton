#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include "stdio.h"
#include <string.h>
#include <map>
#include <memory.h>

class HTTPResponse
{
public:

    HTTPResponse()
    {
        header_["Server"] = "YHGenomics/Maraton";
        header_["Content-Length"] = "0";
        header_["Connection"] = "close";

        this->content_ = new char[1024 * 1024];
    }

    ~HTTPResponse()
    {
        delete ( this->content_ );
    }

    void status( int status ) { status_ = status; };
    int status() { return status_; };

    void content_type( std::string type ) { content_type_ = type; };
    std::string content_type() { return content_type_; };

    void header( std::string name, std::string value )
    {
        header_[name] = value;
    }

    void content(const char* data, int len) 
    {
        memcpy( this->content_, data, len );
        this->content_len_ = len;
    };

    int length() {

    };

    const char* bytes(int* len) {

        char buffer[1024 * 512] = { 0 };
        string head = "";
        char* p = buffer;

        head += "HTTP/1.0 "+ this->status_description( this->status_ ) + "\r\n";

        sprintf_s( buffer, sizeof(buffer), "%d", this->content_len_ );
        header_["Content-Length"] = buffer;

        for ( auto kv : header_ )
        {
            head += kv.first + ": " + kv.second + "\r\n";
        }
        head += "\r\n";

        memcpy( buffer, head.c_str(), head.length() );
        *len += static_cast< int >( head.length() );
        memcpy( buffer + head.length(), this->content_, this->content_len_ );
        *len += this->content_len_;

        char* ret = new char[*len];
        memcpy( ret, buffer, *len );

        return ret;
    };

    void clear()
    {

    };

private:

    map<string, string> header_;
    int status_ = 200;
    std::string content_type_ = "application/json";

    char* content_ = nullptr;
    int content_len_ = 0;

    std::string status_description( int status )
    {
        switch ( status )
        {
        case 200:
        return "200 OK";
        break;
        case 404:
        return "404 Not Found";
        break;
        default:
        break;
        }
    }
};

#endif // !HTTP_RESPONSE_H_
