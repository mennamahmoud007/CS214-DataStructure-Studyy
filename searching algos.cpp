#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

//#include <bits/stdc++.h>
using namespace std;

const char lookupTable[10][2] = {
    {'a', '#'}, {'c', '@'}, {'e', '%'}, {'g', '&'}, {'h', '*'}, {'i', '('}, {'m', ')'}, {'r', '!'}, {'s', ','}, {'t', '='}};

char a[100];
int rows = 10;
;
// encode by binary search col 0
// thisisasecretmessage
char encode(char target)
{
    int low = 0;
    int high = rows - 1;
    int mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (lookupTable[mid][0] == target)
        {
            return lookupTable[mid][1];
        }
        else if (lookupTable[mid][0] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return '?';
}
// linear search
char decode(char target)
{
    for (int i = 0; i < rows; i++)
    {
        if (lookupTable[i][1] == target)
        {
            return lookupTable[i][0];
        }
    }
    return '?';
}
//-------------------------------------------------------------------------------------------------
// int linsearch(int arr[], int n, int target, int &cnt){
//     for (int i = 0; i < n; i++){
//         cnt++;
//         if (arr[i] == target){
//             return i;
//         }
//     }
//     return -1;
// }

// int binsearch(int arr[], int n, int target, int &cnt){
//     int low = 0;
//     int high = n - 1;
//     int mid;
//     while (low <= high){
//         cnt++;
//         mid = low + (high - low) / 2;
//         if (arr[mid] == target){
//             return mid;
//         }
//         else if (arr[mid] < target){
//             low = mid + 1;
//         }
//         else{
//             high = mid - 1;
//         }
//     }
//     return -1;
// }
//-------------------------------------------------------------------------------------------------

int main()
{    
    // int lukky [10]= {{13579},{26791},{26792},{33445},{55555},{62483},{77777},{79422},{85647},{93121}};
    // int win;
    // bool found = false;
    // cout<< "Enter this week’s winning five-digit number ";
    // cin >> win;
    
    // // for (int i=0; i<10 ; i++){
    // //     if (win == lukky[i]){
    // //         found = true;
    // //         break;
    // //     }
    // // }
    
    // int low = 0;
    // int high = 9;
    // while (low <= high){
    //     int mid = low + (high - low) / 2;
    //     if (lukky[mid] == win){
    //         found = true;
    //         break;
    //     }
    //     else if (lukky[mid] < win){
    //         low = mid + 1;
    //     }
    //     else{
    //         high = mid - 1;
    //     }
    // }

    // if (found){
    //     cout << "Congratulations! You have won the lottery!" << endl;
    // }
    // else{
    //     cout << "Sorry, better luck next time." << endl;
    // }


//---------------------------------------------------------------------------------------------------------------------
    string message;
    string encodedMessage = "";
    string decodedMessage = "";

    cout << "Enter message: ";
    getline(cin, message);

    // encode
    for (int i = 0; i < message.length(); i++){
        encodedMessage += encode(message[i]);
    }

    cout << "Encoded Message: " << encodedMessage << endl;

    // decode
    for (int i = 0; i < encodedMessage.length(); i++){
        decodedMessage += decode(encodedMessage[i]);
    }

    cout << "Decoded Message: " << decodedMessage << endl;

    return 0;
}