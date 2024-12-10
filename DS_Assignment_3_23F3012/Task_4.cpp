#include <iostream>
#include <string>

using namespace std;
class Node
{
public:
    Node *left;
    Node *right;
    Node *next;
    int freq;
    string name;
    int h;
    Node(int freq, string name)
    {
        left = NULL;
        right = NULL;
        next = NULL;
        this->freq = freq;
        this->name = name;
        h = 0;
    }
    void printSongs()
    {

        cout << this->name;

        Node *cur = next;
        while (cur)
        {
            cout << " , " << cur->name;

            cur = cur->next;
        }
        cout << " : Frequencey = " << this->freq << endl;
    }
};

class AVL
{
private:
    Node *root;
    int isBalanced(Node *root)
    {
        if (!root)
            return 0;
        int l = -1;
        int r = -1;
        if (root->left)
            l = root->left->h;
        if (root->right)
            r = root->right->h;

        return l - r;
    }
    int rootHight(Node *left, Node *right)
    {
        int l = -1;
        int r = -1;
        if (left)
            l = left->h;
        if (right)
            r = right->h;

        return 1 + max(l, r);
    }
    Node *rotateRight(Node *root)
    {

        Node *newRoot = root->left;
        Node *x = newRoot->right;
        newRoot->right = root;
        newRoot->right->left = x;

        newRoot->right->h = rootHight(newRoot->right->left, newRoot->right->right);
        newRoot->h = rootHight(newRoot->left, newRoot->right);
        return newRoot;
    }
    Node *rotateLeft(Node *root)
    {
        Node *newRoot = root->right;
        Node *x = newRoot->left;
        newRoot->left = root;
        newRoot->left->right = x;

        newRoot->left->h = rootHight(newRoot->left->left, newRoot->left->right);
        newRoot->h = rootHight(newRoot->left, newRoot->right);
        return newRoot;
    }
    void inOrder(Node *root)
    {
        if (!root)
            return;
        inOrder(root->left);
        cout << "h : " << root->h << " : ";
        root->printSongs();
        inOrder(root->right);
    }
    Node *makeTreeBalanced(Node *root, int freq)
    {

        root->h = rootHight(root->left, root->right);

        int bf = isBalanced(root);

        if (bf > 1 && root->left->freq > freq)
        {
            return rotateRight(root);
        }

        if (bf < -1 && root->right->freq < freq)
        {
            return rotateLeft(root);
        }

        if (bf > 1 && root->left->freq < freq)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (bf < -1 && root->right->freq > freq)
        {

            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }
    Node *buildAVL(Node *root, int freq, string name)
    {
        if (!root)
        {
            root = new Node(freq, name);
            return root;
        }
        if (root->name == name)
        {
            root->freq += freq;
            return root;
        }
        if (root->freq > freq)
        {
            root->left = buildAVL(root->left, freq, name);
            return makeTreeBalanced(root, freq);
        }
        else if (root->freq < freq)
        {
            root->right = buildAVL(root->right, freq, name);
            return makeTreeBalanced(root, freq);
        }
        else
        {

            root->next = buildAVL(root->next, freq, name);
            return root;
        }
    }

    Node *searchNode(Node *root, string name, bool &flag, bool &found, bool &internal)
    {
        if (!root)
            return root;

        if (root->name == name)
        {
            flag = true;
            found = true;
            return deleteNode(root);
        }
        Node *cur = root->next;
        Node *pre = root;
        while (cur)
        {
            if (cur->name == name)
            {
                found = true;
                internal = true;
                if (pre == root)
                {

                    root->next = cur->next;
                    root = buildAVL(root, cur->freq + 1, cur->name);
                    delete cur;
                    return root;
                }
                else if (!cur->next)
                {

                    pre->next = NULL;
                    root = buildAVL(root, cur->freq + 1, cur->name);
                    delete cur;
                    return root;
                }
                else
                {
                    pre->next = cur->next;
                    root = buildAVL(root, cur->freq + 1, cur->name);
                    delete cur;
                    return root;
                }
            }
            pre = cur;
            cur = cur->next;
        }

        int freq = root->freq;
        string str = root->name;
        Node *next = NULL;
        if (root->left)
        {
            freq = root->left->freq;
            str = root->left->name;
            next = root->left->next;
        }

        root->left = searchNode(root->left, name, flag, found, internal);
        if (flag)
        {
            while (next)
            {
                root = buildAVL(root, next->freq, next->name);
                next = next->next;
            }
            this->root = buildAVL(this->root, freq + 1, str);
            flag = false;
        }
        if (root->right)
        {
            freq = root->right->freq;
            str = root->right->name;
            next = root->right->next;
        }

        root->right = searchNode(root->right, name, flag, found, internal);
        if (flag)
        {
            while (next)
            {
                root = buildAVL(root, next->freq, next->name);
                next = next->next;
            }
            root = buildAVL(root, freq + 1, str);
            flag = false;
        }
        return root;
    }

    Node *min(Node *root)
    {
        if (!root)
            return NULL;
        while (root->left)
        {
            root = root->left;
        }
        return root;
    }
    Node *searchNodeByFreq(Node *root, int freq)
    {
        if (!root)
            return NULL;

        if (root->freq == freq)
            return deleteNode(root);

        if (root->freq > freq)
            root->left = searchNodeByFreq(root->left, freq);
        else
            root->right = searchNodeByFreq(root->right, freq);

        return root;
    }
    Node *deleteNode(Node *root)
    {

        if (!root->left && !root->right)
        {
            delete root;
            return NULL;
        }
        else if (root->left && !root->right)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        else if (!root->left && root->right)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else
        {
            Node *temp = min(root->right);
            int mini = temp->freq;
            root->freq = mini;
            root->name = temp->name;
            root->next = temp->next;
            root->right = searchNodeByFreq(root->right, mini);
            return root;
        }
    }

    Node *incPlaySong(Node *root, string name)
    {
        bool flag = false;
        bool found = false;
        bool internal = false;
        int freq = 0;
        string str = "";
        Node *next = NULL;
        if (root)
        {
            freq = root->freq;
            str = root->name;
            next = root->next;

            root = searchNode(root, name, flag, found, internal);
            if ((!root || root->name != str) && !internal)
            {
                while (next)
                {
                    root = buildAVL(root, next->freq, next->name);
                    Node *temp = next;
                    next = next->next;
                    delete next;
                }
                root = buildAVL(root, freq + 1, str);
            }
            if (!found)
            {
                cout << "Song Not found.Please insert a valid song name " << endl;
            }
            return root;
        }
        cout << "PlayList is Empty " << endl;
        return NULL;
    }

public:
    AVL()
    {
        root = NULL;
    }
    void insertSong()
    {
        int freq, n;
        string name;

        cout << "Enter Numbe of Songs : ";
        cin >> n;
        while (n)
        {
            cout << "Enter Name : ";
            cin >> name;
            cout << "Enter Frequencey : ";
            cin >> freq;

            root = buildAVL(root, freq, name);
            n--;
        }
    }
    void printSongs()
    {
        cout << endl;
        inOrder(root);
    }
    void playASOng()
    {
        string name;
        cout << "Enter Song Name To Pay it name : ";
        cin >> name;
        root = incPlaySong(root, name);
    }
};
int main()
{
    AVL tree; // 11 a 1 b 5 c 9 d 2 e 4 f 6 g 8 h 3 i 7  j 9 k 5
    tree.insertSong();
    tree.printSongs();
    tree.playASOng();
    tree.printSongs();

    system("pause");
    return 0;
}