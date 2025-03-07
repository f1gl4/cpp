#include "tasks.h"


int main() {

    std::cout << math::fibonacci(0) << std::endl;
    std::cout << math::fibonacci(5) << std::endl;
    std::cout << math::fibonacci(9) << std::endl;

    std::cout << strutils::camel_to_snake("helloWorld") << std::endl;
    std::cout << strutils::camel_to_snake("MyNameIs...") << std::endl;

    std::uint32_t result = 0;
    std::cout << strutils::parse_uint("hello", result) << std::endl;
    std::cout << strutils::parse_uint("999999999999999999", result) << std::endl;
    std::cout << strutils::parse_uint("4294967295", result) << std::endl;

    size_t res;
    //strutils::validate_utf8({0b00001100}, res);
    strutils::validate_utf8({0b11000011, 0b10001101, 0b00001001}, res);
    std::cout << res << std::endl;

    return 0;
}
