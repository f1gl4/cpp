#include "tasks.h"

Tree::Tree(int value)
{
    this->value = std::make_shared<BigData>(value);
}

Tree::Tree(std::shared_ptr<BigData> value)
{
    this->value = std::move(value);
}

Tree* Tree::get_parent() const
{
    return this->parent;
}

bool Tree::has_parent() const
{
    return parent != nullptr;
}

Tree* Tree::get_left_child() const
{
    return left.get();
}

Tree* Tree::get_right_child() const
{
    return right.get();
}

Tree* Tree::get_root()
{
    Tree* cur = this;
    while (cur->parent)
    {
        cur = cur->parent;
    }
    return cur;
}
std::unique_ptr<Tree> Tree::take_left_child()
{
    auto prevLeft = std::move(this->left);

    if (prevLeft)
    {
        prevLeft->parent = nullptr;
    }
    return prevLeft;
}

std::unique_ptr<Tree> Tree::take_right_child()
{
    auto prevRight = std::move(this->right);

    if (prevRight)
    {
        prevRight->parent = nullptr;
    }
    return prevRight;
}

std::unique_ptr<Tree> Tree::take_child(Tree& child)
{
    if (this->left.get() == &child)
    {
        return this->take_left_child();
    }
    if (this->right.get() == &child)
    {
        return this->take_right_child();
    }

    throw std::runtime_error("error child");
}

std::unique_ptr<Tree> Tree::set_left_child(std::unique_ptr<Tree> newChild)
{
    auto prevLeft = std::move(this->left);

    if (newChild)
    {
        newChild->parent = this;
    }
    this->left = std::move(newChild);
    return prevLeft;
}
std::unique_ptr<Tree> Tree::set_right_child(std::unique_ptr<Tree> newChild)
{
    auto prevRight = std::move(this->right);

    if (newChild)
    {
        newChild->parent = this;
    }
    this->right = std::move(newChild);
    return prevRight;
}

void Tree::swap_children()
{
    std::swap(this->left, this->right);
}

bool Tree::is_same_tree_as(Tree* other)
{
    return this->get_root() == other->get_root();
}

void Tree::replace_value(const std::shared_ptr<BigData>& newValue)
{
    this->value = newValue;

    if (this->left)
    {
        this->left->replace_value(newValue);
    }
    if (this->right)
    {
        this->right->replace_value(newValue);
    }
}

std::shared_ptr<BigData> Tree::get_value() const
{
    return this->value;
}