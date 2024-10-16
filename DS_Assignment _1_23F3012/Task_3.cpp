#include <iostream>
#include <string>
using namespace std;
class Node
{
public:
    string action;
    Node *next;
    Node *pre;
    Node(string);
};
Node::Node(string action)
{
    this->action = action;
    next = NULL;
    pre = NULL;
}
class Actions
{
private:
    Node *orgHead;
    Node *hisHead;
    Node *orgTail;
    Node *hisTail;
    int orgSize;
    int hisSize;
    void addActionHis(Node *node);

public:
    Actions();
    void displayHis();
    void displayOrg();
    void addAction(string, Node *);
    void UndoAction();
    void redoAction();
    void deleteAction();
    void deleteNode(Node *);
    void mostRecentAction();
    Node *findAction(int, Node *);
    ~Actions();
};
Actions::Actions()
{
    orgHead = NULL;
    hisHead = NULL;
    orgSize = 0;
    hisSize = 0;
}
void Actions::displayHis()
{
    if (!hisHead)
    {
        cout << "List is Empty ." << endl;
        return;
    }
    Node *current = hisHead;
    int count = 1;
    while (current)
    {
        cout << count << ". " << current->action << endl;
        current = current->next;
        count++;
    }
    cout << endl;
}
void Actions::displayOrg()
{
    if (!orgHead)
    {
        cout << "List is Empty ." << endl;
        return;
    }
    Node *current = orgHead;
    int count = 1;
    while (current)
    {
        cout << count << ". " << current->action << endl;
        current = current->next;
        count++;
    }
    cout << endl;
}
void Actions::addActionHis(Node *node)
{
    if (!hisHead)
    {
        hisHead = node;
        hisTail = node;
        node->next = NULL;
        node->pre = NULL;
        return;
    }
    hisTail->next = node;
    node->pre = hisTail;
    hisTail = node;
    hisTail->next = NULL;
}
void removeAction(Node *node)
{
    if (node->next)
    {
        node->next->pre = node->pre;
    }
    if (node->pre)
    {
        node->pre->next = node->next;
    }
}
void Actions::addAction(string action, Node *node = NULL)
{
    Node *newNode;
    orgSize++;
    if (!node)
    {
        newNode = new Node(action);
    }
    else
    {
        newNode = node;
    }

    if (!orgHead)
    {

        orgHead = newNode;
        orgTail = orgHead;
        newNode->next = NULL;
        newNode->pre = NULL;
        return;
    }
    orgTail->next = newNode;
    newNode->pre = orgTail;
    orgTail = newNode;
    orgTail->next = NULL;
}
void Actions::UndoAction()
{

    if (orgHead == NULL)
    {
        cout << "There is No Action to Undo.Please add an Action First " << endl;
        return;
    }
    displayOrg();
    int n;
    cout << "Enter number of Action : ";
    cin >> n;
    if (n < 1 || n > orgSize)
    {
        cout << "Out Range : " << endl;
        return;
    }

    Node *action = findAction(n, orgHead);

    if (action == orgTail)
    {
        orgTail = orgTail->pre;
        orgTail->next = NULL;
    }
    if (action != orgHead)
    {
        removeAction(action);
    }
    else
    {
        orgHead = orgHead->next;
    }
    addActionHis(action);
    orgSize--;
    hisSize++;
}
Node *Actions::findAction(int n, Node *head)
{
    int count = 1;
    while (head)
    {
        if (count == n)
        {
            return head;
        }
        count++;
        head = head->next;
    }
    return NULL;
}
void Actions::deleteNode(Node *node)
{

    if (node == orgHead)
    {
        if (orgSize == 1)
        {
            delete orgHead;
            orgHead = NULL;
        }
        else
        {
            orgHead = orgHead->next;
            delete orgHead->pre;
            orgHead->pre = NULL;
        }
        orgSize--;
        return;
    }
    if (node->next == NULL)
    {
        node = node->pre;
        delete node->next;
        node->next == NULL;
        orgSize--;
        return;
    }
    node->pre->next = node->next;
    node->next->pre = node->pre;
    delete node;
    orgSize--;
    return;
}
void Actions::mostRecentAction()
{
    if (orgHead == NULL)
    {
        cout << "There is No Recent  Action. " << endl;
        return;
    }
    cout << "Most Recent Action : " << orgTail->action << endl;
}
void Actions::redoAction()
{
    if (hisHead == NULL)
    {
        cout << "There is No Action to redo.Please add an Action First " << endl;
        return;
    }
    displayHis();
    int n;
    cout << "Enter number of Action : ";
    cin >> n;
    if (n < 1 || n > hisSize)
    {
        cout << "Out Range : " << endl;
        return;
    }
    Node *action = findAction(n, hisHead);
    if (action != hisHead)
    {
        removeAction(action);
    }
    else
    {
        hisHead = hisHead->next;
    }
    addAction("", action);
    hisSize--;
}
void Actions::deleteAction()
{
    if (orgHead == NULL)
    {
        cout << "There is  No Action to delete ." << endl;
        return;
    }
    displayOrg();
    int n;
    cout << "Enter number of Action : ";
    cin >> n;
    if (n < 1 || n > orgSize)
    {
        cout << "Out Range : " << endl;
        return;
    }
    Node *node = findAction(n, orgHead);
    deleteNode(node);
    orgSize--;
    return;
}
Actions::~Actions()
{

    while (orgHead)
    {
        deleteNode(orgHead);
    }
    while (hisHead && hisHead->next)
    {
        hisHead = hisHead->next;

        delete hisHead->pre;
        hisHead->pre = NULL;
    }
    delete hisHead;
}
void menu()
{
    cout << "----------------------------------------------" << endl;
    puts("| Enter 1 To add a new Action              : |");
    puts("| Enter 2 To display ACtion History        : |");
    puts("| Enter 3 To Undo An Action                : |");
    puts("| Enter 4 To display Undo Actions          : |");
    puts("| Enter 5 To redo An Action                : |");
    puts("| Enter 6 To delete An Action              : |");
    puts("| Enter 7 Most Recent Action               : |");
    puts("| Enter 8 To Exit Programe                 : |");
    cout << "----------------------------------------------" << endl;
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
    Actions act;
    bool programeExit = false;

    do
    {
        cout << endl;
        string input;
        string action;
        menu();
        cout << "Enter your choice : ";
        cin >> input;
        char choice = inputHandler(input);
        switch (choice)
        {
        case '1':
            cin.ignore();
            cout << "Enter Action : ";

            getline(cin, action);

            act.addAction(action);
            break;
        case '2':
            cout << "Action History : " << endl;
            act.displayOrg();
            break;
        case '3':
            cout << "Actions List : " << endl;
            act.UndoAction();
            break;
        case '4':
            cout << "Undo Actions List : " << endl;
            act.displayHis();
            break;
        case '5':
            cout << "Undo Actions List : " << endl;
            act.redoAction();
            break;
        case '6':
            act.deleteAction();
            break;
        case '7':
            act.mostRecentAction();
            break;
        case '8':
            cout << "Programe is going to Exit " << endl;
            programeExit = true;
            break;

        default:
            cout << "Enter Invalid choice . Please try again Later " << endl;
            break;
        }
    } while (!programeExit);

    system("pause");
    return 0;
}