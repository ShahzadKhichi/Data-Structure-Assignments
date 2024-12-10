#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    bool val;
    Node(bool val)
    {
        this->val = val;
        left = NULL;
        right = NULL;
    }
};

class BST
{

private:
    Node *root;
    vector<bool> arr;
    Node *BuildTree(Node *root, bool val)
    {
        if (!root)
        {
            root = new Node(val);
            return root;
        }

        if (root->val && val)
        {
            root->right = BuildTree(root->right, val);
        }
        else
        {
            root->left = BuildTree(root->left, val);
        }
        return root;
    }
    void preOrder(Node *root)
    {
        if (!root)
            return;

        cout << root->val << " ";
        preOrder(root->left);

        preOrder(root->right);
    }
    void makeTreeArr(Node *root)
    {
        if (!root)
            return;

        arr.push_back(root->val);
        makeTreeArr(root->left);

        makeTreeArr(root->right);
    }

public:
    BST()
    {
        root = NULL;
    }
    void andOfTree()
    {
        if (arr.size() == 0)
            makeTreeArr(root);

        bool result = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            result = result && arr[i];
        }
        cout << "Result of AND Operation : " << result << endl;
    }
    void xorOfTree()
    {
        if (arr.size() == 0)
            makeTreeArr(root);

        bool result = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            result = result xor arr[i];
        }
        cout << "Result of XOR Operation : " << result << endl;
    }
    void orOfTree()
    {
        if (arr.size() == 0)
            makeTreeArr(root);

        bool result = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            result = result or arr[i];
        }
        cout << "Result of OR Operation  : " << result << endl;
    }
    void insertNode()
    {
        bool val;
        int n;
        cout << "Enter Number of Nodes to add : ";
        cin >> n;
        while (n)
        {
            cout << "Enter Value : ";
            cin >> val;
            root = BuildTree(root, val);
            n--;
        }
    }
    void printTree()
    {
        cout << "\nNodes : ";
        preOrder(root);
        cout << endl;
    }
};

int main()
{
    BST tree;

    tree.insertNode();

    tree.printTree();

    tree.andOfTree();
    tree.xorOfTree();
    tree.orOfTree();

    return 0;
}