#include <functional>
#include <cstring>
#include <vector>
#include <iostream>
#include <regex>

using Parser = std::function<const char*(const char*)>;

Parser create_char_parser(char ch);

Parser regex_match(const std::string& input);

Parser skip_ws();

Parser any_of(const std::vector<Parser>& parsers);

Parser sequence(const std::vector<Parser>& parsers);

Parser repeat(const Parser& parser, int n);

Parser create_word_parser(const std::string& input);