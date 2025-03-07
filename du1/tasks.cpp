#include "tasks.h"

// TODO: implement functions from assignment.md

int math::fibonacci(int n)
{
    if (n == 0) return 0; 
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

std::string strutils::camel_to_snake(std::string input)
{
    std::string result;
    for (char ch : input)
    {
        if (isupper(ch)) {
            if (!result.empty()) {
                result += '_';
                result += tolower(ch);
            } else {
                result += tolower(ch);
            }
        } else {
            result += ch;
        }
    }
    return result;
}

bool strutils::parse_uint(std::string input, std::uint32_t &result)
{
    if (input.length() == 0) return false;

    std::uint32_t tmp = 0;

    for (char c : input)
    {
        int number = c - '0';

        if (number > 9 || number < 0) return false;

        if (tmp <= (UINT32_MAX - number) / 10) {
            tmp = tmp * 10 + number;
        } else { return false; }
    }

    result = tmp;
    return true;

}

bool strutils::validate_utf8(std::vector<std::uint8_t> input, size_t &result)
{
    int points = 0;
    std::uint8_t nextBytes = 0;
// 0b11000011, 0b10001101, 0b00001001
    for (std::uint8_t ch : input)
    {
        if (nextBytes > 0) {
            if (ch >> 6 != 0b10) return false;
            nextBytes--;
            if (nextBytes == 0) points++;
            continue;
        }

        if (ch >> 7 == 0b0) {
            points++;
        } else if (ch >> 5 == 0b110) { //2bit -> 1 next
            nextBytes = 1;
        } else if (ch >> 4 == 0b1110) { //3bit -> 2 next
            nextBytes = 2;
        } else if (ch >> 3 == 0b11110) { //4 bit -> 3 next
            nextBytes = 3;
        } else {
            return false;
        }
    }
    
    result = points;
    return true;
}