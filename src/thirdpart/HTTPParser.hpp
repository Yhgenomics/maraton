#ifndef HTTP_PARSER_H_
#define HTTP_PARSER_H_

#include "stdio.h"
#include <vector>
#include <map>
#include <memory.h>
#include <string>

using namespace std;

class HTTPParser
{
public:

    HTTPParser()
    {
        this->method_ = "";
    };
    ~HTTPParser()
    {
    };

    string method()
    {
        return string( this->method_ );
    };

    string path()
    {
        return string( this->path_ );
    };

    map<string, string> header()
    {
        return map<string, string>( this->header_.begin(), this->header_.end() );
    }

    string body()
    {
        return string( this->body_ );
    };

    bool parse( const char* data, int len )
    {
        reset();

        HTTPPARSESTATE state = HTTPPARSESTATE::METHOD;

        const char* phead = data;
        const char* pdata = phead;

        int head = 0;

        string k, v;

        bool ret = false;

        do
        {
            switch ( state )
            {
                //header
            case HTTPPARSESTATE::METHOD: {
                if ( *pdata == ' ' )
                {
                    this->method_ = string( phead, ( pdata - phead ) );
                    phead = pdata + 1;
                    state = HTTPPARSESTATE::PATH;
                }
            }break;
            case HTTPPARSESTATE::PATH: {
                if ( *pdata == ' ' )
                {
                    this->path_ = string( phead, ( pdata - phead ) );

                    while ( ( *pdata ) != '\n' ) pdata++;

                    //skip \n 
                    pdata++;
                    phead = pdata;
                    state = HTTPPARSESTATE::HEADER_KEY;
                }
            }break;
                //property
            case HTTPPARSESTATE::HEADER_KEY: {
                if ( *pdata == ':' )
                {
                    k = string( phead, ( pdata - phead ) );

                    //skip :
                    pdata++;

                    while ( *pdata == ' ' )pdata++;

                    phead = pdata;

                    state = HTTPPARSESTATE::HEADER_VALUE;
                    //step_state = 1;
                }

                if ( *pdata == '\n' && *( pdata - 1 ) == '\r' )
                {
                    state = HTTPPARSESTATE::BODY;
                    pdata++;
                    phead = pdata;
                    ret = true;
                }

            }break;
            case HTTPPARSESTATE::HEADER_VALUE: {
                if ( *pdata == '\n' && *( pdata - 1 ) == '\r' )
                {
                    v = string( phead, ( pdata - phead - 1 ) );

                    pdata++;
                    phead = pdata;
                    state = HTTPPARSESTATE::HEADER_KEY;

                    this->header_.insert( make_pair( string( k ), string( v ) ) );
                }
            }break;
                //body
            case HTTPPARSESTATE::BODY: {
                if ( ( pdata - data ) == len )
                {
                    this->body_ = string( phead, pdata - phead );
                    ret = true;
                }
            }break;

            default:
            return false;
            }

            pdata++;


        } while ( ( pdata - data ) <= len );

        if ( !ret )
        {
            this->reset();
        }

        return ret;
    }

private:

    enum HTTPPARSESTATE
    {
        PATH = 1,
        METHOD,
        HEADER_KEY,
        HEADER_VALUE,
        BODY
    };

    map<string, string> header_;

    string method_;
    string path_;
    string body_;

    void reset()
    {
        this->method_ = string();
        this->path_ = string();
        this->body_ = string();
        this->header_.clear();
    }
};

#endif //HTTP_PARSER_H_