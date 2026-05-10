#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------------
//                        sorting algorithms
//---------------------------------------------------------------------------------
template <class T>                  //0  1  2  3
void insertion(T data[] , int n){  //80 |30 60 50
    for(int i=1 ;i<n;i++){
       int j;
       T tmp =data[i]; // 30

        for(j=i;j>0 && tmp < data[j-1];j--){ //j=1 --> j=0 //data[j]=80
            data[j]=data[j-1]; // data[1]=80
        }
        data[j]=tmp; // data[0]=30      
    }
 }
//----------------------------------------------------------------------------------------------
template <class T>
void selection(T data[], int n){
     for (int i=0;i<n-1;i++){
        for (int j=i+1, least=i; j<n;j++){
            if (data[j]<data[least]){
                least=j;
            }
            swap(data[i],data[least]);
        }
     }
}
//--------------------------------------------------------------------------------------------------
template <class T>
void bubble(T data[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=n-1;j>i;--j){
            if(data[j]<data[j-1]){
                swap(data[j],data[j-1]);
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------
void merge(int arr[], int l, int m, int r)//m = l + (r - l) / 2;       
{
	int i, j, k;
	int n1 = m - l + 1;// First subarray is arr[l..m]                    
	int n2 = r - m;// Second subarray is arr[m+1..r]                     
	int *L=new int[n1], *R=new int[n2];
	
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = j = 0; 
	k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
} 
void mergeSort(int arr[], int l, int r) // l = 0, r = n-1 
{
	if (l < r)  //backtracking condition
	{
		int m = l + (r - l) / 2;
        
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}
//-------------------------------------------------------------------------------------------------
int partition(int arr[], int left, int right)
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
//-------------------------------------------------------------------------------------------------
int k=100; // maximum value in the input array
void countingSort(int A[], int B[], int n, int k)
{
    int C[100];  
    // 1. Initialize aux array
    for (int i = 0; i <= k; i++)
        C[i] = 0;

    // 2. Count occurrences
    for (int j = 0; j < n; j++)
        C[A[j]]++;

    // 3. Cumulative sums
    for (int i = 1; i <= k; i++)
        C[i] += C[i - 1];

    // 4. Build sorted array
    for (int j = n - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j]; 
        C[A[j]]--;
    }
}
//--------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------
void bucketSort(float A[], int n) { 
  vector<vector<float>> B(n); 
  for (int i=0; i<n; i++) B[(int)(n * A[i])].push_back(A[i]); 
  for (int i=0; i<n; i++) sort(B[i].begin(), B[i].end()); 
  int idx = 0; 
  for (int i=0; i<n; i++) for (float x : B[i]) A[idx++] = x; 
}
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
