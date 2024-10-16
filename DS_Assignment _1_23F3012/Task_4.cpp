#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    int id;
    Node *next;
    Node *previous;
    Node *nestedNode;

    Node(int idValue);
};

class BookList
{
public:
    Node *head;

    BookList();
    ~BookList();
    void clearList();
    void insertBook(int id, bool hasNestedVolumes);
    void addNestedVolumes(Node *parent);
    void flattenList();
    void printList() const;
    void inputBook();
    void displayMenu();
};

Node::Node(int idValue) : id(idValue), next(nullptr), previous(nullptr), nestedNode(nullptr) {}

BookList::BookList() : head(nullptr) {}

BookList::~BookList()
{
    clearList();
}

void BookList::clearList()
{
    Node *current = head;
    while (current)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void BookList::insertBook(int id, bool hasNestedVolumes)
{
    Node *newNode = new Node(id);
    if (!head)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->previous = temp;
    }

    if (hasNestedVolumes)
    {
        addNestedVolumes(newNode);
    }
}

void BookList::addNestedVolumes(Node *parent)
{
    int count;
    cout << "Enter number of volumes/series for book " << parent->id << ": ";
    cin >> count;

    for (int i = 0; i < count; ++i)
    {
        int nestedId;
        bool isVolume;
        cout << "Enter ID of volume/series: ";
        cin >> nestedId;
        cout << "Is it a volume? (1 for yes, 0 for no): ";
        cin >> isVolume;

        Node *nestedNode = new Node(nestedId);
        if (!parent->nestedNode)
        {
            parent->nestedNode = nestedNode;
        }
        else
        {
            Node *temp = parent->nestedNode;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = nestedNode;
            nestedNode->previous = temp;
        }

        if (isVolume)
        {
            addNestedVolumes(nestedNode);
        }
    }
}

void BookList::flattenList()
{
    if (!head)
    {
        cout << "\nNo list to flatten.\n";
        return;
    }

    Node *current = head;
    while (current)
    {
        if (current->nestedNode)
        {
            Node *nestedCurrent = current->nestedNode;
            while (nestedCurrent)
            {
                Node *nextNode = nestedCurrent->next;
                nestedCurrent->next = current->next;
                if (current->next)
                {
                    current->next->previous = nestedCurrent;
                }
                current->next = nestedCurrent;
                nestedCurrent->previous = current;
                nestedCurrent = nextNode;
            }
            current->nestedNode = nullptr;
        }
        current = current->next;
    }
}

void BookList::printList() const
{
    if (!head)
    {
        cout << "\nNo list to print.\n";
        return;
    }

    Node *current = head;
    while (current)
    {
        cout << current->id << " ";
        Node *nestedCurrent = current->nestedNode;
        while (nestedCurrent)
        {
            cout << "\n  Volume/Series of book " << current->id << ": " << nestedCurrent->id << " ";
            nestedCurrent = nestedCurrent->next;
        }
        current = current->next;
    }
    cout << endl;
}

void BookList::inputBook()
{
    int id;
    bool hasNested;
    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Does it have volumes/series? (1 for yes, 0 for no): ";
    cin >> hasNested;
    insertBook(id, hasNested);
}

void Menu()
{
    puts("-------------------------------------");
    puts("| 1. Add a book                    | ");
    puts("| 2. Print books                   | ");
    puts("| 3. Flatten list                  | ");
    puts("| 4. Exit                          | ");
    puts("-------------------------------------");
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
    BookList books;
    bool programExit = false;
    do
    {
        Menu();
        cout << "Enter your choice: ";
        string input;
        cin >> input;
        char choice = inputHandler(input);
        switch (choice)
        {
        case '1':
            books.inputBook();
            break;
        case '2':
            books.printList();
            break;
        case '3':
            books.flattenList();
            books.printList();
            break;
        case '4':
            cout << "Program is going to Exit " << endl;
            programExit = true;
            break;
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }
    } while (!programExit);

    return 0;
}
