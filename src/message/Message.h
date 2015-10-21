/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef MESSAGE_H_
#define MESSAGE_H_ 

#include "maraton.h"

class Message
{
public :

    //deserilize
    Message( nlohmann::basic_json<> json );

    //serilize
    Message( size_t command, size_t status);

    Message( Message& message);
    Message( Message&& message );
    Message& operator = ( Message& message );
    Message& operator = ( Message&& message );

    virtual ~Message() {};

    virtual Buffer bytes();

    size_t command() { return this->command_; };
    size_t status() { return this->status_; };

protected:

    size_t command_;
    size_t status_;

    nlohmann::basic_json<> raw_data_;

};

#endif //!MESSAGE_H_ 