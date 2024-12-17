#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int nextPrime(int n)
{
    while (!isPrime(n))
    {
        n++;
    }
    return n;
}

class HashTable
{
private:
    vector<int> table;
    int tableSize;
    int numElements;

    int hash(int key)
    {
        return key % tableSize;
    }

    int secondaryHash(int key)
    {
        return 1 + (key % (tableSize - 1));
    }

    void rehash()
    {
        int oldSize = tableSize;
        tableSize = nextPrime(2 * tableSize);
        vector<int> oldTable = table;

        table.clear();
        table.resize(tableSize, -1);
        numElements = 0;

        for (int i = 0; i < oldSize; i++)
        {
            if (oldTable[i] != -1)
            {
                insertLinearProbing(oldTable[i]);
            }
        }
    }

public:
    HashTable(int size)
    {
        tableSize = size;
        table.resize(size, -1);
        numElements = 0;
    }

    void insertLinearProbing(int key)
    {
        int index = hash(key);
        while (table[index] != -1)
        {
            index = (index + 1) % tableSize;
        }
        table[index] = key;
        numElements++;
        if ((float)numElements / tableSize > 0.7)
        {
            rehash();
        }
    }

    void insertQuadraticProbing(int key)
    {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % tableSize] != -1)
        {
            i++;
        }
        table[(index + i * i) % tableSize] = key;
        numElements++;
        if ((float)numElements / tableSize > 0.7)
        {
            rehash();
        }
    }

    void insertDoubleHashing(int key)
    {
        int index = hash(key);
        int step = secondaryHash(key);
        while (table[index] != -1)
        {
            index = (index + step) % tableSize;
        }
        table[index] = key;
        numElements++;
        if ((float)numElements / tableSize > 0.7)
        {
            rehash();
        }
    }

    void display()
    {
        for (int i = 0; i < tableSize; i++)
        {
            if (table[i] == -1)
            {
                cout << "_ ";
            }
            else
            {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};

int main()
{
    vector<int> ISBNs = {17, 26, 15, 9, 11, 43, 75, 19, 35, 45, 55, 9, 10, 21, 61, 23};

    cout << "--- Linear Probing ---" << endl;
    HashTable linearTable(15);
    for (int isbn : ISBNs)
    {
        linearTable.insertLinearProbing(isbn);
    }
    cout << "Final State of Hash Table:" << endl;
    linearTable.display();

    cout << endl
         << "--- Quadratic Probing ---" << endl;
    HashTable quadraticTable(15);
    for (int isbn : ISBNs)
    {
        quadraticTable.insertQuadraticProbing(isbn);
    }
    cout << "Final State of Hash Table:" << endl;
    quadraticTable.display();

    cout << endl
         << "--- Double Hashing ---" << endl;
    HashTable doubleHashTable(15);
    for (int isbn : ISBNs)
    {
        doubleHashTable.insertDoubleHashing(isbn);
    }
    cout << "Final State of Hash Table:" << endl;
    doubleHashTable.display();

    return 0;
}
