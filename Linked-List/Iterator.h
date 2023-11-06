#pragma once
#include "Node.h"

template <typename T>
class Iterator
{

public:
    Iterator(Node<T> *node) : current(node){};

    T &operator*()
    {
        return current->data;
    }

    Iterator &operator++()
    {
        if (current != nullptr)
        {
            current = current->next;
        }
        return *this;
    }

    // Overload the equality operator to compare iterators
    bool operator==(Iterator &other)
    {
        return current == other.current;
    }

    // Overload the inequality operator to compare iterators
    bool operator!=(const Iterator &other)
    {
        return !(*this == other);
    }

private:
    Node<T> *current;
};