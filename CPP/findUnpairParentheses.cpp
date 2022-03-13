
/*
Question:
 Given a string that includes(only includes) open and close parenthese. find out how many characters that can be made a pair.
 For example:
 input: ((()  output: 2
 input: ))(   output: 1
 input: (())  output: 0 
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

/*
Solution_1:
 using a stack, 
 1) for loop the str:
   if the stack is empty, put the charactor from str to stack.
   if the charactor is "(" from str, then push to stack.
   if the charactor is ")" from str, compare the charactor between stack top one and str:
      if the top ont in stack is "(", then remove the top one from stack.
      else put the charactor to stack.
 2) calculate the elements number of the stack.   

 Complexity: Time: N, Space: N
*/
int findUnpairParenthese(const string& str)
{
    if (str.empty()) {
        return 0;
    }

    stack<char> s;

    for (const auto& c: str) {
        if (s.empty()) {
            s.push(c);
            continue;
        }

        if (s.top() == '(' && c == ')') {
            s.pop();
        } else{
            s.push(c);
        }
    }

    int rtn = 0;
    while (!s.empty()) {
        rtn++;
        s.pop();
    }

    return rtn;
}


/*
Follow up: Can change the Space complexity to 1(constant) ?

Solution_2:
define a index left, and a pairnumber that how many pairs have found. 
for loop the str:
  if element equal '(', left equal the current index i. 
  if element equal ')', if str[left] == '(', make a pair, left--. 
                        else means str[left] == ')', cannnot make a pair, left move to index i.

 Complexity: Time: N, Space: 1
*/
int findUnpairParenthese_1(const string& str)
{
    if (str.empty()) {
        return 0;
    }

    int pairs = 0;
    int left = 0;
    for (int i = 0 ; i < str.size(); i++) {
        if (str[i] == ')' && (left >= 0 && str[left] == '(' )) {
            left--;
            pairs++;
        } else {
            left = i;
        }
    }

    return str.size() - pairs * 2;;
}


int main()
{
    {
        string s1 = "(())";
        cout << s1 << " has " << findUnpairParenthese(s1) << " unpair parethese" << endl;

        string s2 = "(()";
        cout << s2 << " has " << findUnpairParenthese(s2) << " unpair parethese" << endl;

        string s3 = "))(";
        cout << s3 << " has " << findUnpairParenthese(s3) << " unpair parethese" << endl;

        string s4 = ")(()(";
        cout << s4 << " has " << findUnpairParenthese(s4) << " unpair parethese" << endl;
    }

    {
        cout << endl;
        string s1 = "(())";
        cout << s1 << " has " << findUnpairParenthese_1(s1) << " unpair parethese" << endl;

        string s2 = "(()";
        cout << s2 << " has " << findUnpairParenthese_1(s2) << " unpair parethese" << endl;

        string s3 = "))(";
        cout << s3 << " has " << findUnpairParenthese_1(s3) << " unpair parethese" << endl;

        string s4 = ")(()(";
        cout << s4 << " has " << findUnpairParenthese_1(s4) << " unpair parethese" << endl;

    }

    return 0;
}





