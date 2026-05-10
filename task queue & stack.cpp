#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

/*Given an array of integers arr and an integer k, find the first negative integer in each contiguous subarray (window) of size k. If a window contains no negative integer, output 0 for that window.

Input:
• An array arr of n integers (−10⁵ ≤ arr[i] ≤ 10⁵)
• An integer k (1 ≤ k ≤ n ≤ 10⁵)

Output:
A list of length n−k+1 where the i‑th element is the first negative integer in the window starting at index i, or 0 if none exist.

Example:
Input: arr = [12, -1, -7, 8, -15, 30, 16, 28], k = 3
Output: [-1, -1, -7, -15, -15, 0]

Constraints:
• Time complexity: O(n)
• Space complexity: O(k)
• You must use a queue (deque) to store indices of negative numbers.

Task:
Write a function first_negative_in_window(arr, k) that returns the list of results. */


vector<int> first_negative_in_window(vector<int> arr, int k)
{
    int n = arr.size();
    queue<int> q;
    vector<int> result;

    for (int i = 0; i < k; i++)
    {
        if (arr[i] < 0)
        {
            q.push(i); //  q=[1, 2]
        }
    }

    for (int i = k; i < n; i++)
    {

        if (!q.empty())
        {
            result.push_back(arr[q.front()]); //result=[-1, -1, -7, -15, -15]
        }
        else  
        {
            result.push_back(0);
        }
        while (!q.empty() && q.front() < i-k+1)
        {
            q.pop();
        }
        if (arr[i] < 0)
        {
            q.push(i);
        }
    }
    if (!q.empty())
    {
        result.push_back(arr[q.front()]);
    }
    else
    {
        result.push_back(0);
    }
}

/*You are given an array prices where prices[i] is the stock price on day i (0‑based index). For each day i, the stock span is defined as the maximum number of consecutive days (including day i) immediately before (and including) day i where the price was less than or equal to prices[i].

Input:
• An array prices of n integers (1 ≤ n ≤ 10⁵, 1 ≤ prices[i] ≤ 10⁵)

Output:
An array span of the same length where span[i] is the stock span for day i.

Example:
Input: prices = [100, 80, 60, 70, 60, 75, 85]
Output: [1, 1, 1, 2, 1, 4, 6]

Constraints:
• Time complexity: O(n)
• Space complexity: O(n)
• You must use a stack in your solution.

Task:
Write a function stock_span(prices) that returns the list of spans.*/

vector<int> stock_span(vector<int> prices)
{
    int n = prices.size();
    vector<int> span(n);
    stack<int> s; 

    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && prices[s.top()] <= prices[i])
        {
            s.pop();
        }
        span[i] = s.empty() ? (i + 1) : (i - s.top());
        s.push(i);
    }
    return span;
}


int main()
{
    vector<int> arr = {12, -1, -7, 8, -15, 30, 16, 28};
    int k = 3;

    vector<int> ans = first_negative_in_window(arr, k);

    for (int x : ans) {
        cout << x << " "<< endl;
    }
    
    vector<int> span = stock_span(arr);
    for (int x : span) {
        cout << x << " "<< endl;
    }

    return 0;
}