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
#include <unordered_map>

#include <deque>

using Key = int32_t;
using Value = int32_t;

struct Node
{
public:
    Node(Value a_value = -1, Key a_key = -1);

    Value m_value;
    Key m_key;
    std::unique_ptr<Node> m_upNext;
    Node* m_pPrevious;
};

Node::Node(Value a_value, Key a_key)
: m_value(a_value)
, m_key(a_key)
{
}

class Cache
{
public:
    Cache(size_t a_cp);
    virtual ~Cache();

    virtual void set(Key a_key, Value a_value) = 0;
    virtual Value get(Key a_key) = 0;

protected:
    std::unordered_map<uint32_t, Node*> m_mp;
    size_t m_cp;

    std::unique_ptr<Node> m_upHead;
    Node* m_pTail;
};

Cache::Cache(size_t a_cp)
: m_upHead(std::make_unique<Node>())
, m_cp(a_cp)
{
    m_upHead->m_upNext = std::make_unique<Node>();
    m_upHead->m_pPrevious = nullptr;

    m_pTail = m_upHead->m_upNext.get();
    m_pTail->m_upNext = nullptr;
    m_pTail->m_pPrevious = m_upHead.get();
}

Cache::~Cache()
{
    while (m_upHead->m_upNext.get() != m_pTail)
    {
        m_upHead->m_upNext = std::move(m_upHead->m_upNext->m_upNext);
    }
    
}

class LRUCache : public Cache
{
public:
    LRUCache(size_t a_cp);

    void set(Key a_key, Value a_value) final override;
    Value get(Key a_key) final override;

private:
    std::unique_ptr<Node> remove_from_list(Node* a_pNode);
    Node* insert_to_list(std::unique_ptr<Node> a_upInsertNode, Node* a_pInListNode);
    size_t m_nNodes;
};

LRUCache::LRUCache(size_t a_cp)
: Cache(a_cp)
, m_nNodes(0)
{
}

void LRUCache::set(Key a_key, Value a_value)
{
    if (m_mp.count(a_key)) {
        auto pNode = m_mp.at(a_key);
        auto upNodeOwner = remove_from_list(pNode);
        upNodeOwner->m_value = a_value;
        insert_to_list(std::move(upNodeOwner), m_upHead.get());

    } else {
        if (m_nNodes < m_cp) m_nNodes++;
        else {
            m_mp.erase(m_pTail->m_pPrevious->m_key);
            remove_from_list(m_pTail->m_pPrevious);
        }

        auto upNodeOwner = std::make_unique<Node>(a_value, a_key);
        m_mp[a_key] = insert_to_list(std::move(upNodeOwner), m_upHead.get());
        // m_mp[a_key] = insert_to_list(std::make_unique<Node>(a_value), m_upHead.get()); // the same
    }
}

Value LRUCache::get(Key a_key)
{
    if (m_mp.count(a_key)) return m_mp.at(a_key)->m_value;
    else return -1;
}

std::unique_ptr<Node> LRUCache::remove_from_list(Node* a_pNode)
{
    auto pLastNode = a_pNode->m_pPrevious;
    auto&& upNext = a_pNode->m_upNext;
    upNext->m_pPrevious = pLastNode;

    auto upRet = std::move(pLastNode->m_upNext);
    pLastNode->m_upNext = std::move(upNext);

    return upRet;
}

Node* LRUCache::insert_to_list(std::unique_ptr<Node> a_upInsertNode, Node* a_pInListNode)
{
    auto&& upNext = a_pInListNode->m_upNext;
    upNext->m_pPrevious = a_upInsertNode.get();
    a_upInsertNode->m_upNext = std::move(upNext);
    a_upInsertNode->m_pPrevious = a_pInListNode;
    a_pInListNode->m_upNext = std::move(a_upInsertNode);

    return a_pInListNode->m_upNext.get();
}

static int get_number(std::string_view svString, size_t posStart, size_t& a_posEnd)
{
    std::string_view svDigits = "0123456789";
    const auto numberStart = svString.find_first_of(svDigits, posStart);
    a_posEnd = svString.find_first_not_of(svDigits, numberStart);
    const auto svNumber = svString.substr(numberStart, a_posEnd - numberStart);

    return std::stoi(std::string(svNumber));
}

int main()
{
    std::string sLine;
    std::getline(std::cin, sLine);

    uint32_t nCommands, nCapability;
    if (2 != sscanf(sLine.c_str(), "%d %d", &nCommands, &nCapability)) {
        return -1;
    }

    LRUCache cache(nCapability);
    for (size_t i(0); i < nCommands; i++) {
        std::getline(std::cin, sLine);
        std::string_view svLine = sLine;
        if (svLine.find("get") == 0) {
            size_t posEnd;
            const auto nNumber = get_number(svLine, 3, posEnd);
            std::cout << cache.get(static_cast<Key>(nNumber)) << "\r\n";

        } else if (svLine.find("set") == 0) {
            size_t posEnd;
            const auto nKey = get_number(svLine, 3, posEnd);
            const auto nValue = get_number(svLine, posEnd, posEnd);
            cache.set(static_cast<Key>(nKey), static_cast<Value>(nValue));

        } else {
            std::cout << "Something wrong!\r\n";
        }
    }

    return 0;
}
