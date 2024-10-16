#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
class Node
{
public:
    char ch;
    Node *next;
    Node(char val);
};
Node::Node(char val)
{
    next = NULL;
    ch = val;
}
class Stack
{
private:
    Node *Top;
    int Size;

public:
    Stack();
    bool push(char ch);
    bool pop();
    bool isEmpty();
    char top();
    int size();
    bool isPalindrome(string str);
    void displayStack();
    ~Stack();
};
Stack::Stack()
{
    Top = NULL;
    Size = 0;
}
bool Stack::push(char ch)
{
    Node *newNode = new Node(ch);
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
bool Stack::pop()
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        Node *temp = Top;
        Top = Top->next;
        delete temp;
    }
    Size--;
    return true;
}
bool Stack::isEmpty()
{
    return !Top;
}
char Stack::top()
{
    if (Top)
    {
        return Top->ch;
    }
    return '0';
}
int Stack::size()
{
    return Size;
}
bool Stack::isPalindrome(string str)
{

    for (auto ch : str)
    {
        push(ch);
    }
    for (auto ch : str)
    {
        if (ch != top())
        {
            return false;
        }
        pop();
    }
    return true;
}
void Stack::displayStack()
{
    if (isEmpty())
    {
        return;
    }
    char ch = top();
    pop();
    displayStack();
    cout << ch;
    push(ch);
}
Stack::~Stack()
{

    while (pop())
        ;
}
void menu()
{
    cout << "---------------------------------------------------------" << endl;
    puts("| Enter 1 : push a character         :              |");
    puts("| Enter 2 : pop a character          :              |");
    puts("| Enter 3 : check Empty or not       :              |");
    puts("| Enter 4 : view Top character       :              |");
    puts("| Enter 5 : view size                :              |");
    puts("| Enter 6 : Print Stack              :              |");
    puts("| Enter 7 : check palindrome string  :              |");
    puts("| Enter 8 : To Exit programe         :              |");
    cout << "---------------------------------------------------------" << endl;
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
    Stack st;
    string str;
    string input;
    bool exitPrograme = false;
    do
    {
        menu();
        cout << "Enter a Your Choice : ";
        cin >> input;
        char choice = inputHandler(input);
        switch (choice)
        {
        case '1':
            cout << "Enter character : ";
            choice = _getch();
            cout << choice << endl;
            st.push(choice);
            break;
        case '2':
            st.pop();
            break;
        case '3':
            if (st.isEmpty())
            {
                cout << "Stack is Empty " << endl;
            }
            else
            {
                cout << "Stack is Not Empty" << endl;
            }
            break;
        case '4':
            if (st.isEmpty())
            {
                cout << "Stack is Empty please Push a character first" << endl;
            }
            else
                cout << "Top Character is " << st.top() << endl;
            break;
        case '5':
            cout << "Stack Size : " << st.size() << endl;
            break;
        case '6':
            if (st.isEmpty())
            {
                cout << "Stack is Empty please Push a character first" << endl;
            }
            else
            {
                cout << "Stack : ";
                st.displayStack();
                cout << endl;
            }
            break;
        case '7':
            cin.ignore();
            cout << "Enter string : ";
            getline(cin, str);
            if (st.isPalindrome(str))
            {
                cout << str << " is a Palindrome " << endl;
            }
            else
                cout << str << " is Not a Palindrome " << endl;
            break;
        case '8':
            exitPrograme = true;
            cout << "Progame is going to Exit" << endl;
            break;
        default:
            cout << "Invalid Choice .Please try again" << endl;
            break;
        }

    } while (!exitPrograme);
    return 0;
}