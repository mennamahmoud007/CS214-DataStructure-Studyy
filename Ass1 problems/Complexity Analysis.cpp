//Part A: Complexity Analysis (2 Marks)
//1. Problem 1 : Determine the time complexity for each code snippets with justification:

//1)
int hello_recursive(int n) {
    if (n <= 1) return 1; //basecase O(1) 
    return hello_recursive(n-1) + hello_recursive(n-2);
}
/*
**Trace**
hello_recursive(4) //1=2^0
hello_recursive(3)+hello_recursive(2) //2=2^1
hello_recursive(2)+hello_recursive(1)+hello_recursive(1)+hello_recursive(0) //4=2^2
hello_recursive(1)+hello_recursive(0)+1+1+1
1+1+1+1+1=5

The function follows a recursive pattern similar to the Fibonacci sequence, where each call generates two additional calls: hello_recursive(n-1) and hello_recursive(n-2).
This forms a recursion tree with branching factor 2 and depth n.
Therefore, the total number of calls grows exponentially, approximately 2^n
Hence, the time complexity is O(2^n)
space complexity is O(n) due to the maximum depth of the recursion stack being n.
*/
//----------------------------------------------------------------------------------------------------------------------
//2)
void test(int n) {
    int i = n;
    while (i > 1) {  //log(n)
        int j = 1;
        while (j < i) { //log(i)
            j *= 2;
        }
        i /= 2;
    }}
/*
**Trace**
if n = 16
i = 16
j: 1 → 2 → 4 → 8 → 16   // 4 steps = log(16)

i = 8
j: 1 → 2 → 4 → 8        // 3 steps = log(8)

i = 4
j: 1 → 2 → 4            // 2 steps = log(4)

i = 2
j: 1 → 2                // 1 step = log(2)


The outer loop runs log(n) times since i is divided by 2 each iteration.
The inner loop runs log(i) times, where i decreases in each iteration.
So the total work is:
log(n) + log(n/2) + log(n/4) + ...
This forms a decreasing sequence whose sum is O(log n).
Therefore, the total time complexity is O(log n).
 */