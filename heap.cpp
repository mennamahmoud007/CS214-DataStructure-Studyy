#include <iostream>
using namespace std;

class MaxHeap { //time complexity for insert, deleteRoot, getMax is o(log n) and for buildMaxHeap is o(n) and for heapSort is o(n log n)
public:
    int heap[100];//space complexity o(1) as we are using a fixed size array
    //if we were to use a dynamic array or vector, the space complexity would be o(n) where n is the number of elements in the heap
    int size;

    // Constructor
    MaxHeap() {
        size = 0;
    }

    // Get parent index
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Get left child index
    int leftChild(int i) {
        return (2 * i) + 1;
    }

    // Get right child index
    int rightChild(int i) {
        return (2 * i) + 2;
    }

    // Swap two values
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Insert into heap
    void insert(int value) { //o(log n)

        // Insert at end
        heap[size] = value;
        int current = size;
        size++;

        // Heapify up
        while (current > 0 && heap[current] > heap[parent(current)]) {

            swap(heap[current], heap[parent(current)]);

            current = parent(current);
        }
    }

    // Heapify down
    void heapify(int i) { //o(log n) = o(h) where h is the height of the heap, which is log n for a complete binary tree

        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        // Check left child
        if (left < size && heap[left] > heap[largest])
            largest = left;

        // Check right child
        if (right < size && heap[right] > heap[largest])
            largest = right;

        // If largest changed
        if (largest != i) {

            swap(heap[i], heap[largest]);

            heapify(largest);
        }
    }
    //build a max heap class with insert
    void buildMaxHeap(int arr[], int n) { //o(n) 

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
        /*or with insert*/ //o(n log n)
        /*
        for (int i = 0; i < n; i++) {
            insert(arr[i]);
        }
        */
    }

    // Delete root (extract max element)
    int deleteRoot() { //o(log n)

        if (size == 0) {
            cout << "Heap is empty\n";
            return;
        }
        int maxElement = heap[0];
        // Replace root with last element
        heap[0] = heap[size - 1];
        size--;
        // Restore heap property
        heapify(0);
        return maxElement;
    }

    // Get maximum element
    int getMax() { //o(1)

        if (size == 0) {
            cout << "Heap is empty\n";
            return -1;
        }

        return heap[0];
    }
    // Increase key
    void increaseKey(int index, int newValue) { //o(log n)

        if (newValue < heap[index]) {
            cout << "New value must be larger\n";
            return;
        }
        // update value
        heap[index] = newValue;
        // heapify up
        while (index > 0 &&
            heap[index] > heap[parent(index)]) {

            swap(heap[index], heap[parent(index)]);

            index = parent(index);
        }
    }
    //sort an array using heap sort
    void heapSort(int arr[], int n) { //o(n log n)

        buildMaxHeap(arr, n);

        for (int i = n - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            size--;
            heapify(0);
        }
    }
    // Print heap
    void printHeap() { //o(n)

        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }

        cout << endl;
    }

};

//priority queue using linked list vs priority queue using heap
// using linked list has o(n) time complexity for insertion and o(1) time complexity for deletion of the highest priority element,
//  using heap has o(log n) time complexity for both insertion and deletion of the highest priority element.
// Therefore, priority queue using heap is more efficient than priority queue using linked list for large datasets.
//1)linked list implementation of priority queue
struct Node {
    int data;
    int priority;
    Node* next;

    Node(int d, int p) : data(d), priority(p), next(nullptr) {}
}; 
class PriorityQueueLinkedList {
private:
    Node* head;
public:
    PriorityQueueLinkedList() : head(nullptr) {}
    void push(int data, int priority) { //o(n)
        Node* newNode = new Node(data, priority);
        if (!head || head->priority < priority) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next && temp->next->priority >= priority) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    void pop() { //o(1)
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    int top() { //o(1)
        if (head) {
            return head->data;
        }
        throw runtime_error("Priority Queue is empty");
    }
};
//2)heap implementation of priority queue
struct PriorityQueueHeap {
private:
    MaxHeap heap;
public:
    void push(int data, int priority) {
        heap.insert(data);
    }
    void pop() {
        heap.deleteRoot();
    }
    int top() {
        return heap.getMax();
    }
    int maximum() {
        return heap.getMax();
    }    
    int insert(int data, int priority) {
        heap.insert(data);
    }
    int extractMax() {
        return heap.deleteRoot();
    }
    void increaseKey(int index, int newValue) {
        heap.increaseKey(index, newValue);
    }    
    
};

//-------------------TESTING THE HEAP IMPLEMENTATION------------------

int main() {

    MaxHeap h;
    int n=sizeof(h.heap)/sizeof(h.heap[0]);

    // Insert elements
    h.insert(50);
    h.insert(30);
    h.insert(40);
    h.insert(10);
    h.insert(5);
    h.insert(60);

    cout << "Heap elements: ";
    h.printHeap();

    cout << "Maximum element: " << h.getMax() << endl;

    // Delete root
    h.deleteRoot();

    cout << "After deleting root: ";
    h.printHeap();

    cout << "Maximum element: " << h.getMax() << endl;

    return 0;
}