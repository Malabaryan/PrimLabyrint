#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <stdexcept>
#include "Node.h"

using namespace std;

template <typename E>
class LinkedQueue
{
private:
    Node<E>* front;
    Node<E>* rear;
    int size;

public:
    LinkedQueue()
    {
        front = rear = new Node<E>();
        size = 0;
    }
    ~LinkedQueue()
    {
        clear();
        delete front;
    }
    void clear()
    {
        while(size--){
            dequeue();
        }

    }
    void enqueue(E pElement)
    {
        rear->next = new Node<E>(pElement, rear->next);
        rear = rear->next;
        size++;

    }
    E dequeue() throw(runtime_error)
    {
        Node<E>* ele = front;
        front = front->next;
        size--;
        return ele->element;
    }
    E frontValue() throw(runtime_error)
    {
        if (front->next == NULL)
        {
            throw runtime_error("Queue is empty.");
        }
        return front->next->element;
    }
    int getSize()
    {
        return size;
    }
};

#endif // LINKEDQUEUE_H
