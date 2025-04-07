#pragma once

#include <memory>
#include <cstdint>
#include <iostream>

/// UTF-8 string (reuse your previous implementation and modify it)

using CodePoint = uint32_t;
class UTF8String;

/// Binary tree
// Big data that we cannot afford to copy
struct BigData {
    explicit BigData(int value): value(value) {}

    BigData(const BigData&) = delete;
    BigData& operator=(const BigData&) = delete;

    int value;
};

class Tree
{
private:
    std::shared_ptr<BigData> value;
    std::unique_ptr<Tree> left;
    std::unique_ptr<Tree> right;
    Tree* parent;

public:
    Tree(int value);
    Tree(std::shared_ptr<BigData> value);

    Tree* get_parent() const;
    bool has_parent() const;
    Tree* get_left_child() const;
    Tree* get_right_child() const;
    Tree* get_root();
    std::unique_ptr<Tree> take_left_child();
    std::unique_ptr<Tree> take_right_child();
    std::unique_ptr<Tree> take_child(Tree& child);
    std::unique_ptr<Tree> set_left_child(std::unique_ptr<Tree> newChild);
    std::unique_ptr<Tree> set_right_child(std::unique_ptr<Tree> newChild);
    void swap_children();
    bool is_same_tree_as(Tree* other);
    void replace_value(const std::shared_ptr<BigData>& newValue);
    std::shared_ptr<BigData> get_value() const;
};
