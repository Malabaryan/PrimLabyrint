#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>

template <typename E>
class Node
{
public:
    E element;
    Node* next;

    Node(E pElement, Node* pNext = NULL)
    {
        element = pElement;
        next = pNext;
    }

    Node(Node* pNext = NULL)
    {
        next = pNext;
    }

	E getValue()
    {
        return element;
    }


};

#endif // NODE_H
