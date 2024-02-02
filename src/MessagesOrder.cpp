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
#include <memory>
#include <unordered_set>

#include <deque>

class Message
{
public:
    Message(std::string_view svMessage, int32_t uIndex);

    const std::string& get_text();
    void print();

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

void Message::print()
{
    std::cout << sMessage_m << std::endl;
}

bool Message::operator<(const Message &other)
{
    return uIndex_m < other.uIndex_m;
}

class MessageFactory
{
public:
    static std::unique_ptr<Message> create_message(std::string_view text);
    // static Message create_message(const std::string& text);

private:
    inline static size_t uMessageCounter = 0;
};

std::unique_ptr<Message> MessageFactory::create_message(std::string_view text)
{
    uMessageCounter++;
    return std::make_unique<Message>(std::string(text), uMessageCounter);
}

// Message MessageFactory::create_message(const std::string &text)
// {
//     uMessageCounter++;
//     return Message(text, uMessageCounter);
// }

class Recipient
{
public:
    // void receive(const Message& message);
    void receive(std::unique_ptr<Message>&& message);

    void print_messages();

private:
    void fix_order();

    std::vector<std::unique_ptr<Message>> vMessages;
    // std::vector<Message> vMessages;
};

void Recipient::receive(std::unique_ptr<Message>&& message)
{
    vMessages.push_back(std::move(message));
}

void Recipient::print_messages()
{
    fix_order();

    for (const auto& pMessage : vMessages) {
        pMessage->print();
    }
}

void Recipient::fix_order()
{
    std::sort(vMessages.begin(), vMessages.end(), 
        [](std::unique_ptr<Message>& upA, std::unique_ptr<Message>& upB) -> bool {
                return *upA < *upB;
        }
    );
}

class Network
{
public:
    void Add(std::unique_ptr<Message>&& upMessage);
    void SendTo(Recipient& recipent);

private:
    std::unordered_set<std::unique_ptr<Message>> usMessages;
};

int main()
{
    Network network;
    std::string sLine;
    for (std::getline(std::cin, sLine); !sLine.empty(); std::getline(std::cin, sLine)) {
        network.Add(MessageFactory::create_message(sLine));
    }

    Recipient recipient;
    network.SendTo(recipient);

    recipient.print_messages();
}

void Network::Add(std::unique_ptr<Message>&& upMessage)
{
    usMessages.insert(std::move(upMessage));
}

void Network::SendTo(Recipient &recipent)
{
    for (auto it = usMessages.begin(); it != usMessages.end();) {
        recipent.receive(std::move(usMessages.extract(it++).value()));
    }
}

