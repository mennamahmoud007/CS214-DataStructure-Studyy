#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
// #include <bits/stdc++.h>
using namespace std;
//stack with linked list as pointers

class Stack{
    private:
    struct Node{
        int value;
        Node* next;
    };
    Node* top;
    int stsize;
    public:
    Stack(int size){
        top = NULL;
        stsize = size;
    }
    void push(int x){
        Node* newNode = new Node;
        newNode->value = x;
        newNode->next = top;
        top = newNode;
        stsize++;
    }
    void pop(){
        if (top == NULL){
            cout << "Stack is empty" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        temp =temp->next = NULL; // to avoid dangling pointer
        delete temp;
        stsize--;
    }
    bool isEmpty(){
        return top == NULL;
    }
    void getTop(){
        if (top == NULL){
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Top element: " << top->value << endl;
    }
    void display(){
        Node* current = top;
        cout << "Stack elements: ";
        while (current != NULL){
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }
};

//stack with array-list implementation
class IntStack
{
private:
    int* stackArray;
    int stackSize;
    int top;

public:
    IntStack(int size)
    {
        stackArray = new int[size];
        stackSize = size;
        top = -1;
    }

    ~IntStack()
    {
        delete[] stackArray;
    }
    bool isFull()
    {
        return (top == stackSize - 1);
    }

    bool isEmpty()
    {
        return (top == -1);
    }

    void push(int num)
    {
        if (isFull())
            cout << "The stack is full.\n";
        else
        {
            top++;
            stackArray[top] = num;
        }
    }


    void pop(int& num)
    {
        if (isEmpty())
            cout << "The stack is empty.\n";
        else
        {
            num = stackArray[top];
            top--;
        }
    }

    void print()
    {
        cout << "\nStack contents:\n";
        for (int i = top; i >= 0; i--)
            cout << stackArray[i] << endl;
    }

    int peek() // returns the top value without removing it
    {
        if (isEmpty())
        {
            cout << "The stack is empty.\n";
            return -1; // or throw an exception
        }
        else
        {
            return stackArray[top];
        }
    }

    int count() // returns the number of elements in the stack
    {
        return top + 1;
        //return stackSize - (stackSize - top - 1); // alternative way
    }

    void clear() 
    {
        top = -1; // just reset top, no need to delete elements
        //stacksize = 0; // if we want to reset size as well, but usually we keep the size
    }

    bool search(int value) 
    {
        for (int i = top; i >= 0; i--)
        {
            if (stackArray[i] == value)
                return true;
        }
        return false;
    }

    void displayBottom() // prints the bottom element of the stack
    {
        if (isEmpty())
        {
            cout << "The stack is empty.\n";
        }
        else
        {
            cout << "Bottom element: " << stackArray[0] << endl;
        }
    }


};

//------------------------------------------------------------------------------------------------------------------------------
//bracket matching using stack
bool arePair(char opening, char closing){
    if (opening == '(' && closing == ')') return true;
    if (opening == '{' && closing == '}') return true;
    if (opening == '[' && closing == ']') return true;
    return false;
}
bool isBalanced(string exp){
    stack<char> s; // using STL stack for simplicity
    for (char ch : exp){
        if (ch == '(' || ch == '{' || ch == '['){
            s.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']'){
            if (s.empty() || !arePair(s.top(), ch)){
                return false; // closing bracket without matching opening
            }
            else s.pop(); // pop the matched opening bracket
        }
    }
    return s.empty(); // if stack is empty, all brackets are balanced
}
//--------------------------------------------------------------------------------------------------------------
//big integer
#include <iostream>
#include <stack>
#include <string>
using namespace std;

string addLargeNumbers(string num1, string num2)
{
    stack<int> s1, s2, result;

    // Push digits of num1 and num2 onto their respective stacks
    for (char c : num1)
        s1.push(c - '0');

    for (char c : num2)
        s2.push(c - '0');

    int carry = 0;

    // Add digits until both stacks are empty
    while (!s1.empty() || !s2.empty())
    {
        int sum = carry;

        if (!s1.empty())
        {
            sum += s1.top();
            s1.pop();
        }

        if (!s2.empty())
        {
            sum += s2.top();
            s2.pop();
        }

        result.push(sum % 10);   // Push the units digit
        carry = sum / 10;        // Calculate the carry
    }

    // If there's a remaining carry
    if (carry > 0)
        result.push(carry);

    // Convert the result stack back to a string
    string answer = "";
    while (!result.empty())
    {
        answer += char(result.top() + '0');
        result.pop();
    }

    return answer;
}
//------------------------------------------------------------------------------------------------------------------------
//postfixint
#include <iostream>
#include <stack>
using namespace std;

int evaluatePostfix(string exp)
{
    stack<int> st;

    for (int i = 0; i < exp.length(); i++)
    {
        char c = exp[i];

        // If the scanned character is an operand (number here), push it to the stack.
        if (isdigit(c))
        {
            st.push(c - '0');
        }
        else
        {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            int result;

            if (c == '+') result = a + b;
            else if (c == '-') result = a - b;
            else if (c == '*') result = a * b;
            else if (c == '/') result = a / b;

            st.push(result);
        }
    }

    return st.top();
}

int main()
{
    cout << "\n-------------- Stack --------------\n";

    IntStack stack(5);
    int catchVar;
    int val;

    cout << "\nPlease enter int values to push into the stack (-1 to stop):\n";
    cin >> val;
    while (val != -1)
    {
        stack.push(val);
        cin >> val;
    }

    stack.print();

    cout << "\n .............. Lab Requirements of Stack .............\n";
    cout << "\n Check code of Stack and write the required member functions";
    cout << "\n Then test these functions by calling them from the main()"; 
    

    cout << endl;

    return  0;
}