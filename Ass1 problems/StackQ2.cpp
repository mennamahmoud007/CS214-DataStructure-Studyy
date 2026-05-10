#include <iostream>
#include <string>
using namespace std;
/*Question2:  Given a circular integer array nums (i.e., the next element of 
nums[nums.length - 1] is nums[0]), return the next greater number for every element in 
nums. 
The next greater number of a number x is the first greater number to its traversing-order 
next in the array, which means you could search circularly to find its next greater 
number. If it doesn't exist, return -1 for this number. 
Example 1: 
Input: nums = [1,2,1] 
Output: [2,-1,2] 
Explanation: The first 1's next greater number is 2;  
The number 2 can't find next greater number.  
The second 1's next greater number needs to search circularly, which is also 2. 
Example 2: 
Input: nums = [1,2,3,4,3] 
Output: [2,3,4,-1,4]*/
class CircularArray {
public:
    int size;
    int* arr;

    void create() {
        cin >> size;

        arr = new int[size];

        for(int i=0; i<size; i++) { //O(n)
            cin >> arr[i];
        }
    }

    void findnextBigInt() { //O(n**2) in worst case when all elements are the same and we have to loop through the whole array for each element

        for(int i=0; i<size; i++) { //O(n) for each element in the array

            int current = arr[i];
            int* searchPtr = arr + i;
            bool found = false;

            if(searchPtr == arr + size - 1)
                searchPtr = arr;
            else
                searchPtr++;

            while(searchPtr != arr+i) { //O(n) in worst case when all elements are the same and we have to loop through the whole array

                if(*searchPtr > current) {
                    cout << *searchPtr << " ";
                    found = true;
                    break;
                }

                if(searchPtr == arr + size - 1)
                    searchPtr = arr;
                else
                    searchPtr++;
            }

            if(!found)
                cout << -1 << " ";
        }
    }
};

int main() {

    CircularArray array; 

    array.create();
    array.findnextBigInt();
}
