#pragma once
#include "Node.h"
#include "Iterator.h"
#include <iostream>
using namespace std;
template <typename T>

class LinkedList
{
    Node<T> *head;
    Node<T> *tail;

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    Iterator<T> begin()
    {
        return Iterator<T>(head);
    }
    Iterator<T> end()
    {
        return Iterator<T>(nullptr);
    }

    void insertAtHead(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            Node<T> *temp = head;
            head = newNode;
            head->next = temp;
        }
    }
    void insertAtTail(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
            // tail->next = head;
        }
    }

    void insertAtMiddle(T value)
    {
        int start = 0;
        int end = size();
        int middle = start + ((end - start) / 2);
        Node<T> *ptr = head;
        Node<T> *newNode = new Node<T>(value);
        while (middle-- > 0)
        {
            ptr = ptr->next;
        }

        newNode->next = ptr->next;
        ptr->next = newNode;
    }
    void insertAfter(T value, T newValue)
    {
        Node<T> *temp = search(value);
        Node<T> *newNode = new Node<T>(newValue);
        if (temp == tail)
        {
            tail->next = newNode;
            tail = newNode;
        }
        if (temp != nullptr)
        {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    bool isEmpty()
    {
        if (head == nullptr)
        {
            return true;
        }
        return false;
    }
    void insertBefore(T value, T newValue)
    {
        Node<T> *temp = search(value);
        Node<T> *temp1;
        Node<T> *newNode = new Node<T>(newValue);
        if (temp == head)
        {
            head = newNode;
            newNode->next = temp;
        }
        else
        {

            Node<T> *prevNode = previousNode(head, temp);
            prevNode->next = newNode;
            newNode->next = temp;
        }
    }

    Node<T> *search(T value)
    {
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            if (temp->data == value)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void display()
    {
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << "-->";
            temp = temp->next;
        }
        cout << "Null";
    }

    void recursive_display(Node<T> *head)
    {
        if (head == nullptr)
            return;
        cout << head->data << "-->";
        recursive_display(head->next);
    }

    void recursive_reverse_display(Node<T> *head)
    {
        if (head != nullptr)
        {
            recursive_reverse_display(head->next);
            cout << head->data << "-->";
        }
    }

    bool check_circular()
    {
        // return li.getTail()->next == li.getHead() ? true : false;

        if (tail->next == head)
        {
            cout << head->data;
            return true;
        }
        return false;
    }

    void deleteTail()
    {
        Node<T> *temp = previousNode(head, tail);
        temp->next = nullptr;
        tail = temp;
    }

    Node<T> *deleteHead()
    {
        Node<T> *temp = head;
        head = head->next;
        return temp;
    }

    void deleteMiddle()
    {
        int middle = size() / 2;
        Node<T> *temp = getNode(middle);
        Node<T> *prev = previousNode(head, temp);
        prev->next = temp->next;
    }

    Node<T> *reverseUsingHead(Node<T> *head)
    {
        Node<T> *temp = head;
        Node<T> *prev = nullptr;
        Node<T> *next = nullptr;
        while (temp != nullptr)
        {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        return prev;
    }

    bool isPlagro(Node<T> *head)
    {
        Node<T> *reverseList = reverseUsingHead(head);
        Node<T> *cur = head;
        bool flag = false;

        while (cur != nullptr)
        {
            if (cur->data == reverseList->data)
                flag = true;
            else
                flag = false;
            cur = cur->next;
            reverseList = reverseList->next;
        }
        return flag;
    }
    Node<T> *getNode(int index)
    {
        Node<T> *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp;
    }

    void deleteByValue(T value)
    {
        Node<T> *temp = search(value);
        if (temp != nullptr)
        {
            Node<T> *prev = previousNode(head, temp);
            prev->next = temp->next;
        }
    }

    Node<T> *getHead()
    {
        return head;
    }

    Node<T> *getTail()
    {
        return tail;
    }

    void setHead(Node<T> *head)
    {
        this->head = head;
    }
    void setTail(Node<T> *tail)
    {
        this->tail = tail;
    }
    int size()
    {
        Node<T> *temp = head;
        int count = 0;
        while (temp != nullptr)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }
    Node<T> *reverseBetween(Node<T> *head, int left, int right)
    {
        Node<T> *nextNode = NULL;
        Node<T> *prevNode = NULL;
        if (head != NULL)
        {
            Node<T> *curNode = _getNode(left, head);
            while (left <= right)
            {
                nextNode = curNode->next;
                curNode->next = prevNode;
                prevNode = curNode;
                curNode = prevNode;
                left++;
            }
        }
        return prevNode;
    }

    Node<T> *_getNode(int index, Node<T> *head)
    {
        while (index-- > 1)
        {
            head = head->next;
        }
        return head;
    }

private:
    Node<T> *previousNode(Node<T> *start, Node<T> *target)
    {
        if (start == nullptr || start->next == nullptr)
            return nullptr;
        else if (start->next == target)
            return start;
        return previousNode(start->next, target);
    }
};
