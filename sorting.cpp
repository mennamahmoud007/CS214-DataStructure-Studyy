#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------------
//1] Quadratic sorting algorithms: insertion, selection, bubble sorts
//---------------------------------------------------------------------------------
/*
1. Insertion sort: builds the sorted array one item at a time by repeatedly taking the next item and inserting it into the correct position in the already sorted part of the array.
2. Selection sort: repeatedly selects the smallest (or largest) element from the unsorted portion   
of the array and swaps it with the first unsorted element, effectively growing the sorted portion of the array.
3. Bubble sort: repeatedly steps through the list, compares adjacent elements and swaps them if they
are in the wrong order, until the entire array is sorted.

insertion sort is more efficient than selection and bubble sorts for small or partially sorted arrays, 
while selection and bubble sorts are generally less efficient for larger arrays due to their higher time complexity.
speed: insertion > selection > bubble

all of them are inplace, meaning they sort the array without requiring additional storage space (beyond a few temporary variables).
and are stable, meaning they maintain the relative order of equal elements in the sorted output.
*/

//-------------------------------------1) Insertion Sort------------------------------------------------------------
template <class T>                  //0  1  2  3
void insertion(T data[] , int n){  //80 |30 60 50
    for(int i=1 ;i<n;i++){
       int j;
       T tmp =data[i]; // 30

        for(j=i;j>0 && tmp < data[j-1];j--){ //j=1 --> j=0 //data[j]=80
            data[j]=data[j-1]; // data[1]=80 //movement
        }
        data[j]=tmp; // data[0]=30      //movement
    }
 }
 /*worst case: O(n^2) comparisons and movements when the input array is sorted in reverse order
 best case: O(n) comparisons and movements when the input array is already sorted
average case: O(n^2)comparisons and movements when the input array is in random order
 */

//-------------------------------------------2) selection sort---------------------------------------------------
template <class T>
void selection(T data[], int n){
     for (int i=0;i<n-1;i++){
        for (int j=i+1, least=i; j<n;j++){
            if (data[j]<data[least]){
                least=j;
            }
            swap(data[i],data[least]); //3 movements [tmp = data[i]; data[i] = data[least]; data[least] = tmp;]
        }
     }
/*every case O(n^2) comparisons and O(n) movements (swaps)
as it doesn't take advantage of already sorted elements (can't recognize them) as 
it always scans the entire unsorted portion of the array to find the minimum element, regardless of the initial order of the elements.
*/
}

//-------------------------------------------3) bubble sort-------------------------------------------------------
template <class T>
void bubble(T data[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=n-1;j>i;--j){
            if(data[j]<data[j-1]){
                swap(data[j],data[j-1]); //3 movements [tmp = data[j]; data[j] = data[j-1]; data[j-1] = tmp;]
            }
        }
    }
}
/*(best case) O(n) comparisons and O(1) movements (swaps) when the input array is already sorted.
(worst case) O(n^2) comparisons and O(n^2) movements (swaps) when the input array is sorted in reverse order,
average case O(n^2) comparisons and O(n^2) movements (swaps) when the input array is in random order.
*/

//-------------------------------------------------------------------------------------------------
//2] Divide and conquer sorting algorithms: merge and quick sorts
//-------------------------------------------------------------------------------------------------
/*
1. Merge sort: divides the array into two halves, recursively sorts each half, and then merges the sorted halves back together.
2. Quick sort: selects a 'pivot' element from the array and partitions the other elements into two sub-arrays according to whether
 they are less than or greater than the pivot, and then recursively applies the same process to the sub-arrays.

 while merge sort guarantees O(n log n) time complexity in all cases, quick sort has an average and best-case time complexity of O(n log n) 
 but can degrade to O(n^2) in the worst case (e.g., when the smallest or largest element is always chosen as the pivot).

 both of them are not inplace, meaning they require additional storage space to hold the temporary arrays during the sorting process.
 merge sort is stable, meaning it maintains the relative order of equal elements in the sorted output,
 while quick sort is not stable, as the relative order of equal elements may not be preserved due to the partitioning process.
 
 merge sort is often preferred for sorting linked lists and large datasets that do not fit into memory ==> optimal for external sorting,
 while quick sort is commonly used for in-memory sorting of arrays due to its lower constant factors and better cache performance.
 merge/heap = optimal 
*/

//------------------------------1) merge sort------------------------------------------------------
void merge(int arr[], int l, int m, int r)      
{
	int i=0, j=0, k=l;
    vector<int> L(arr, arr+m+1), R(arr+m+1, arr+r+1);    // 1.divide 
// Merge the temp arrays back into arr[l..r]
	while (i < L.size() && j < R.size()){
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++]; // 2.sort and merge
    }
    // 3. copy the remaining elements of L[] and R[], if there are any
	while (i < L.size())
	{
		arr[k++] = L[i++];
	}

	while (j < R.size())
	{
		arr[k++] = R[j++];
	}
} 

void mergeSort(int arr[], int l, int r) // l = 0, r = n-1 
{
	if (l < r)  //backtracking condition
	{
		int m =(l+r) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}
//time complexity: O(n log n) in all cases, as the array is always divided into two halves and each element is processed during the merge step.
//space complexity: O(n) due to the temporary arrays used for merging

//------------------------------2) Quick Sort------------------------------------------------------
int partition(int arr[], int left, int right) //o()
{
    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while (i <= j)
    {
        while (i <= right && arr[i] <= pivot) i++;
        while ( j>= left && arr[j] > pivot) j--;
        swap(arr[i], arr[j]);
    }
    swap(arr[left], arr[j]);
    return j;
}
void quickSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int middle = partition(arr, left, right);

		quickSort(arr, left, middle - 1);
		quickSort(arr, middle + 1, right);
	}
}
//time complexity: O(n log n) on average and in the best case,
// but can degrade to O(n^2) in the worst case (e.g., when the smallest or largest element is always chosen as the pivot)
//or when the input array is already sorted or reverse sorted, as it leads to unbalanced partitions and increased recursion depth.
//space complexity: O(log n) on average due to recursive calls,  auxiliary space O(1)

//-----------------------------------------------------------------------------------------------------------
//3] Linear time (non-comparison based)(address-based) sorting algorithms: counting, radix and bucket sorts 
//-----------------------------------------------------------------------------------------------------------
/* 1. Counting sort: counts the number of occurrences of each distinct element in the input array and uses
 this information to determine the position of each element in the sorted output.
2. Radix sort: sorts the input array by processing individual digits of the numbers,
 starting from the least significant digit to the most significant digit, 
 using a stable sorting algorithm (like counting sort) as a subroutine to sort the digits.
3. Bucket sort: distributes the elements of the input array into a number of buckets, sorts each bucket individually
 (using a different sorting algorithm (like insertion sort) or recursively applying the bucket sort),
 and then concatenates the sorted buckets to produce the final sorted array.     

 counting and radix sorts are efficient for sorting integers or fixed-length strings,
 while bucket sort is effective for sorting floating-point numbers uniformly distributed over a range.

all of them have a linear time complexity of o(n)
 O(n + k) for counting sort,
 O(d * (n + k)) for radix sort, and O(n + k) for bucket sort,
 where n is the number of elements in the input array, k is the range of the input values (for counting sort),
 and d is the number of digits in the largest number (for radix sort).
 
all of them are not inplace, as they require additional storage space for the auxiliary arrays used during the sorting process.
 counting and radix sorts are stable, while bucket sort can be either stable or unstable depending on the sorting algorithm used for sorting the individual buckets.

*/

//------------------------------1) counting sort------------------------------------------------------
int k=100; // maximum value in the input array
void countingSort(int A[], int B[], int n, int k)
{
    int C[100];  
    // 1. Initialize aux array //o(k)
    for (int i = 0; i <= k; i++)
        C[i] = 0;

//or int C[k+1] = {}; // this will initialize all elements to 0

    // 2. Count occurrences //o(n)
    for (int j = 0; j < n; j++)
        C[A[j]]++;

    // 3. Cumulative sums //o(k)
    for (int i = 1; i <= k; i++)
        C[i] += C[i - 1];

    // 4. Build sorted array //o(n)
    for (int j = n - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j]; 
        C[A[j]]--;
    }
}

//------------------------2) radix sort--------------------------------------------------------
void countByDigit(int arr[], int n, int exp) { 
  int out[n], cnt[10] = {}; 
  for (int i=0;i<n;i++) cnt[(arr[i]/exp)%10]++; 
  for (int i=1;i<10;i++) cnt[i]+=cnt[i-1]; 
  for (int i=n-1;i>=0;i--) out[--cnt[(arr[i]/exp)%10]] = arr[i]; 
  for (int i=0;i<n;i++) arr[i]=out[i]; 
} 
void radixSort(int arr[], int n) { 
  int mx = *max_element(arr, arr+n); 
  for (int exp=1; mx/exp>0; exp*=10) countByDigit(arr, n, exp); 
} 
//space complexity: O(n + k) due to the auxiliary arrays used for counting and output, 
//where n is the number of elements in the input array and k is the range of the input values (for counting sort).

//time complexity: O(d * (n + k)) for radix sort, where n is the number of elements in the input array,
// k is the range of the input values (for counting sort), and d is the number of digits in the largest number (for radix sort).

//----------------------3) bucket sort----------------------------------------------------------
void bucketSort(float A[], int n) { 
  vector<vector<float>> B(n); 
  for (int i=0; i<n; i++) B[(int)(n * A[i])].push_back(A[i]); // 1. distribute elements into buckets
  for (int i=0; i<n; i++) sort(B[i].begin(), B[i].end()); // 2. sort individual buckets
  int idx = 0; 
  for (int i=0; i<n; i++) for (float x : B[i]) A[idx++] = x; // 3. concatenate sorted buckets
}
/*worst case: O(n^2) when all elements are in the same bucket,
 leading to a single bucket containing all elements,
  which is then sorted using a comparison-based sorting algorithm(like insertion sort).
best case & average case: O(n + k) when the input elements are uniformly distributed across the buckets,
*/

//---------------------------------------------------------------------------------
//                     Main function to test the sorting algorithms
//---------------------------------------------------------------------------------
int main()
{

    // int arr[4]={80,30,60,50};
    // //insertion(arr,4); 
    // //selection(arr,4);
    // //bubble(arr,4);
    // //mergeSort(arr,0,3);
	// //quickSort(arr,0,3);
    // for(int i=0;i<4;i++){
    //     cout<<arr[i]<<" ";
    // }

	 int A[7] = {4, 2, 2, 8, 3, 3, 1};
     int B[7]; // array sorted
    countingSort(A, B, 7, 8);
    cout << "Sorted array: ";
    for (int i = 0; i < 7; i++)
        cout << B[i] << " ";
    cout << endl;


    return 0;
}
