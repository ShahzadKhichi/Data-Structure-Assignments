#include <iostream>
#include <conio.h>
using namespace std;
template <typename T>
class Queue
{
private:
    T *QueueArray;
    int size;
    int front;
    int rear;

public:
    Queue(int size)
    {
        front = rear = -1;
        this->size = size;
        QueueArray = new T[this->size];
    }
    bool isEmpty()
    {
        return front == -1;
    }
    bool isFull()
    {
        return (rear + 1) % size == front;
    }
    bool insertAtFront(T data)
    {
        if (isFull())
        {
            cout << "Queue is Full .You Cannot Insert More Elements " << endl;
            return false;
        }
        if (isEmpty())
        {
            front = rear = 0;
            QueueArray[front] = data;
            return true;
        }
        if (front == 0)
        {
            front = size - 1;
        }
        else
            front--;
        QueueArray[front] = data;
        return true;
    }
    bool insertAtRear(T data)
    {
        if (isFull())
        {
            cout << "Queue is Full .You Cannot Insert More Elements " << endl;
            return false;
        }
        if (isEmpty())
        {
            front = rear = 0;
            QueueArray[front] = data;
            return true;
        }
        rear = (rear + 1) % size;
        QueueArray[rear] = data;
        return true;
    }
    bool removeFromFront()
    {
        if (isEmpty())
        {
            return false;
        }
        if (front == rear)
        {
            front = rear = -1;
            return true;
        }
        front = (front + 1) % size;
        return true;
    }
    bool removeFromRear()
    {
        if (isEmpty())
        {
            return false;
        }
        if (front == rear)
        {
            front = rear = -1;
            return true;
        }
        if (rear == 0)
        {
            rear = size - 1;
        }
        else
            rear--;
        return true;
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty.Please Add elements first " << endl;
            return;
        }
        int temp = front;
        while (temp != rear)
        {
            cout << QueueArray[temp] << " ";
            temp = (temp + 1) % size;
        }
        cout << QueueArray[temp] << endl;
    }
    ~Queue()
    {
        delete[] QueueArray;
    }
};
void menu()
{
    puts("---------------------------------------");
    puts("Enter 1 To Insert At Front of Queue : ");
    puts("Enter 2 To Insert At Rear  of Queue : ");
    puts("Enter 3 To Remove At front of Queue : ");
    puts("Enter 4 To Remove At Rear  of Queue : ");
    puts("Enter 5 To Display the whole  Queue : ");
    puts("Enter 6 To Exit the programe        : ");
    puts("---------------------------------------");
}

int main()
{
    int size;
    char choice;
    bool exitPrograme = false;

    cout << "Enter size of Queue : ";
    cin >> size;
    Queue<char> Q(size);
    do
    {
        menu();
        cout << "Enter choice : ";
        choice = _getch();
        cout << choice << endl;
        switch (choice)
        {
        case '1':
            cout << "Enter element : ";
            cin >> choice;
            Q.insertAtFront(choice);
            break;
        case '2':
            cout << "Enter element : ";
            cin >> choice;
            Q.insertAtRear(choice);
            break;
        case '3':
            Q.removeFromFront();
            break;
        case '4':
            Q.removeFromRear();
            break;
        case '5':
            Q.display();
            break;

        case '6':
            cout << "Programe is going to Exit " << endl;
            exitPrograme = true;
            break;
        default:
            cout << "Invalid Choice .Please Try again " << endl;
            break;
        }

    } while (!exitPrograme);

    return 0;
}