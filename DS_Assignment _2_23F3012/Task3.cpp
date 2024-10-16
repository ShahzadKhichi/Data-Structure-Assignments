#include <iostream>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node(int data) : data(data), next(NULL) {};
};
class Stack
{
    Node *Top;

public:
    int size;
    Stack()
    {
        Top = NULL;
        size = 0;
    }
    bool isEmpty()
    {
        return !Top;
    }
    int top()
    {
        if (!Top)
        {
            return -1;
        }
        return Top->data;
    }
    void push(int data)
    {
        size++;
        Node *newNode = new Node(data);
        if (Top == NULL)
        {
            Top = newNode;
            return;
        }
        newNode->next = Top;
        Top = newNode;
    }
    bool pop()
    {

        if (Top == NULL)
        {
            return false;
        }
        Node *temp = Top;
        Top = Top->next;
        delete temp;
        temp = NULL;
        size--;
        return true;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty " << endl;
            return;
        }
        Node *temp = Top;
        while (temp)
        {
            cout << temp->data;
            temp = temp->next;
            if (temp)
                cout << " ";
        }
        cout << endl;
    }
};

void display(Stack &source, Stack &helper, Stack &destination)
{
    cout << "Shelf 1 : ";
    source.display();
    cout << "Shelf 2 : ";
    helper.display();
    cout << "Shelf 3 : ";
    destination.display();
}
void ShelfShuffle(int size, Stack &source, Stack &helper, Stack &destination)
{
    if (size == 1)
    {
        destination.push(source.top());
        source.pop();
        cout << endl;
        display(source, helper, destination);
        return;
    }
    ShelfShuffle(size - 1, source, destination, helper);
    destination.push(source.top());
    source.pop();
    cout << endl;
    display(source, helper, destination);
    ShelfShuffle(size - 1, helper, source, destination);
}
int main()
{
    Stack source, helper, destination;
    int elemments;
    cout << "Enter the number of elements : ";
    cin >> elemments;
    for (int i = elemments; i > 0; i--)
    {
        source.push(i);
    }
    display(source, helper, destination);
    ShelfShuffle(source.size, source, helper, destination);
    system("pause");
    return 0;
}