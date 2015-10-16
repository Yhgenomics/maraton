/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef LOGER_H_
#define LOGER_H_ 

#include "stdio.h"
#include <stdarg.h>

#include "Singleton.h"

class Logger
{
public:

    static void sys( const char* fmt, ... );
    static void error( const char* fmt, ... );

private:

    Logger();
    ~Logger();

};

#endif //LOGER_H_ 