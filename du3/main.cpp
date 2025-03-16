#include "tasks.h"

int main() {

    auto parser = skip_ws();
    std::cout << parser(" 123") << std::endl;
    std::cout << parser("\n\t1   1") << std::endl;

    auto parserAny_of = any_of({create_char_parser('x'), create_char_parser('y')});
    std::cout << parserAny_of("yz") << std::endl;

    auto seqParser = sequence({
        create_char_parser('x'),
        any_of({ create_char_parser('y'), regex_match("\\d") }),
        create_char_parser('z')
    });
    std::cout << seqParser("xyzu") << std::endl;

    return 0;
}
