#ifndef BYTES_HPP_
#define BYTES_HPP_

#include "Macro.h"

class Buffer
{
public:
    Buffer() {};
    ~Buffer()
    {
        SAFE_DELETE( this->raw );
    };
    Buffer( Buffer & buffer )
    {
        SAFE_DELETE ( this->raw );

        this->raw = new char[buffer.length];
        memcpy( this->raw, buffer.raw, buffer.length );

        this->length = buffer.length;
    };
    Buffer( Buffer&& buffer )
    {
        this->raw = buffer.raw;
        this->length = buffer.length;

        buffer.raw = nullptr;
        buffer.length = 0;
    }
    Buffer& operator=( Buffer& buffer )
    {
        SAFE_DELETE ( this->raw );

        this->raw = new char[buffer.length];
        memcpy( this->raw, buffer.raw, buffer.length );

        this->length = buffer.length;

        return *this;
    }
    Buffer& operator=( Buffer&& buffer )
    {
        this->raw = buffer.raw;
        this->length = buffer.length;

        buffer.raw = nullptr;
        buffer.length = 0;

        return *this;
    }

    char* raw = nullptr;
    int length = 0;
};


#endif // !BYTES_HPP_
