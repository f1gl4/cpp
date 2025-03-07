#include "tasks.h"


//UTF8String(const std::string& str); // constructor string

//UTF8String(const char* str);

//UTF8String(const std::vector<CodePoint>& codepoints); // constructor codepoints vector

UTF8String::UTF8String(const UTF8String& other)
{
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->data_ = new uint8_t[this->capacity_];
    std::copy(other.data_, other.data_ + other.size_, this->data_);
}

//UTF8String::UTF8String& operator=(const UTF8String& other); // copy assignm

UTF8String::~UTF8String()
{
    delete[] this->data_;
}

bool UTF8String::operator==(const UTF8String &other) const
{
    return std::equal(this->data_, this->data_ + this->size_, other.data_, other.data_ + other.size_);
}

UTF8String::operator std::string() const
{
    return std::string(reinterpret_cast<const char*>(this->data_), this->size_);
}


std::size_t UTF8String::get_byte_count() const 
{
    return this->size_;
}