#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node
{
    int studentID;
    string name;
    int department;
    Node *left;
    Node *right;

    Node(int id, string n, int dept)
        : studentID(id), name(n), department(dept), left(nullptr), right(nullptr)
    {
    }
};

class AVL
{
private:
    Node *root;

    int height(Node *node)
    {
        return node ? 1 + max(height(node->left), height(node->right)) : -1;
    }

    int balanceFactor(Node *node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void rightRotate(Node *&node)
    {
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node = temp;
    }

    void leftRotate(Node *&node)
    {
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node = temp;
    }

    void balanceNode(Node *&node)
    {
        if (!node)
            return;

        int balance = balanceFactor(node);

        if (balance > 1)
        {
            if (balanceFactor(node->left) < 0)
            {
                leftRotate(node->left);
            }
            rightRotate(node);
        }
        else if (balance < -1)
        {
            if (balanceFactor(node->right) > 0)
            {
                rightRotate(node->right);
            }
            leftRotate(node);
        }
    }

    void insert(Node *&node, int id, string name)
    {
        int department = getDepartmentFromID(id);
        if (!node)
        {
            node = new Node(id, name, department);
            return;
        }

        if (id < node->studentID)
        {
            insert(node->left, id, name);
        }
        else if (id > node->studentID)
        {
            insert(node->right, id, name);
        }
        else
        {
            cout << "Duplicate Student ID is not allowed!\n";
            return;
        }

        balanceNode(node);
    }

    void deleteNode(Node *&node, int id)
    {
        if (!node)
            return;

        if (id < node->studentID)
        {
            deleteNode(node->left, id);
        }
        else if (id > node->studentID)
        {
            deleteNode(node->right, id);
        }
        else
        {
            if (!node->left || !node->right)
            {
                Node *temp = node->left ? node->left : node->right;
                delete node;
                node = temp;
            }
            else
            {
                Node *temp = getMin(node->right);
                node->studentID = temp->studentID;
                node->name = temp->name;
                node->department = temp->department;
                deleteNode(node->right, temp->studentID);
            }
        }

        balanceNode(node);
    }

    Node *getMin(Node *node)
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

    string getDepartmentName(int departmentID)
    {
        switch (departmentID)
        {
        case 1:
            return "CS (Computer Science)";
        case 2:
            return "SE (Software Engineering)";
        case 3:
            return "EE (Electrical Engineering)";
        case 4:
            return "S&H (Science & Humanities)";
        case 5:
            return "FSM (Food Science & Management)";
        default:
            return "Unknown Department";
        }
    }

    int getDepartmentFromID(int studentID)
    {
        return studentID / 1000;
    }

    void displayTree(Node *node)
    {
        if (!node)
            return;

        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            cout << "Student ID: " << current->studentID << ", Name: " << current->name << ", Department: " << getDepartmentName(current->department) << endl;

            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
    }

    Node *search(Node *node, int id)
    {
        if (!node || node->studentID == id)
        {
            return node;
        }

        if (id < node->studentID)
        {
            return search(node->left, id);
        }
        else
        {
            return search(node->right, id);
        }
    }

    void updateDepartment(Node *&node, int oldID, int newDepartment)
    {
        Node *found = search(node, oldID);
        if (!found)
        {
            cout << "Student not found!" << endl;
            return;
        }
        string studentName = found->name;
        int uniquePart = oldID % 1000;
        int newID = newDepartment * 1000 + uniquePart;
        deleteNode(node, oldID);
        insert(node, newID, studentName);

        cout << "Student updated successfully! New ID: " << newID << endl;
    }

public:
    AVL() : root(nullptr) {}

    void insert(int id, string name)
    {
        insert(root, id, name);
    }

    void remove(int id)
    {
        deleteNode(root, id);
    }

    void display()
    {
        cout << "\n\tLevel Order Traversal\n";
        displayTree(root);
    }

    void updateStudentDepartment(int oldID, int newDepartment)
    {
        updateDepartment(root, oldID, newDepartment);
    }
};
void Menu()
{
    puts(" MENU ");
    puts("Input 1 to Add Student");
    puts("Input 2 to Remove Student");
    puts("Input 3 to Update Student Department");
    puts("Input 4 to Print Students");
    puts("Input 5 to Exit");
    puts("Input your choice: ");
}
int main()
{
    AVL tree;
    int choice;
    string name;
    int id, newDepartment;
    bool exitPrograme = false;
    do
    {
        Menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Student ID : ";
            cin >> id;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, name);
            tree.insert(id, name);
            break;

        case 2:
            cout << "Enter Student ID to remove: ";
            cin >> id;
            tree.remove(id);
            break;

        case 3:
            cout << "Enter Student ID to update: ";
            cin >> id;
            cout << "Enter New Department \n1 for CS\n2 for SE\n3 for EE\n4 for S&H\n5 for FSM\n: ";
            cin >> newDepartment;
            tree.updateStudentDepartment(id, newDepartment);
            break;

        case 4:
            tree.display();
            break;

        case 5:
            cout << "Program is Exiting . ." << endl;
            exitPrograme = true;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (!exitPrograme);

    system("pause");
    return 0;
}