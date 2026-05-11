#include <iostream>
using namespace std;

class MaxHeap {
public:
    int heap[100];
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
    void insert(int value) {

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
    void heapify(int i) {

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

    // Delete root (max element)
    void deleteRoot() {

        if (size == 0) {
            cout << "Heap is empty\n";
            return;
        }

        // Replace root with last element
        heap[0] = heap[size - 1];

        size--;

        // Restore heap property
        heapify(0);
    }

    // Get maximum element
    int getMax() {

        if (size == 0) {
            cout << "Heap is empty\n";
            return -1;
        }

        return heap[0];
    }

    // Print heap
    void printHeap() {

        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }

        cout << endl;
    }
};

int main() {

    MaxHeap h;

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