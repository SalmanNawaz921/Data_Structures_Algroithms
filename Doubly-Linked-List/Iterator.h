#pragma once
#include "DoublyLinkedList.h"
#include "Node.h"

template <typename T>
class Iterator
{
private:
    Node<T> *current;

public:
    Iterator(Node<T> *node) : current(node){};

    Iterator &
    operator++()
    {
        if (current != nullptr)
            current = current->next;

        return *this;
    }
    Iterator &
    operator--()
    {
        if (current != nullptr)
            current = current->prev;
        return *this;
    }
    T &operator*()
    {
        return current->data;
    }
    bool operator!=(const Iterator &other)
    {
        return (current != other.current);
    }
};