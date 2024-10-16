#include <iostream>
#include <conio.h>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;

    Node(T data) : data(data), next(NULL) {}
};
template <typename T>
class Queue
{
    Node<T> *front, *rear;
    int Size;
    int maxSize;

public:
    Queue()
    {
        front = rear = NULL;
        Size = 0;
        maxSize = 0;
    }

    bool isEmpty()
    {
        return !front;
    }

    void setMax(int size)
    {
        maxSize = size;
    }
    bool isFull()
    {
        if (maxSize == Size)
        {
            return true;
        }
        return false;
    }
    bool enqueue(T data)
    {
        if (isFull())
        {
            return false;
        }
        Node<T> *newNode = new Node<T>(data);
        Size++;
        if (rear == NULL)
        {
            front = rear = newNode;
            return true;
        }
        rear->next = newNode;
        rear = newNode;
        return true;
    }

    bool dequeue()
    {

        if (isEmpty())
        {
            return false;
        }
        T data = front->data;
        Node<T> *temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }
        delete temp;
        Size--;
        return true;
    }
    T QueueFront()
    {
        if (isEmpty())
        {
            return 0;
        }
        return front->data;
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty" << endl;
            return;
        }
        Node<T> *temp = front;
        while (temp)
        {
            cout << temp->data;
            if (temp->next)
                cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }
    int size()
    {
        return Size;
    }
    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }
};

class QueueMangementSystem
{
    int noOfQueue;
    int noOfPerson;
    Queue<int> *Q;

public:
    QueueMangementSystem(int noOfQueue, int noOfPerson)
        : noOfQueue(noOfQueue), noOfPerson(noOfPerson)
    {
        Q = new Queue<int>[noOfQueue];
        for (int i = 0; i < noOfQueue; i++)
        {
            Q[i].setMax(noOfPerson);
        }
    }
    void display()
    {

        for (int i = 0; i < noOfQueue; i++)
        {
            cout << "Queue " << i + 1 << " : ";
            Q[i].display();
        }
    }
    bool addPerson()
    {
        for (int i = 0; i < noOfQueue; i++)
        {
            if (!Q[i].isFull())
            {
                if (Q[i].enqueue(Q[i].size() + 1))
                {
                    return true;
                }
            }
        }
        return false;
    }
    void ProcessQueue()
    {

        if (Q[0].isEmpty())
        {
            cout << "no person is in Queue to process" << endl;
            return;
        }
        cout << "Processing person " << Q[0].QueueFront() << " from Queue 1" << endl;
        Q[0].dequeue();
        for (int i = 0; i < noOfQueue - 1; i++)
        {
            if (!Q[i + 1].isEmpty())
            {
                Q[i].enqueue(Q[i + 1].QueueFront());
                Q[i + 1].dequeue();
            }
        }
        cout << "Queues after processing : \n";
        display();
    }

    ~QueueMangementSystem()
    {
        delete[] Q;
    }
};
void menu()
{

    puts("1 .Add a person to Queue : ");
    puts("2 .process a person from Queue : ");
    puts("3 .display All Queues :");
    puts("4 .Exit programe : ");
}
int main()
{
    puts("\t\t\tQueue Management System ");
    int noOfPerson, noOfQueue;
    bool exitProgram = false;
    char choice;

    cout << "Enter the number of Queues: ";
    cin >> noOfQueue;

    do
    {
        cout << "Enter the number of persons : ";
        cin >> noOfPerson;
        if (noOfPerson < 10)
        {
            cout << "No of Person must be greater than 10 . please try again " << endl;
        }
    } while (noOfPerson < 10);
    QueueMangementSystem QM(noOfQueue, noOfPerson);
    cout << endl;
    do
    {
        menu();
        cout << "Enter choice : ";
        choice = _getch();
        cout << choice << endl;
        switch (choice)

        {
        case '1':
            if (QM.addPerson())
            {
                cout << "Person Added Successfully" << endl;
            }
            else
            {
                cout << "No space in Queues . person cannot be added" << endl;
            }
            break;
        case '2':
            QM.ProcessQueue();
            break;
        case '3':
            QM.display();
            break;
        case '4':
            cout << "programe is going to exit" << endl;
            exitProgram = true;
            break;
        default:
            break;
        }
    } while (!exitProgram);

    return 0;
}
