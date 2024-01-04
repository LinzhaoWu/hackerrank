#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <memory>
#include <stack>
#include <sstream>


class Tag
{
public:
    Tag(std::string name);
    ~Tag();

    void AddChild(std::string_view name);
    Tag* GetChild(std::string_view name);

    std::string_view GetName();

    void AddAttribute(std::string_view sName, std::string_view sValue);
    std::string_view GetAttribute(std::string_view sName);

private:
    std::string m_name;
    std::vector<std::string_view> m_children;
    std::unordered_map<std::string, std::string> m_attributes;
};

Tag::Tag(std::string name)
: m_name(name)
{
}

Tag::~Tag()
{
}

class TagRepository
{
public:
    static Tag* GetTag(std::string_view name);
    static void AddTag(std::string_view name);

private:
    inline static std::unordered_map<std::string, Tag> m_mapTags = {};
};

void Tag::AddChild(std::string_view nameChild)
{
    m_children.push_back(nameChild);
    TagRepository::AddTag(nameChild);
}

Tag* Tag::GetChild(std::string_view name)
{
    const auto it = std::find_if(m_children.cbegin(), m_children.cend(), 
        [&name](const auto& svChildName) {
            return svChildName.compare(name) == 0;
        });

    if (m_children.cend() == it) return nullptr; // If it doesn't have this child, return nullptr
    else return TagRepository::GetTag(name);
}

std::string_view Tag::GetName()
{
    return std::string_view(m_name.c_str());
}

void Tag::AddAttribute(std::string_view sName, std::string_view sValue)
{
    m_attributes[std::string(sName)] = std::string(sValue);
}

std::string_view Tag::GetAttribute(std::string_view sName)
{
    return m_attributes.at(std::string(sName));
}

enum class TagStatus {
    TAG_HEAD,
    TAG_TAIL
};

TagStatus GetLineTag(std::string_view line, std::string& nameTag, std::size_t& posEnd)
{
    if (line.starts_with("<")) {
        const auto pos = line.find(' ');
        if (std::string_view::npos != pos)
        {
            nameTag = line.substr(1, pos - 1);
            posEnd = pos;
        }
        return TagStatus::TAG_HEAD;

    } else if (line.starts_with("</")) {
        return TagStatus::TAG_TAIL;
    }

    std::cout << "Something is Wrong!" << std::endl;
    return TagStatus::TAG_TAIL;
}

void ReadAttributes(std::string_view svLine, Tag* pTagCurrent, std::size_t& posStart)
{
    const std::string_view svDelimiters = " =\"";

    const auto posKeyStart = svLine.find_first_not_of(svDelimiters, posStart);
    if (svLine[posKeyStart] == '>') return;
    const auto posKeyEnd = svLine.find_first_of(svDelimiters, posKeyStart);
    const auto svKey = svLine.substr(posKeyStart, posKeyEnd - posKeyStart);

    const auto posValueStart = svLine.find_first_not_of(svDelimiters, posKeyEnd);
    const auto posValueEnd = svLine.find_first_of(svDelimiters, posKeyStart);
    const auto svValue = svLine.substr(posValueStart, posValueEnd - posValueStart);

    pTagCurrent->AddAttribute(svKey, svValue);
    posStart = posValueEnd;
}

uint32_t AnalyseQuery(Tag& tagRoot, std::string_view svLine)
{
    const std::string_view svDelimiters = ".~";
    const auto svTagConnector = '.';
    const auto svAttrConnector = '~';

    std::size_t posStart = 0;
    Tag* pTagCurrent = &tagRoot;

    for (std::size_t posEnd = svLine.find_first_of(svDelimiters, posStart); 
         posEnd != std::string_view::npos; 
         posStart = posEnd) {
        const auto svTagName = svLine.substr(posStart, posEnd - posStart);
        pTagCurrent = pTagCurrent->GetChild(svTagName);
        if (pTagCurrent == nullptr) {
            std::cout << "Not Found!" << std::endl;
            return 1;
        }

        posEnd = svLine.find_first_of(svDelimiters, posStart);
    }

    const std::string_view svAttr = svLine.substr(posStart, svLine.size() - posStart);
    std::cout << pTagCurrent->GetAttribute(svAttr) << std::endl;
    return 0;
}

#define TEST
#ifdef TEST
std::string TEST_INPUT = "4 3\n<tag1 value = \"HelloWorld\">\n <tag2 name = \"Name1\">\n </tag2>\n </tag1>\n tag1.tag2~name\n tag1~name\n tag1~value";
#endif

int main() {
    #ifdef TEST
    std::istringstream iss(TEST_INPUT);
    #endif

    std::string sLine;
    #ifdef TEST
    std::getline(iss, sLine);
    #else
    std::getline(std::cin, sLine);
    #endif

    uint32_t nAttribute, nQuery;
    if (2 != sscanf_s(sLine.c_str(), "%d %d", &nAttribute, &nQuery)) {
        return -1;
    }

    Tag root("root");
    std::stack<std::string> stackTagNames;
    stackTagNames.push(std::string(root.GetName()));

    for (uint32_t i(0); i < nAttribute; i++) {
        #ifdef TEST
        std::getline(iss, sLine);
        #else
        std::getline(std::cin, sLine);
        #endif
        std::string sTag;
        std::size_t pos;

        if (TagStatus::TAG_HEAD == GetLineTag(sLine, sTag, pos)) {
            const auto pTagParent = TagRepository::GetTag(stackTagNames.top());
            pTagParent->AddChild(sTag);
            stackTagNames.push(sTag);

            const auto pTagCurrent = TagRepository::GetTag(sTag);
            while (std::string_view::npos != pos) {
                ReadAttributes(sLine, pTagCurrent, pos);
            }
        } else {
            stackTagNames.pop();
        }
    }

    if (!stackTagNames.empty()) {
        std::cout << "Something is wrong!";
        return -1;
    }

    for (uint32_t i(0); i < nQuery; i++) {
        #ifdef TEST
        std::getline(iss, sLine);
        #else
        std::getline(std::cin, sLine);
        #endif
        AnalyseQuery(root, sLine);
    }

    return 0;
}

Tag *TagRepository::GetTag(std::string_view svName)
{
    auto sName = std::string(svName);
    if (!TagRepository::m_mapTags.contains(sName)) {
        return nullptr;
    } 

    return &m_mapTags.at(sName);
}

void TagRepository::AddTag(std::string_view name)
{
    m_mapTags.emplace(std::string(name), std::string(name));
}
