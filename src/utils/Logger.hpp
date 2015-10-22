/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-22
* Description:
* * * * * * * * * * * * * * * */

#ifndef LOGER_H_
#define LOGER_H_ 

#include "stdio.h"
#include <stdarg.h>
#include "Singleton.hpp"

class Logger
{
public:

    static void sys( const char* fmt, ... )
    {
        printf( "[SYS]" );
        va_list args;
        va_start( args, fmt );
        printf( fmt, *args );
        va_end( args );
        printf( "\r\n" );
    }

    static void error( const char* fmt, ... )
    {
        printf( "[ERROR]" );
        va_list args;
        va_start( args, fmt );
        printf( fmt, *args );
        va_end( args );
        printf( "\r\n" );
    }

private:
    
    Logger() {};
    ~Logger() {};
};

#endif //LOGER_H_ 