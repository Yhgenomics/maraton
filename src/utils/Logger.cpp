#include "Logger.h"

void Logger::sys( const char * fmt, ... )
{
    printf( "[SYS]" );
    va_list args;
    va_start( args, fmt );
    printf( fmt, *args );
    va_end( args );
    printf( "\r\n" );
}

void Logger::error( const char * fmt, ... )
{
    printf( "[ERROR]" );
    va_list args;
    va_start( args, fmt );
    printf( fmt, *args );
    va_end( args );
    printf( "\r\n" );
}

Logger::Logger()
{
}

Logger::~Logger()
{
}
