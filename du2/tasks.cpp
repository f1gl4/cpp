#include "tasks.h"

void UTF8String::addCapacity(std::size_t minCapacity)
{
    if (minCapacity <= capacity_) return;

    std::size_t newCap = (capacity_ == 0) ? 1 : capacity_;
    while (newCap < minCapacity)
    {
        newCap *= 2;
    }

    uint8_t* newData = new uint8_t[newCap];
    for (std::size_t i = 0; i < size_; i++) {
        newData[i] = data_[i];
    }

    delete[] data_;

    data_ = newData;
    capacity_ = newCap;
}

UTF8String::UTF8String(const std::string& str)
{
    size_ = str.size();
    capacity_ = size_;
    data_ = new uint8_t[capacity_];

    std::memcpy(data_, reinterpret_cast<const uint8_t*>(str.data()), size_);
}

//UTF8String(const std::vector<CodePoint>& codepoints); // constructor codepoints vector

UTF8String::UTF8String(const UTF8String& other)
{
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->data_ = new uint8_t[this->capacity_];
    std::copy(other.data_, other.data_ + other.size_, this->data_);
}

UTF8String& UTF8String::operator=(const UTF8String& other)
{
    if (this == &other) {
        return *this;
    }
    
    delete[] this->data_;

    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->data_ = new uint8_t[this->capacity_];
    std::copy(other.data_, other.data_ + other.size_, this->data_);

    return *this;
}

UTF8String::~UTF8String()
{
    delete[] this->data_;
}

UTF8String UTF8String::operator+(const UTF8String& other) const
{
    UTF8String result;
    result.addCapacity(size_ + other.size_);

    for (std::size_t i = 0; i < size_; ++i)
    {
        result.data_[i] = data_[i];
    }

    for (std::size_t i = 0; i < other.size_; ++i)
    {
        result.data_[size_ + i] = other.data_[i];
    }

    result.size_ = size_ + other.size_;

    return result;
}

UTF8String& UTF8String::operator+=(const UTF8String& other)
{
    addCapacity(size_ + other.size_);

    for (std::size_t i = 0; i < other.size_; ++i){
        data_[size_ + i] = other.data_[i];
    }
    size_ += other.size_;

    return *this;
}

bool UTF8String::operator==(const UTF8String &other) const
{
    return std::equal(this->data_, this->data_ + this->size_, other.data_, other.data_ + other.size_);
}

bool UTF8String::operator!=(const UTF8String &other) const
{
    return !(std::equal(this->data_, this->data_ + this->size_, other.data_, other.data_ + other.size_));
}

UTF8String::operator std::string() const
{
    return std::string(reinterpret_cast<const char*>(this->data_), this->size_);
}

void UTF8String::append(char ch)
{
    addCapacity(size_ + 1);

    data_[size_] = static_cast<uint8_t>(ch);
    ++size_;
}

//void append(CodePoint codepointer); // ???

//std::optional<CodePoint> ntn_code_point(int index) const; // indexed by code point

std::optional<uint8_t> UTF8String::operator[](int index) const
{
    if (index >= this->size_) {
        return std::nullopt;
    }
    return this->data_[index];
}

std::size_t UTF8String::get_byte_count() const 
{
    return this->size_;
}

//std::size_t get_point_count() const; // cur stored code points