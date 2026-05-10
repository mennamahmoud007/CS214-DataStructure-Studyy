#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct DNode
{
    T value;
    DNode<T> *next;
    DNode<T> *back;
};
template <class T>
class doublyLinkedList
{
protected:
    int count;
    DNode<T> *first;
    DNode<T> *last;

public:
    doublyLinkedList()
    {
        first = last = NULL;
        count = 0;
    }
    void reverse() const
    {
        DNode<T> *current = last;
        cout << "List reversed elements: ";
        while (current != NULL)
        {
            cout << current->value << " ";
            current = current->back;
        }
        cout << endl;
    }
};