#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#pragma once

class Visitor;

class Value {
public:
    Value() = default;
    virtual ~Value() = default;

    virtual const Value* operator[](const size_t) const;
    virtual const Value* operator[](const std::string&) const;

    virtual Value* clone() const = 0;
    virtual void accept(Visitor& visitor) = 0;

};

class Integer : public Value
{
private:
    int value;

public:
    Integer(int value);
    ~Integer() = default;

    int get_value() const;

    Value* clone() const override;
    void accept(Visitor& visitor) override;
};


class Null : public Value
{
public:
    Null() = default;
    ~Null() = default;

    Value* clone() const override;
    void accept(Visitor& visitor) override;
};


class Array : public Value
{
private:
    std::vector<Value*> values;

public:
    Array() = default;
    Array(std::vector<Value*> values);
    ~Array();

    Value* operator[](size_t index) const override;

    void append(Value* value);
    void remove(const size_t index);
    size_t size() const;

    Value* clone() const override;
    void accept(Visitor& visitor) override;
};


class Object : public Value
{
private:
    std::unordered_map<std::string, Value*> dictionary;

public:
    Object() = default;
    Object(std::unordered_map<std::string, Value*> dict);
    ~Object();

    Value* operator[](const std::string& key) const override;

    std::vector<std::string> keys() const;
    void insert(const std::string& key, Value* value);
    void remove(const std::string& key);
    size_t size() const;

    Value* clone() const override;
    void accept(Visitor& visitor) override;
};


class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visit(Integer& value) = 0;
    virtual void visit(Array& value) = 0;
    virtual void visit(Null& value) = 0;
    virtual void visit(Object& value) = 0;
};


class RemoveNullVisitor : public Visitor
{
public:
    void visit(Integer& value) override;
    void visit(Array& value) override;
    void visit(Null& value) override;
    void visit(Object& value) override;
};