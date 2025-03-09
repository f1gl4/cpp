#pragma once

#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>
#include <cstring>

#include <optional>

using CodePoint = uint32_t;

class UTF8String {
public:
    UTF8String(); // constructor
    UTF8String(const std::string& str); // constructor string
    UTF8String(const std::vector<CodePoint>& codepoints); // constructor codepoints vector
    UTF8String(const UTF8String& other); // copy constructor
    UTF8String& operator=(const UTF8String& other); // copy assignm

    // operators
    UTF8String operator+(const UTF8String& other) const; // concatenate (new object return)
    UTF8String& operator+=(const UTF8String& other); // append (change cur object)
    bool operator==(const UTF8String &other) const; // equal
    operator std::string() const; // converted to std::string by explicit cast

    void append(char ch); // add new ascii chars
    void append(CodePoint codepointer); // new code points

    std::optional<CodePoint> ntn_code_point(int index) const; // indexed by code point
    std::optional<uint8_t> operator[](int index) const; // indexed by bytes

    std::size_t get_byte_count() const; // cur stored bytes
    std::size_t get_point_count() const; // cur stored code points


    ~UTF8String(); // destructor

private:
    uint8_t* data_;
    std::size_t size_;
    std::size_t capacity_;

    void addCapacity(std::size_t minCapacity);
};
