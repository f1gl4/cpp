#include "tasks.h"

// TODO: implement functions from tasks.h

Parser create_char_parser(char ch)
{
    return [ch](const char* input) -> const char*
    {
        if (std::strlen(input) == 0) return nullptr;

        if (*input == ch) return input + 1;

        return nullptr;
    };
}

Parser regex_match(const std::string& input)
{
    std::regex re("^" + input);
    return [re](const char* str) -> const char*
    {
        std::cmatch match;

        if (std::regex_search(str, match, re)) return str + match.length();

        return nullptr;
    };
}

Parser skip_ws()
{
    return [](const char* input) -> const char*
    {
        for (auto i = 0; i < std::strlen(input); i++)
        {
            if (std::isspace(input[i])) continue;

            return input + i;
        }

        return input + std::strlen(input);
    };
}

Parser any_of(const std::vector<Parser>& parsers)
{
    return [parsers](const char* input) -> const char*
    {
        for (const auto& parser : parsers)
        {
            const char* res = parser(input);
            if (res) return res;
        }
        return nullptr;
    };
}

Parser sequence(const std::vector<Parser>& parsers)
{
    return [parsers](const char* input) -> const char*
    {
        const char* cur = input;
        for (const auto& parser : parsers)
        {
            cur = parser(cur);
            if (!cur) return nullptr;
        }

        return cur;
    };
}

Parser repeat(const Parser& parser, int n)
{
    return [parser, n](const char* input) -> const char*
    {
        const char* cur = input;
        for (auto i = 0; i < n; i++)
        {
            cur = parser(cur);
            if (!cur) return nullptr;
        }
        return cur;
    };
}

Parser create_char_parser(const std::string& input)
{
    return [input](const char* str) -> const char*
    {
        std::vector<Parser> parsers;
        parsers.reserve(input.size());

        for (char ch : input)
        {
            parsers.push_back(create_char_parser(ch));
        }
        return sequence(parsers)(str);
    };
}