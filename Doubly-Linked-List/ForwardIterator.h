#pragma once
#include "DoublyLinkedList.h"
#include "Node.h"

template <typename T>
class ForwardIterator
{
private:
    Node<T> *current;

public:
    ForwardIterator(Node<T> *node) : current(node){};

    ForwardIterator &
    operator++()
    {
        if (current != nullptr)
            current = current->next;

        return *this;
    }
    T &operator*()
    {
        return current->data;
    }
    bool operator!=(const ForwardIterator &other)
    {
        return (current != other.current);
    }
};