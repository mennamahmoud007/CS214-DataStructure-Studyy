#include <iostream>
using namespace std;
// Implement a queue of integers using an array. The queue should have the following member functions:

// ======================================================
// ======================= IntQueue ======================
// ======================================================
class IntQueue
{
private:
    int *queueArray; // Points to the queue array
    int queueSize;   // The queue size
    int front;       // Subscript of the queue front
    int rear;        // Subscript of the queue rear
    int count;       // Number of items in the queue

public:
    IntQueue(int s)
    {
        if (s <= 0)
            queueSize = 100;
        else
            queueSize = s;

        front = 0;
        queueArray = new int[queueSize];
        rear = queueSize - 1;
        count = 0;
    }

    ~IntQueue()
    {
        delete[] queueArray;
    }
    bool isEmpty() const
    { // time complexity O(1)
        return (count == 0);
        // return (front == -1); // alternative way
    }

    bool isFull() const
    { // time complexity O(1)
        return (count == queueSize);
    }

    void enqueue(int num)
    { // time complexity O(1)
        if (isFull())
            cout << "The queue is full.\n";

        else if (isEmpty())
        {
            front = rear = 0;
            queueArray[rear] = num;
            count++;
        }
        else
        {
            rear = (rear + 1) % queueSize;
            queueArray[rear] = num;
            count++;
        }
    }
    void dequeue(int &num)
    { // time complexity O(1)
        if (isEmpty())
            cout << "The queue is empty.\n";
        else
        {

            num = queueArray[front];
            front = (front + 1) % queueSize;
            count--;
        }
    }
    void clear()
    { // time complexity O(1)
        front = queueSize - 1;
        rear = queueSize - 1;
        count = 0;
    }

    void print()
    { // time complexity O(n)
        cout << "\nQueue contents:\n";
        if (!isEmpty())
        {
            int tempCount = 0;
            size_t i = front;
            while (tempCount < count)
            {
                cout << queueArray[i] << " ";
                i = (i + 1) % queueSize;
                tempCount++;
            }
            cout << endl;
        }
        else
            cout << "Empty Queue";
    }

    int peekFront() // returns the front value without removing it
    {               // time complexity O(1)
        if (isEmpty())
        {
            cout << "The queue is empty.\n";
            return -1; // or throw an exception
        }
        else
        {
            return queueArray[front];
        }
    }
    int peekRear() // returns the rear value without removing it
    {              // time complexity O(1)
        if (isEmpty())
        {
            cout << "The queue is empty.\n";
            return -1; // or throw an exception
        }
        else
        {
            return queueArray[rear];
        }
    }
    int countItems() // returns the number of items in the queue
    // time complexity O(1)
    {
        return count;
    }

    //[4] search
    // time complexity O(n)
    bool search(int value)
    {
        if (isEmpty())
            return false;

        int tempCount = 0;
        size_t i = front;
        while (tempCount < count)
        {
            if (queueArray[i] == value)
                return true;
            i = (i + 1) % queueSize;
            tempCount++;
        }
        return false;
    }

    int searchIndex(int value) // returns the index of the first occurrence of the value, or -1 if not found
    {                          // time complexity O(n)
        int pos = -1;
        if (!isEmpty())
        {
            for (int i = front; i != rear; i = (i + 1) % queueSize)
                if (queueArray[i] == value)
                {
                    pos = i;
                    break;
                }
            if (pos == -1)
            {
                if (queueArray[rear] == value)
                    pos = rear;
            }
        }
        else
            cout << "Q is empty! " << endl;
        return pos;
    }

    void displayMiddle()
    { // time complexity O(1)
        if (isEmpty())
        {
            cout << "The queue is empty.\n";
        }
        else
        {
            int middleIndex = (front + count / 2) % queueSize;
            cout << "Middle element: " << queueArray[middleIndex] << endl;
        }
    }
};
// ======================================================
// ===================== linkedQueue =====================
template<class t>
class linkedQueue
{
private:
	struct Node
	{
		t item;
		Node *next;
	};
	int length;
	Node *frontPtr, *rearPtr;

public:
	
linkedQueue():frontPtr(NULL), rearPtr(NULL), length(0)
	{}
	bool isEmpty()
	{
		return (length == 0);
	}

	void dequeue()
	{
		if (isEmpty())
			cout << "Empty Queue" << endl;
		else if (length == 1)
		{
			delete frontPtr;
			rearPtr = NULL;
			length = 0;
		}
		else
		{
			Node *current = frontPtr;
			frontPtr = frontPtr->next;
			delete current;//free(current)
			length--;
		}
	}

	void enqueue(t item)
	{
		Node *newNode = new Node;
		newNode->item = item;
		newNode->next = NULL;

		if (length == 0)
			rearPtr = frontPtr = newNode;
		else
		{
			rearPtr->next = newNode;
			rearPtr = newNode;
		}
		length++;
	}

	t front()
	{
		assert(!isEmpty());
		return frontPtr->item;
	}

	t rear()
	{
		assert(!isEmpty());
		return rearPtr->item;
	}

	void clearQueue()
	{
		Node *current;

		while (frontPtr != NULL)
		{
			current = frontPtr;
			frontPtr = frontPtr->next;
			delete current;
		}
		rearPtr = NULL;
		length = 0;
	}
	void display()
	{
		Node*cur = frontPtr;
		cout << "Item in the queue :[ ";
		while (cur!=NULL)
		{
			cout << cur->item<<" ";
			cur = cur->next;
		}cout << "]" << endl;
	}

	void search(t item)
	{
		Node*cur = frontPtr;
		bool flag = true;
		while (cur != NULL)
		{
			if (cur->item == item)
			{
				cout << "the item :" << item << " found" << endl;
				flag = false;
				break;
			}
			cur = cur->next;
		}
		if(flag)
			cout << "the item : " << item << " not found" << endl;

	}

};


// ======================================================
// ========================= MAIN ========================
// ======================================================

int main()
{
    cout << "\n-------------- Queue --------------\n";

    IntQueue queue(5);
    int qval;
    int outVal;

    cout << "\nPlease enter int values to enqueue into the queue (-1 to stop):\n";
    cin >> qval;
    while (qval != -1)
    {
        queue.enqueue(qval);
        cin >> qval;
    }

    queue.print();

    cout << "\n .............. Lab Requirements of Queue .............\n";
    cout << "\n Check code of Queue and write the required member functions";
    cout << "\n Then test these functions by calling them from the main()\n";
    queue.displayMiddle();


    return 0;
}
