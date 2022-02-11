/*
Question:
Given a string, only include digit number(0~9), rotate 180 degree (The tale becomes head, and the digits are up side down), 
then compare with the original string, 
For example, 
  case1: input "1234", after moving, will be "4321" (but all of them are up side down), that means they are different, then return false.
  case2: input "181", after moving, will be "181", (1 up side down is 1, 8 up side down is 8), that means they are same, then return true.

Thinking:
About the digit numbers: 0~9, doing up side down,
  1) the digits: 0, 1, 8, compare before and after, they are same.
  2) the digits: 2, 3, 4, 5, 7, compare before and after, they are different.
  3) the digits: 6, 9, compare before after, they will become each other.

Solution:
 1) if the string includes one of digits(2, 3, 4, 5, 7), then we can say after moving, the two strings are different, we can return false directly.
 2) if the string only includes the digits(0, 1, 6, 8, 9), then we can rotate the string and save as a ne string.
 3) we need to check the new string, if there are 6 or 9 exist, we should change them: 6->9, 9->6.
 4) then compare the two string, if they are different, then return false, otherwise, return true.
 */

#include <iostream>
#include <string>
#include <set>

using namespace std;

bool isSameString(const string& str)
{
    if (str.empty()) {
        return true;
    }

    set<char> diffSet = {'2', '3', '4', '5', '7'};
    for (auto& c: str) {
        if (diffSet.find(c) != diffSet.end()) {
            return false;
        }
    }

    cout << "oldStr=" << str << endl;

    string newStr = string(str.crbegin(), str.crend());

    for (auto& c: newStr) {
        if (c == '9') {
            c = '6';
        } else if (c == '6') {
            c = '9';
        }
    }
    cout << "newStr=" << newStr << endl;

    if (newStr != str) {
        return false;
    }

    return true;
}

/*
 Updated(2/11/2022):(Optimized)
 Acturally, this is a palindrome questions.
 So we can compare the string from 2 sides( left-> middle, righ->middle), compare the left and right character:
 if they are one of {2,3,4,5,7}, return false directly.
 if they are same, check: 
    if they both are 9, or both are 6, return false directly.
 else(they are different) check:
    if they both are not pair(9,6) or (6,9), return false directly.
 return true.
*/
bool isPalindromeString_1(const string& str)
{
    if (str.empty()) {
        return true;
    }

    set<char> diffSet = {'2', '3', '4', '5', '7'};
    for (auto& c: str) {
        if (diffSet.find(c) != diffSet.end()) {
            return false;
        }
    }

    //{0, 1, 6, 8, 9}
    int left = 0, right = str.size() - 1;
    while (left < right) {
    
        if (str[left] == str[right]) { 
            if (str[left] == '9' || str[left] == '6') {  
                return false;
            }
        } else { 
            if (!((str[left] == '9' && str[right] == '6') || (str[left] == '6' && str[right] == '9'))) {
                return false;
            }
        } 

        left++;
        right--;
    }
    
    return true;
}

bool isPalindromeString_2(const string& str)
{
    if (str.empty()) {
        return true;
    }

    set<char> diffSet = {'2', '3', '4', '5', '7'};
    
    auto left = str.begin(), right = str.end() - 1;
    while (left < right) {
        if (diffSet.find(*left) != diffSet.end() || diffSet.find(*right) != diffSet.end()) {  // one of {2, 3, 4, 5, 7}
            return false;
        }    

        if (*left == *right) { 
            if (*left == '9' || *left == '6') {  
                return false;
            }
        } else { 
            if (!((*left == '9' && *right == '6') || (*left == '6' && *right == '9'))) {
                return false;
            }
        } 

        left++;
        right--;
    }
    
    return true;
}

int main()
{
    {
        cout<< "isSameString:" << endl;
        string s1 = "1234";  // should be false.
        string s2 = "96";    // should be true
        string s3 = "18";    // should be false

        cout << isSameString(s1) <<endl;
        cout << isSameString(s2) <<endl;
        cout << isSameString(s3) <<endl;

        string s4 = "996";    // should be false
        string s5 = "9966";    // should be true
        string s6 = "916";    // should be true

        cout << isSameString(s4) <<endl;
        cout << isSameString(s5) <<endl;
        cout << isSameString(s6) <<endl;
    }

    {
        cout<< "\nisPalindromeString_1:" << endl;
        string s1 = "1234";  // should be false.
        string s2 = "96";    // should be true
        string s3 = "18";    // should be false

        cout << isPalindromeString_1(s1) <<endl;
        cout << isPalindromeString_1(s2) <<endl;
        cout << isPalindromeString_1(s3) <<endl;

        string s4 = "996";    // should be false
        string s5 = "9966";    // should be true
        string s6 = "916";    // should be true

        cout << isPalindromeString_1(s4) <<endl;
        cout << isPalindromeString_1(s5) <<endl;
        cout << isPalindromeString_1(s6) <<endl;
    }

    {
        cout<< "\nisPalindromeString_2:" << endl;
        string s1 = "1234";  // should be false.
        string s2 = "96";    // should be true
        string s3 = "18";    // should be false

        cout << isPalindromeString_2(s1) <<endl;
        cout << isPalindromeString_2(s2) <<endl;
        cout << isPalindromeString_2(s3) <<endl;

        string s4 = "996";    // should be false
        string s5 = "9966";    // should be true
        string s6 = "916";    // should be true

        cout << isPalindromeString_2(s4) <<endl;
        cout << isPalindromeString_2(s5) <<endl;
        cout << isPalindromeString_2(s6) <<endl;
    }


    return 0;
}