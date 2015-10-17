#include "NetworkDataBuilder.h"
#include <memory.h>

NetworkDataBuilder::NetworkDataBuilder()
{
    this->circle_buffer_ = new char[this->buffer_length_];
    this->available_len_ = this->buffer_length_;
    this->used_len_ = 0;
}

NetworkDataBuilder::~NetworkDataBuilder()
{
    if ( this->circle_buffer_ != nullptr )
    {
        delete this->circle_buffer_;
        this->circle_buffer_ = nullptr;
    }
}

bool NetworkDataBuilder::push( const char * data, int len )
{
    if ( available_length() < len )
    {
        throw "[NetworkDataBuilder.cpp] not enough buffer";
        return false;
    }


    if ( tail_ + len > this->buffer_length_ )
    {
        char* ptail = this->circle_buffer_ + this->tail_;
        int delta_len = this->buffer_length_ - tail_;
        memcpy( ptail, data, delta_len );
        memcpy( this->circle_buffer_, data + delta_len, len - delta_len );
    }
    else
    {
        char* ptail = this->circle_buffer_ + this->tail_;

        memcpy( ptail, data, len );
    }


  

    this->tail_ = ( this->tail_ + len ) % this->buffer_length_;

    this->used_len_ += len;

    this->available_len_ = this->buffer_length_ - this->used_len_;

    return true;
}

char * NetworkDataBuilder::pop( int len )
{
    if ( len > this->used_length() )
    {
        return nullptr;
    }

    char* ret = new char[len];
    int ret_pos = 0;
    char* phead = this->circle_buffer_ + this->head_;
    
    // there are two pices data
    // one is at end of circle buffer
    // antoher is at front of circle buffer
    if ( ( this->head_ + len ) > this->buffer_length_ )
    {
        int end_len = this->buffer_length_ - this->head_;
        memcpy( ret, phead+ ret_pos, end_len );
        ret_pos += this->buffer_length_ - this->head_;
        memcpy( ret + ret_pos, this->circle_buffer_, ( len - end_len ) );
    }
    // circle buffer contains all data inside
    else
    {
        memcpy( ret, phead + ret_pos, len );
    }

    this->head_ = ( this->head_ + len ) % this->buffer_length_;

    this->used_len_ -= len;

    this->available_len_ = this->buffer_length_ - this->used_len_;

    return ret;
}
 
int NetworkDataBuilder::length()
{
    return this->buffer_length_;
}

int NetworkDataBuilder::used_length()
{
    return   this->used_len_;
}

int NetworkDataBuilder::available_length()
{
    
    return this->available_len_;
}
