#pragma once
#include "DoublyLinkedList.h"
#include "Node.h"

template <typename T>
class ReverseIterator
{
private:
    Node<T> *current;

public:
    ReverseIterator(Node<T> *node) : current(node){};

    ReverseIterator &
    operator++()
    {
        if (current != nullptr)
            current = current->prev;

        return *this;
    }
    T &operator*()
    {
        return current->data;
    }
    bool operator!=(const ReverseIterator &other)
    {
        return (current != other.current);
    }
};