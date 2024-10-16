#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <conio.h>
using namespace std;
template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node(T val)
    {
        next = NULL;
        data = val;
    }
};
template <typename T>
class Stack
{
private:
    Node<T> *Top;
    int Size;

public:
    Stack()
    {
        {
            Top = NULL;
            Size = 0;
        }
    }
    bool push(T str)
    {
        {
            Node<T> *newNode = new Node<T>(str);
            if (Top == NULL)
            {
                Top = newNode;
            }
            else
            {
                newNode->next = Top;
                Top = newNode;
            }
            Size++;
            return true;
        }
    }
    bool pop()
    {
        if (isEmpty())
        {
            return false;
        }
        else
        {
            Node<T> *temp = Top;
            Top = Top->next;
            delete temp;
        }
        Size--;
        return true;
    }
    bool isEmpty()
    {
        return !Top;
    }
    T top()
    {
        if (Top)
        {
            return Top->data;
        }
        return 0;
    }
    int size()
    {
        return Size;
    }
    void displayStack()
    {
        if (isEmpty())
        {
            return;
        }
        T str = top();
        pop();
        displayStack();
        cout << str;
        push(str);
    }
    ~Stack()
    {

        while (pop())
            ;
    }
};
bool isCoffient(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}
bool isOperatorChar(char ch)
{
    if (ch == '^' || ch == '+' || ch == '*' || ch == '/' || ch == '-' || ch == '(' || ch == ')')
    {
        return true;
    }
    return false;
}
vector<string> stringToArrOfString(string polynomial)
{
    vector<string> v;
    string st;
    for (int i = 0; i < polynomial.size(); i++)
    {

        if (polynomial[i] == ' ')
        {
            continue;
        }
        else if (isCoffient(polynomial[i]))
        {

            st.push_back(polynomial[i]);
        }
        else
        {

            if (st.empty())
            {

                st.push_back(polynomial[i]);
                v.push_back(st);
                st.clear();
            }
            else
            {
                v.push_back(st);
                st.clear();
                st.push_back(polynomial[i]);
                v.push_back(st);
                st.clear();
            }
        }
    }
    v.push_back(st);
    return v;
}

bool isOperator(string ch)
{
    if (ch == "^" || ch == "+" || ch == "*" || ch == "/" || ch == "-" || ch == "(" || ch == ")")
    {
        return true;
    }
    return false;
}
int opPrecedence(string op)
{
    if (op == "+" || op == "-")
    {
        return 1;
    }
    else if (op == "*" || op == "/")
    {
        return 2;
    }
    else if (op == "^")
    {
        return 3;
    }
    else
        return -1;
}
bool compareTopPostFix(string top, string cur)
{
    if (opPrecedence(top) >= opPrecedence(cur))
    {
        return true;
    }
    return false;
}
bool compareTopPreFix(string top, string cur)
{
    if (opPrecedence(top) > opPrecedence(cur))
    {
        return true;
    }
    return false;
}
vector<string> InfixToPostFix(vector<string> infix)
{
    vector<string> result;
    Stack<string> st;
    for (auto i : infix)
    {
        if (i == " ")
        {
            continue;
        }
        if (!isOperator(i))
        {

            result.push_back(i);
        }
        else
        {
            if (i == "(")
            {
                st.push(i);
            }
            else if (i == ")")
            {
                while (!st.isEmpty() && st.top() != "(")
                {
                    result.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else
            {
                while (!st.isEmpty() && compareTopPostFix(st.top(), i))
                {
                    result.push_back(st.top());
                    st.pop();
                }
                st.push(i);
            }
        }
    }
    while (!st.isEmpty())
    {
        result.push_back(st.top());
        st.pop();
    }
    return result;
}
vector<string> InfixToPreFix(vector<string> infix)
{
    vector<string> result;
    Stack<string> st;
    reverse(infix.begin(), infix.end());
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] == "(")
        {
            infix[i] = ")";
        }
        else if (infix[i] == ")")
        {
            infix[i] = "(";
        }
    }

    for (auto i : infix)
    {
        if (!isOperator(i))
        {
            result.push_back(i);
        }
        else
        {
            if (i == "(")
            {
                st.push(i);
            }
            else if (i == ")")
            {
                while (!st.isEmpty() && st.top() != "(")
                {
                    result.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else
            {
                while (!st.isEmpty() && compareTopPreFix(st.top(), i))
                {
                    result.push_back(st.top());
                    st.pop();
                }
                st.push(i);
            }
        }
    }
    while (!st.isEmpty())
    {
        result.push_back(st.top());
        st.pop();
    }
    for (int i = 0, j = result.size() - 1; i < j; i++, j--)
    {
        swap(result[i], result[j]);
    }
    return result;
}
int performOperation(int opr1, int opr2, string op)
{
    if (op == "+")
    {
        return opr1 + opr2;
    }
    else if (op == "-")
    {
        return opr1 - opr2;
    }
    else if (op == "/")
    {
        return opr1 / opr2;
    }
    else if (op == "*")
    {
        return opr1 * opr2;
    }
    else if (op == "^")
    {
        return pow(opr1, opr2);
    }
    else
        return -1;
}
bool isInterger(string str)
{
    if (str.size() == 0)
    {
        return false;
    }
    for (auto i : str)
    {
        if (!(i >= '0' && i <= '9'))
        {
            return false;
        }
    }
    return true;
}
int evaluatePostFix(vector<string> postFix)
{
    Stack<int> st;
    for (auto i : postFix)
    {

        if (!isOperator(i))
        {
            if (isInterger(i))
                st.push(stoi(i));
        }
        else
        {
            int opr2 = st.top();
            st.pop();
            int opr1 = st.top();
            st.pop();
            int res = performOperation(opr1, opr2, i);
            st.push(res);
        }
    }
    return st.top();
}
int evaluatePreFix(vector<string> preFix)
{
    Stack<int> st;
    reverse(preFix.begin(), preFix.end());
    for (auto i : preFix)
    {
        if (!isOperator(i))
        {
            if (isInterger(i))
                st.push(stoi(i));
        }
        else
        {
            int opr1 = st.top();
            st.pop();
            int opr2 = st.top();
            st.pop();
            int res = performOperation(opr1, opr2, i);
            st.push(res);
        }
    }
    return st.top();
}
void menu()
{
    puts("Enter 1 : PostFix Notation         :   ");
    puts("Enter 2 : PreFix Notation          :   ");
    cout << "Enter your choice : ";
}
char inputHandler(string input)
{
    if (input.size() > 1 || input.size() < 1)
    {
        return '9';
    }
    return input[0];
}
int main()
{

    string str;
    char choice;
    vector<string> temp;
    vector<string> exp;
    cout << "Enter Expression :  ";
    getline(cin, str);
    temp = stringToArrOfString(str);
    menu();
    do
    {
        choice = _getch();
        cout << choice << endl;
        if (choice == '1' || choice == '2')
        {
            break;
        }
        cout << "Invalid choice . Please Try again " << endl;

    } while (true);
    if (choice == '1')
    {
        exp = InfixToPostFix(temp);
        cout << "PostFix Expression : ";
        for (auto i : exp)
        {

            cout << i;
        }
        cout << endl;
        cout << "Result : " << evaluatePostFix(exp) << endl;
    }
    else
    {
        exp = InfixToPreFix(temp);
        cout << "PreFix Expression : ";
        for (auto i : exp)
        {
            cout << i;
        }
        cout << endl;
        cout << "Result : " << evaluatePreFix(exp) << endl;
    }

    system("pause");
    return 0;
}