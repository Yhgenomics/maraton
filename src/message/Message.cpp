#include "Message.h"

Message::Message(const std::string json_str )
{
    this->raw_data_ = nlohmann::json::parse( json_str );;

    this->status_ = this->raw_data_["command"];
    this->command_ = this->raw_data_["status"];
}

Message::Message( const std::string version, size_t command, size_t status )
{
    this->raw_data_.clear();
    this->raw_data_["command"] = command;
    this->raw_data_["status"] = status;
    this->raw_data_["version"] = version;

    this->version_ = version;
    this->status_ = status;
    this->command_ = command;
}

Message::Message( Message & message )
{
    this->raw_data_.parse( message.raw_data_.dump() );
    this->command_ = message.command_;
    this->status_ = message.status_;

}

Message::Message( Message && message )
{
    this->raw_data_ = message.raw_data_;
    this->command_ = message.command_;
    this->status_ = message.status_;

    message.raw_data_ = nullptr;
    message.command_ = 0;
    message.status_ = 0;
}

Message& Message::operator=( Message & message )
{
    this->raw_data_ = message.raw_data_;
    this->command_ = message.command_;
    this->status_ = message.status_;

    return *this;
}

Message & Message::operator=( Message && message )
{
    this->raw_data_ = message.raw_data_;
    this->command_ = message.command_;
    this->status_ = message.status_;

    message.raw_data_ = nullptr;
    message.command_ = 0;
    message.status_ = 0;
    return *this;
}

Buffer Message::bytes()
{
    Buffer buffer;
    auto json = this->raw_data_.dump();
    buffer.raw( json.c_str(), static_cast< int >( json.length() ) + 1 );

    return buffer;
}
