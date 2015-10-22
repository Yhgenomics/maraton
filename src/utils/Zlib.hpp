/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-10-22
* Description:
* * * * * * * * * * * * * * * */ 

#ifndef ZLIB_HPP_
#define ZLIB_HPP_

#include <memory.h>
#include "Buffer.hpp"

class Zlib
{
public:

    Buffer compress( const char* data, int len)
    {
        Buffer buffer;
        buffer.raw( data, len );
        
        return buffer;
    };

    Buffer uncompress( const char* data, int len)
    {
        Buffer buffer;
        buffer.raw( data, len );

        return buffer;
    };
};

#endif // !COMPRESSOR_HPP_
