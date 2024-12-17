#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class HashTableChaining
{
    vector<list<int>> table;
    int size;

    int hashFunction(int key)
    {
        return key % size;
    }

public:
    HashTableChaining(int s) : size(s)
    {
        table.resize(size);
    }

    void insert(int key)
    {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    void display()
    {
        for (int i = 0; i < size; ++i)
        {
            cout << i << ": ";
            for (auto &x : table[i])
                cout << x << " -> ";
            cout << endl;
        }
    }
};

class HashTableBucketing
{
    vector<vector<int>> table;
    int size;
    int bucketSize;

    int hashFunction(int key)
    {
        return key % size;
    }

public:
    HashTableBucketing(int s, int b) : size(s), bucketSize(b)
    {
        table.resize(size, vector<int>(0));
    }

    void insert(int key)
    {
        int index = hashFunction(key);
        if (table[index].size() < bucketSize)
            table[index].push_back(key);
        else
            rehash();
    }

    void rehash()
    {
        size *= 2;
        vector<vector<int>> newTable(size, vector<int>(0));
        for (auto &bucket : table)
        {
            for (auto &key : bucket)
            {
                int index = key % size;
                newTable[index].push_back(key);
            }
        }
        table = newTable;
    }

    void display()
    {
        for (int i = 0; i < size; ++i)
        {
            cout << i << ": ";
            for (auto &x : table[i])
                cout << x << " ";
            cout << endl;
        }
    }
};

int main()
{
    int keys[] = {17, 26, 15, 9, 11, 43, 75, 19, 35, 45, 55, 9, 10, 21, 61, 23};
    int n = sizeof(keys) / sizeof(keys[0]);

    cout << "Chaining:" << endl;
    HashTableChaining ht1(10);
    for (int i = 0; i < n; ++i)
        ht1.insert(keys[i]);
    ht1.display();

    cout << endl
         << "Bucketing:" << endl;
    HashTableBucketing ht2(10, 3);
    for (int i = 0; i < n; ++i)
        ht2.insert(keys[i]);
    ht2.display();

    return 0;
}
