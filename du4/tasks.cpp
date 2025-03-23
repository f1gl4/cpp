#include "tasks.h"

const Value* Value::operator[](const size_t) const
{
    throw std::runtime_error("error");
}

const Value* Value::operator[](const std::string&) const
{
    throw std::runtime_error("error");
}


Integer::Integer(int value) : value(value) { }

int Integer::get_value() const 
{
    return this->value;
}

Value* Integer::clone() const
{
    return new Integer(this->value);
}

void Integer::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


Value* Null::clone() const
{
    return new Null(*this);
}

void Null::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


Array::Array(std::vector<Value*> values) : values(std::move(values)) { }

Array::~Array()
{
    for (auto v : this->values)
    {
        delete v;
    }
}

Value* Array::operator[](size_t index) const
{
    if (index >= this->values.size()) return nullptr;

    return this->values[index];
}

void Array::append(Value* value)
{
    values.push_back(value);
}

void Array::remove(size_t index)
{
    if (index < values.size())
    {
        delete this->values[index];
        this->values.erase(this->values.begin() + index);
    }
}

size_t Array::size() const
{
    return values.size();
}

Value* Array::clone() const
{
    Array* newArr = new Array();
    newArr->values.reserve(this->values.size());

    for (auto v : values)
    {
        newArr->values.push_back(v->clone());
    }
    return newArr;
}

void Array::accept(Visitor& visitor)
{
    visitor.visit(*this);
}


Object::Object(std::unordered_map<std::string, Value*> dict)
{
    this->dictionary = std::move(dict);
}

Object::~Object()
{
    for (auto d : dictionary)
    {
        delete d.second;
    }
}

Value* Object::operator[](const std::string& key) const
{
    auto it = dictionary.find(key);

    if (it == dictionary.end()) return nullptr;

    return it->second;
}

std::vector<std::string> Object::keys() const
{
    std::vector<std::string> res;
    res.reserve(dictionary.size());

    for (auto& [key, _] : dictionary)
    {
        res.push_back(key);
    }
    std::sort(res.begin(), res.end());

    return res;
}

void Object::insert(const std::string& key, Value* value)
{
    auto it = dictionary.find(key);

    if (it != dictionary.end())
    {
        delete it->second;
    }

    dictionary[key] = value;
}

void Object::remove(const std::string& key)
{
    delete this->operator[](key);
    this->dictionary.erase(this->dictionary.find(key));
}

size_t Object::size() const
{
    return this->dictionary.size();
}

Value* Object::clone() const
{
    Object* newObj = new Object();
    newObj->dictionary.reserve(this->dictionary.size());

    for (auto& [key, v] : dictionary)
    {
        newObj->dictionary[key] = v->clone();
    }
    return newObj;
}

void Object::accept(Visitor& visitor)
{
    visitor.visit(*this);
}