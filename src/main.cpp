#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <deque>
#include <cstring>
#include <string>

#include <deque>

class Message
{
public:
    Message(std::string_view svMessage, int32_t uIndex);

    const std::string& get_text();

    bool operator<(const Message& other);

private:
    std::string sMessage_m;
    int32_t uIndex_m;
};

Message::Message(std::string_view svMessage, int32_t uIndex)
: sMessage_m(svMessage)
, uIndex_m(uIndex)
{
}

const std::string &Message::get_text()
{
    return sMessage_m;
}

bool Message::operator<(const Message &other)
{
    return uIndex_m < other.uIndex_m;
}

class MessageFactory
{
public:
    static Message create_message(const std::string& text);

private:
    inline static size_t uMessageCounter = 0;
};

Message MessageFactory::create_message(const std::string &text)
{
    uMessageCounter++;
    return Message(text, uMessageCounter);
}

class Recipient
{
public:
    Recipient(/* args */);
    ~Recipient();

private:
    /* data */
};

Recipient::Recipient(/* args */)
{
}

Recipient::~Recipient()
{
}

class Network
{
public:
    Network(/* args */);
    ~Network();

private:
    /* data */
};

Network::Network(/* args */)
{
}

Network::~Network()
{
}

int main()
{
    MessageFactory message_factory;
    Recipient recipient;
}
