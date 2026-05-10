#include <iostream>
#include <string>
#include <stack>
#include <utility>
using namespace std;
/*Problem 5 : Stack [3 marks] 
Question 1- Implement a function that evaluates valid mathematical expression string s 
containing digits, +, -, parentheses, and spaces. 
You are not allowed to use built-in evaluation functions like eval(). 
Handle unary minus (e.g., -1, -(2+3)), but unary plus is invalid. 
Example inputs and outputs: 
Input: "1 + 1" → Output: 2 
Input: " 2-1 + 2 " → Output: 3 
Input: "(1+(4+5+2)-3)+(6+8)" → Output: 23 
Constraints: 
1≤s.length≤3×105 
s consists of digits, +, -, (, ), and spaces. 
Expression is valid. 
No two consecutive operators.*/
long long evaluateString(string _str){ //time: O(n) & space: O(n)-->worst case all parentheses (((())))
    long long result = 0, sign = 1, num = 0; //positive by default
    stack<pair<long long, long long>> _stack; 

    // Handling the string
    for(int i = 0; i < _str.size(); i++){
        if(_str[i] >= '0' && _str[i] <= '9'){
            num = num * 10 + (_str[i] - '0');
        }
        else if(_str[i] == '+'){
            result += sign * num;
            sign = 1;
            num = 0;
        }
        else if(_str[i] == '-'){
            result += sign * num;
            sign = -1;
            num = 0;
        } 
        else if(_str[i] == '('){
            _stack.push({result, sign});
            num = 0; result = 0; sign = 1;
        }
        else if(_str[i] == ')'){
            result += sign * num;
            num = 0; 
            long long savedResult = _stack.top().first;
            long long savedSign = _stack.top().second;
            result *= savedSign;
            result += savedResult;
            _stack.pop();
        }
    }

    return result += sign * num;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string expression;
    getline(cin, expression);
    long long x = evaluateString(expression);
    cout << x << endl;
    
    return 0;
}