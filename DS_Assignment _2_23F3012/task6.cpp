#include <iostream>
#include <string>
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

template <typename T>
class Queue
{
private:
    Node<T> *Front;
    Node<T> *rear;

public:
    Queue()
    {
        Front = rear = NULL;
    }
    bool isEmpty()
    {
        return !Front;
    }
    void enqueue(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (isEmpty())
        {
            Front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }
    T front()
    {
        if (!isEmpty())
        {
            return Front->data;
        }
        return 0;
    }
    bool dequeue()
    {
        if (isEmpty())
        {
            return false;
        }
        if (Front == rear)
        {
            delete Front;
            Front = rear = NULL;
            return true;
        }
        Node<T> *temp = Front;
        Front = Front->next;
        delete temp;
        return true;
    }
    ~Queue()
    {
        while (dequeue())
            ;
    }
};
int main()
{
    string str;
    Queue<char> queue;
    Stack<char> stack;
    bool flag = true;
    cout << "Enter a string  : ";
    cin >> str;
    for (auto i : str)
    {
        queue.enqueue(i);
        stack.push(i);
    }
    while (!stack.isEmpty() && !queue.isEmpty())
    {
        if (stack.top() != queue.front())
        {

            flag = false;
            break;
        }
        stack.pop();
        queue.dequeue();
    }
    if (flag)
    {
        cout << "String is  a Palindrome " << endl;
    }
    else
    {
        cout << "String is Not a Palindrome " << endl;
    }
    system("pause");
    return 0;
}