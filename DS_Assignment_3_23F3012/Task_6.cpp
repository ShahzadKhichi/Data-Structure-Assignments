#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int data, height;
    Node *left;
    Node *right;
    Node(int d)
    {
        data = d;
        left = right = NULL;
        height = 1;
    }
};
class AVL
{
private:
    Node *root;
    int getheight(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        return root->height;
    }
    int getbalance(Node *root)
    {
        return getheight(root->left) - getheight(root->right);
    }
    Node *leftRotation(Node *root)
    {
        Node *child = root->right;
        Node *childleft = child->left;
        child->left = root;
        root->right = childleft;
        root->height = 1 + max(getheight(root->left), getheight(root->right));
        child->height = 1 + max(getheight(child->left), getheight(root->right));
        return child;
    }
    Node *rightRotation(Node *root)
    {
        Node *child = root->left;
        Node *childright = child->right;
        child->right = root;
        root->left = childright;
        root->height = 1 + max(getheight(root->left), getheight(root->right));
        child->height = 1 + max(getheight(child->left), getheight(root->right));
        return child;
    }
    Node *makeBSTBalance(Node *root, int d)

    {
        root->height = 1 + max(getheight(root->left), getheight(root->right));

        int balance = getbalance(root);

        if (balance > 1 && d < root->left->data)
        {
            return rightRotation(root);
        }

        else if (balance < -1 && d > root->right->data)
        {
            return leftRotation(root);
        }

        else if (balance > 1 && d > root->left->data)
        {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }

        else if (balance < -1 && d < root->right->data)
        {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        else
        {
            return root;
        }
    }
    Node *insert(Node *root, int d)
    {
        Node *temp = new Node(d);
        if (root == NULL)
        {
            return temp;
        }
        if (d < root->data)
        {
            root->left = insert(root->left, d);
        }
        else if (d > root->data)
        {
            root->right = insert(root->right, d);
        }
        else
        {
            return root;
        }
        return makeBSTBalance(root, d);
    }
    Node *deleteNode(Node *root, int d)
    {
        if (root == NULL)
        {
            return NULL;
        }
        if (d < root->data)
        {
            root->left = deleteNode(root->left, d);
        }
        else if (d > root->data)
        {
            root->right = deleteNode(root->right, d);
        }
        else
        {

            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }

            else if (root->left != NULL && root->right == NULL)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            else if (root->left == NULL && root->right != NULL)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }

            else if (root->left != NULL && root->right != NULL)
            {
                Node *current = root->left;
                while (current->left != NULL)
                {
                    current = current->right;
                }
                root->data = current->data;
                root->left = deleteNode(root->left, current->data);
            }
        }

        return makeBSTBalance(root, d);
    }
    void TreeInArray(Node *root, vector<int> &v)
    {
        if (root == NULL)
        {
            return;
        }
        TreeInArray(root->left, v);
        v.push_back(root->data);
        TreeInArray(root->right, v);
    }
    void display(Node *root)
    {
        if (!root)
            return;
        display(root->left);
        cout << root->data << " ";
        display(root->right);
    }

public:
    AVL()
    {
        root = NULL;
    }
    void insertNodes()
    {
        int n;
        cout << "Enter Number of Nodes : ";
        cin >> n;
        while (n--)
        {
            int data;
            cout << "Enter data ";
            cin >> data;
            root = insert(root, data);
        }
    }
    void inOrder()
    {
        cout << "Nodes : ";
        display(root);
        cout << endl;
    }
    void deleteKthLargest()
    {
        int k;
        cout << "Enter k : ";
        cin >> k;

        vector<int> v;
        TreeInArray(root, v);
        if (k > v.size())
        {
            cout << "Out of Range " << endl;
            return;
        }
        else
        {
            root = deleteNode(root, v[v.size() - k]);
        }
    }
};
int main()
{
    AVL tree;
    tree.insertNodes();
    tree.inOrder();
    tree.deleteKthLargest();
    tree.inOrder();

    system("pause");
    return 0;
}