#ifndef NETWORK_DATA_BUILDER_H_
#define NETWORK_DATA_BUILDER_H_

// in some cases two tcp message will be combined into one or chopped
// this class will solve the problem
class NetworkDataBuilder
{
public:

    NetworkDataBuilder();
    ~NetworkDataBuilder();
   
    virtual bool push( const char* data, int len );
    virtual char* pop( int len ) ;

    int length();
    int used_length();
    int available_length();

    int tail_ = 0;
    int head_ = 0;

private:

    NetworkDataBuilder( NetworkDataBuilder & ) = delete;
    NetworkDataBuilder( NetworkDataBuilder && ) = delete;
    NetworkDataBuilder operator=( NetworkDataBuilder ) = delete;

   
    int used_len_ = 0;
    int available_len_ = 0;

    const int buffer_length_ = 100;

    char* circle_buffer_ = nullptr;

};

#endif // !NETWORK_DATA_BUILDER_H_
