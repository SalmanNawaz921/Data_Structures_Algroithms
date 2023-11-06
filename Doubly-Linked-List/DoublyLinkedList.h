#pragma once

#include "Node.h"
#include "ReverseIterator.h"
#include "ForwardIterator.h"
#include "Iterator.h"
#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    };
    ReverseIterator<T> rBegin() { return ReverseIterator<T>(tail); };
    ReverseIterator<T> rEnd() { return ReverseIterator<T>(nullptr); };
    ForwardIterator<T> fBegin() { return ForwardIterator<T>(head); };
    ForwardIterator<T> fEnd() { return ForwardIterator<T>(nullptr); };
    Iterator<T> begin() { return Iterator<T>(head); };
    Iterator<T> end() { return Iterator<T>(nullptr); };
    Node<T> *getHead() { return head; };
    void setHead(Node<T> *head) { this->head = head; };
    Node<T> *getTail() { return tail; };
    void setTail(Node<T> *tail) { this.tail = tail; };
    bool isEmpty() { return head == nullptr; };

    void insertAtFront(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (!isEmpty())
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        else
        {
            head = newNode;
            tail = newNode;
        }
    }

    void insertAtTail(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (!isEmpty())
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else
        {
            head = newNode;
            tail = newNode;
        }
    }

    void insertAtBefore(Node<T> *currNode, T value)
    {
        Node<T> *newNode = new Node<T>(value);
        currNode->prev->next = newNode;
        newNode->prev = currNode->prev;
        currNode->prev = newNode;
        newNode->next = currNode;
    }
    void insertAtAfter(Node<T> *currNode, T value)
    {
        Node<T> *newNode = new Node<T>(value);
        newNode->next = currNode->next;
        currNode->next = newNode;
        newNode->prev = currNode;
    }

    void removeHead()
    {
        if (!isEmpty())
            head = head->next;
    }
    void removeTail()
    {
        if (!isEmpty())
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
    }

    void removeAt(int index)
    {
        if (index == 0)
        {
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node<T> *nodeToRemove = getNode(index);

        if (nodeToRemove->next != nullptr)
        {
            nodeToRemove->prev->next = nodeToRemove->next;
            nodeToRemove->next->prev = nodeToRemove->prev;
        }
        else
        {
            nodeToRemove->prev->next = nullptr;
        }
    }
    void splice(Node<T> *node, DoublyLinkedList<T> listToMerge)
    {
        listToMerge.getTail()->next = node->next;
        node->next = listToMerge.getHead();
        listToMerge.getHead()->prev = node;
    }

    void display()
    {
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << "-->";
            temp = temp->next;
        }
    }

    Node<T> *reverseLinkedList(Node<T> *head)
    {
        Node<T> *temp = head;
        Node<T> *prev = nullptr;

        while (temp != nullptr)
        {
            prev = temp->prev;
            temp->prev = temp->next;
            temp->next = prev;
            temp = temp->prev;
        }

        // head = prev; // Update the new head if necessary
        return prev->prev;
    }

    Node<T> *getNode(int index)
    {
        Node<T> *node = head;
        while (index-- > 0)
        {
            node = node->next;
        }
        return node;
    }
};
