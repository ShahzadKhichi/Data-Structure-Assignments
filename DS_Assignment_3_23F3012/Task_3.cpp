#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    int val;
    Node(int val)
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

    Node *BuildTree(Node *root, int val)
    {
        if (!root)
        {
            root = new Node(val);
            return root;
        }

        if (root->val < val)
        {
            root->right = BuildTree(root->right, val);
        }
        else if (root->val > val)
        {
            root->left = BuildTree(root->left, val);
        }
        return root;
    }
    void inOrder(Node *root)
    {
        if (!root)
            return;

        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }
    int rightVal(Node *root)
    {
        if (!root->right)
            return root->val;

        return root->right->val;
    }

    int makeGreaterTree(Node *root, int temp = 0)
    {
        if (!root)
            return temp;

        root->val += makeGreaterTree(root->right, temp);

        return max(makeGreaterTree(root->left, root->val), root->val);
    }

public:
    BST()
    {
        root = NULL;
    }

    void insertNode()
    {
        int val;
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
        inOrder(root);
        cout << endl;
    }
    void GreaterTree()
    {
        makeGreaterTree(root);
    }
};

int main()
{
    BST tree;

    tree.insertNode();
    cout << "\nBefore : ";
    tree.printTree();
    cout << "After : ";
    tree.GreaterTree();
    tree.printTree();

    return 0;
}