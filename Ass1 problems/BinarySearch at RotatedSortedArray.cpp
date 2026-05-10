#include <iostream>
using namespace std;

/*Problem 2 : Updated Binary Search [3.5 marks] 
Update the traditional binary search algorithm to search for an item in a Rotated Sorted Array.  
A rotated sorted array is an array that was originally sorted, but then some 
elements from the end were moved to the beginning. Each rotated sorted array 
has a Peak, that’s the element at which the rotation starts. For example: 
[5, 6, 7, 1, 2, 3, 4] 
       ↑ 
    PEAK (value = 7) 
Requirements: 
Update binary search algorithm [1.5 mark]  
Handle duplicate elements within the array. [0.5 mark]  
Calculate and print the total number of element-to-element comparisons 
performed during the search. [0.5 mark]  
State the complexity for best and worst cases. [0.5 mark]  
Write a main to test your function.[0.5 mark] */


/*
Time Complexity:

Best Case: O(1) → when target == arr[mid]
Average Case: O(log n) → when no duplicates (normal binary search)
Worst Case: O(n) → when duplicates exist

Space Complexity: O(1)
*/

//normal binary search
bool binarySearch(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] == target)
        {
            return true;
        }

        if (target < arr[mid])
        {
            right = mid - 1;
        }

        else
        {
            left = mid + 1;
        }
    }
    return false;
}
/*search in roteted sorted array*/
bool searchInRotatedSortedArray(int arr[], int left, int right, int target)
{
    int comparisons = 0;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        comparisons++;
        if (arr[mid] == target) //best case O(1)
        {
            cout << "Comparisons: " << comparisons << endl;
            return true;
        } 
        /*duplication*/
        if (arr[left] == arr[mid] && arr[mid] == arr[right]) 
        //o(n) in worst case when duplicates exist that it loops through the whole array 111111
        {
            left++; 
            right--;
            continue;
        }
        if (arr[left] <= arr[mid]) // Left half is sorted 5 6 7 | 1 2 3
        {//normal binary search on the left half
            if (target >= arr[left] && target < arr[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        else // Right half is sorted //normal binary search on the right half // 1 2 3 | 5 6 7
        {
            if (target > arr[mid] && target <= arr[right])
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }
    cout << "Comparisons: " << comparisons << endl;
    return false;
}
int main()
{
    int arr1[] = {5, 6, 7, 1, 2, 3, 4};
    cout << "Search 6: ";
    cout << (searchInRotatedSortedArray(arr1, 0, 6, 6) ? "Found" : "Not Found") << endl;

    /*element not found*/
    cout << "Search 8: ";
    cout << (searchInRotatedSortedArray(arr1, 0, 6, 8) ? "Found" : "Not Found") << endl;

    /*with duplication*/
    int arr2[] = {5, 5, 7, 1, 2, 5, 5};
    cout << "Search 7 (duplicates): ";
    cout << (searchInRotatedSortedArray(arr2, 0, 6, 7) ? "Found" : "Not Found") << endl;

    /*without roteted*/
    int arr3[] = {1, 2, 3, 4, 5};
    cout << "Search 3 (not rotated): ";
    cout << (searchInRotatedSortedArray(arr3, 0, 4, 3) ? "Found" : "Not Found") << endl;

    return 0;
}
