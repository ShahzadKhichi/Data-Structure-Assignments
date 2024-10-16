#include <iostream>
using namespace std;

class Node
{
public:
    int id;
    Node *next;

    Node(int id)
    {
        this->id = id;
        this->next = nullptr;
    }
};

class CircularLinkedList
{
public:
    Node *head;

    CircularLinkedList()
    {
        head = nullptr;
    }

    void insert(int id)
    {
        Node *newNode = new Node(id);
        if (head == nullptr)
        {
            head = newNode;
            head->next = head;
        }
        else
        {
            Node *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    void moveNodeToFront(int id)
    {
        if (head == nullptr)
        {
            puts("No node to access.");
            return;
        }

        Node *temp = head;
        Node *tail = nullptr;

        do
        {
            tail = temp;
            temp = temp->next;
        } while (temp != head);

        temp = head;
        Node *prev = nullptr;

        do
        {
            if (temp->id == id)
            {
                if (prev)
                {
                    prev->next = temp->next;
                    tail->next = temp;
                    temp->next = head;
                    head = temp;
                }
                puts("After accessing file id.");
                return;
            }
            prev = temp;
            temp = temp->next;
        } while (temp != head);

        puts("Desired id not found in list.");
    }

    void print()
    {
        if (head == nullptr)
        {
            puts("No list to print.");
            return;
        }

        Node *temp = head;
        do
        {
            cout << temp->id << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

void Menu()
{
    cout << "--------------------------------------" << endl;
    puts("| Enter 1. Insert Node              : |");
    puts("| Enter 2. Move Node to Front       : |");
    puts("| Enter 3. Print List               : |");
    puts("| Enter 4 To Exit Programe          : |");
    cout << "---------------------------------------" << endl;
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
    CircularLinkedList cache;

    bool progameExit = false;
    do
    {
        Menu();
        char choice;
        int id;
        string input;
        cout << "Enter your choice: ";
        cin >> input;

        choice = inputHandler(input);

        switch (choice)
        {
        case '1':
            cout << "Enter id to insert: ";
            cin >> id;
            cache.insert(id);
            puts("Node inserted.");
            break;
        case '2':
            cout << "Enter id to move to front: ";
            cin >> id;
            cache.moveNodeToFront(id);
            break;
        case '3':
            puts("Current state of the list:");
            cache.print();
            break;
        case '4':
            puts("Exiting the program...");
            progameExit = true;
            return 0;
        default:
            puts("Invalid choice. Please try again.");
        }
    } while (!progameExit);
    system("pause");
    return 0;
}
