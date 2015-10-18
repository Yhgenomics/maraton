#ifndef NETWORK_DATA_BUILDER_H_
#define NETWORK_DATA_BUILDER_H_

#include "Macro.h"

// in some cases two tcp message will be combined into one or chopped
// this class will solve the problem
class CircleBuffer
{
public:

    CircleBuffer();
    ~CircleBuffer();
   
    virtual bool push( const char* data, int len );
    virtual char* pop( int len ) ;

    int length();
    int used_length();
    int available_length();

    int tail_ = 0;
    int head_ = 0;

private:

    CircleBuffer( CircleBuffer & ) = delete;
    CircleBuffer( CircleBuffer && ) = delete;
    CircleBuffer operator=( CircleBuffer ) = delete;

   
    int used_len_ = 0;
    int available_len_ = 0;

    const int buffer_length_ = CIRCLE_BUFFER_SIZE;

    char* circle_buffer_ = nullptr;

};

#endif // !NETWORK_DATA_BUILDER_H_
