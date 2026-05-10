#include <iostream>
#include <string>
using namespace std;
/*Problem 3 : Search in bitonic array [3.5 marks] 
A Bitonic Array is an array that first monotonically increases and then monotonically decreases. 
The turning point is called the Bitonic Point.  
Example: [ 1,  4,  8,  12,  9,  6,  3 ] BITONIC POINT (value = 12) 
You are given an unsorted array. You are to first sort the array into bitonic form, where halves 
are sorted using bubblesort in the left half to sort values ascending and selection sort to sort 
values in the right half descending, then search for a target element using linear search. 
Requirements: 
•        Calculate and print the total number of comparisons and swaps performed during 
the sorting phase. 
•        Handle duplicate elements within the array. 
•        Write a main to test your function with at least 5 test cases, including: 
1.     Target at the bitonic point. 
2.     Target in the left half (ascending portion). 
3.     Target in the right half (descending portion). 
4.     Target not present in the array. 
5.     Array with duplicate elements.*/

class BitonicArray {
private:
    int* arr;
    int n;
    int swaps;
    int comp;

    void printArr() {
        for(int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

public:
    BitonicArray(int inputArr[], int size) {
        n = size;
        arr = new int[n];
        for(int i = 0; i < n; i++) {
            arr[i] = inputArr[i];
        }
        swaps = 0;
        comp = 0;
    }

    ~BitonicArray() {
        delete[] arr;
    }

    void solve() {
        swaps = 0;
        comp = 0;

        int indexBV = 0;
        int bv = arr[0];

        for(int i = 1; i < n; i++) { //o(n)
            comp++;
            if (arr[i] > bv) {
                bv = arr[i];
                indexBV = i;
            }
        }
        swap(arr[n/2], arr[indexBV]);
        swaps++;

        // Bubble sort (left half ascending) //O((n/2)**2) in worst case when the left half is sorted in descending order
        for(int i = 0; i < (n/2) - 1; i++) {
            for(int j = 0; j < (n/2) - i - 1; j++) {
                comp++;
                if (arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                    swaps++;
                }
            }
        }
        cout << endl;

        // Selection sort (right half descending) //O((n/2)**2) in worst case when the right half is sorted in ascending order
        for(int i = (n/2) + 1; i < n; i++) {
            int maxIdx = i;
            for (int j = i + 1; j < n; j++) {
                comp++;
                if (arr[j] > arr[maxIdx]) {
                    maxIdx = j;
                }
            }
            if(maxIdx != i) {
                swap(arr[i], arr[maxIdx]);
                swaps++;
            }
        }

        printArr();
        cout << "Swaps: " << swaps << " Comparisons: " << comp << endl;
        cout << endl;
    }

    void search(int target) { //O(n) in worst case when the target is not present in the array and we have to check all elements
        //o(1) if the target is found at the first index best case
        for(int i = 0; i < n; i++) {
            if(arr[i] == target) {
                cout << "Target " << target << " found at index " << i << endl;
                return;
            }
        }
        cout << "Target " << target << " not found" << endl;
    }
};

int main() {
    cout << "Test 1: Target at the Bitonic Point" << endl;
    int arr1[] = {3, 1, 9, 12, 8, 4, 6};
    BitonicArray b1(arr1, 7);
    b1.solve();
    b1.search(12);

    cout << " Test 2: Target in the Left Half" << endl;
    int arr2[] = {3, 6, 4, 9, 1, 12, 8};
    BitonicArray b2(arr2, 7);
    b2.solve();
    b2.search(3);

    cout << "Test 3: Target in the Right Half" << endl;
    int arr3[] = {12, 6, 9, 1, 8, 3, 4};
    BitonicArray b3(arr3, 7);
    b3.solve();
    b3.search(4);

    cout << "Test 4: Target not in the array" << endl;
    int arr4[] = {3, 1, 9, 12, 8, 4, 6};
    BitonicArray b4(arr4, 7);
    b4.solve();
    b4.search(99);

    cout << "Test 5: Array with Duplicate Elements" << endl;
    int arr5[] = {1, 2, 1, 2, 1, 2, 1};
    BitonicArray b5(arr5, 7);
    b5.solve();
    b5.search(2);
}