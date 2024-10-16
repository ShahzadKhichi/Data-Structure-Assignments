#include <iostream>
#include <cmath>
using namespace std;
class Term
{
public:
    int coefficient;
    int exponent;
    Term *next;
    Term(int coefficient, int exponent)
    {
        this->coefficient = coefficient;
        this->exponent = exponent;
        this->next = NULL;
    }
};
class Polynomial
{
private:
    void insertAtTail(Term *newTerm);
    void insertAthead(Term *newTerm);
    Term *exponentAlreadyExist(int exponent);
    void deletePloynomial();

public:
    Term *firstTerm = NULL;
    Term *lastTerm = NULL;
    int size = 0;
    void Input();
    void displayPolynomial();
    Polynomial &operator+(Polynomial &obj);
    int operator()(int val);
    Polynomial *operator*(Polynomial &obj);

    ~Polynomial();
};
void Polynomial::insertAtTail(Term *newTerm)
{
    if (lastTerm == NULL)
    {
        firstTerm = newTerm;
        lastTerm = newTerm;
        return;
    }
    lastTerm->next = newTerm;
    lastTerm = newTerm;
}
void Polynomial::insertAthead(Term *newTerm)
{
    if (firstTerm == NULL)
    {
        firstTerm = newTerm;
        lastTerm = newTerm;
        return;
    }
    newTerm->next = firstTerm;
    firstTerm = newTerm;
}
Term *Polynomial::exponentAlreadyExist(int exponent)
{
    Term *current = firstTerm;
    while (current)
    {
        if (current->exponent == exponent)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void Polynomial::Input()
{
    deletePloynomial();
    cout << "Enter Number of terms : ";
    cin >> size;
    int c, e;
    int count = 0;
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        cout << "Enter coffient of " << i + 1 << " Term  : ";
        cin >> c;
        cout << "Enter exponent of " << i + 1 << " Term  : ";
        cin >> e;
        if (c == 0)
        {
            count++;
        }
        if (i == 0)
        {

            Term *newTerm = new Term(c, e);
            max = e;
            insertAthead(newTerm);
        }
        else
        {

            Term *already = exponentAlreadyExist(e);

            if (already)
            {
                already->coefficient = already->coefficient + c;
                count++;
            }
            else
            {
                Term *newTerm = new Term(c, e);
                if (max > e)
                {
                    insertAtTail(newTerm);
                    max = e;
                }
                else
                {
                    insertAthead(newTerm);
                }
            }
        }
    }
    size -= count;
}
void Polynomial::displayPolynomial()
{
    Term *current = firstTerm;
    while (current)
    {
        // current->displayTerm();
        if (current == firstTerm)
        {
            if (current->coefficient != 1)
                cout << current->coefficient;
            if (current->exponent != 0)
            {
                cout << "n^" << current->exponent << " ";
            }
        }
        else
        {
            if (current->coefficient > 0)
            {
                cout << " + ";
            }
            if (current->coefficient != 1)
                cout << current->coefficient;
            if (current->exponent != 0)
            {
                if (current->exponent != 1)
                    cout << "n^" << current->exponent << " ";
                else
                    cout << "n";
            }
        }
        current = current->next;
    }
}
void Polynomial::deletePloynomial()
{
    while (firstTerm)
    {
        Term *temp = firstTerm;
        firstTerm = firstTerm->next;
        delete temp;
        size--;
    }
}
Polynomial::~Polynomial()
{
    deletePloynomial();
}
Polynomial &Polynomial::operator+(Polynomial &obj)
{
    Term *current1 = firstTerm;
    Term *current2 = obj.firstTerm;
    Term *pre1 = NULL;
    Term *pre2 = NULL;
    while (current1 && current2)
    {
        if (current1->exponent == current2->exponent)
        {
            current1->coefficient += current2->coefficient;
            pre1 = current1;
            current1 = current1->next;
            pre2 = current2;
            current2 = current2->next;
        }
        else if (current1->exponent > current2->exponent)
        {
            current1 = current1->next;
        }
        else
        {
            Term *newNode = new Term(current2->coefficient, current2->exponent);
            if (current1 == firstTerm)
            {
                insertAthead(newNode);
            }
            else
            {
                newNode->next = pre1->next;
                pre1->next = newNode;
            }
            current2 = current2->next;
        }
    }
    while (current2)
    {
        Term *newNode = new Term(current2->coefficient, current2->exponent);
        insertAtTail(newNode);
        current2 = current2->next;
    }

    return *this;
}
int Polynomial::operator()(int val)
{
    int result = 0;
    Term *current = firstTerm;
    while (current)
    {
        result += current->coefficient * pow(val, current->exponent);
        current = current->next;
    }
    return result;
}
Polynomial *Polynomial::operator*(Polynomial &obj)
{
    Polynomial *newObj = new Polynomial;
    if (size > obj.size)
    {
        Term *current2 = obj.firstTerm;
        Term *pre1 = NULL;
        Term *pre2 = NULL;
        while (current2)
        {
            Term *current1 = firstTerm;
            while (current1)
            {
                int c = current1->coefficient * current2->coefficient;
                int e = current1->exponent + current2->exponent;
                Term *newTerm = newObj->exponentAlreadyExist(e);
                if (newTerm)
                {
                    newTerm->coefficient += c;
                }
                else
                {
                    newTerm = new Term(c, e);
                    newObj->insertAtTail(newTerm);
                }
                current1 = current1->next;
            }

            current2 = current2->next;
        }
    }
    else
    {
        Term *current2 = firstTerm;
        Term *pre1 = NULL;
        Term *pre2 = NULL;
        while (current2)
        {
            Term *current1 = obj.firstTerm;
            while (current1)
            {
                int c = current1->coefficient * current2->coefficient;
                int e = current1->exponent + current2->exponent;

                Term *newTerm = newObj->exponentAlreadyExist(e);
                if (newTerm)
                {
                    newTerm->coefficient += c;
                }
                else
                {
                    newTerm = new Term(c, e);
                    newObj->insertAtTail(newTerm);
                }
                current1 = current1->next;
            }
            current2 = current2->next;
        }
    }
    return newObj;
}
void menu()
{
    cout << "---------------------------------------------------------" << endl;
    puts("| Enter 1 : Insert Polynomial 1          :              |");
    puts("| Enter 2 : Insert Polynomial 2          :              |");
    puts("| Enter 3 : print Polynomial 1           :              |");
    puts("| Enter 4 : print Polynomial 2           :              |");
    puts("| Enter 5 : To Add polynomial 1 & 2      :              |");
    puts("| Enter 6 : To Multiply Polynomial 1 & 2 :              |");
    puts("| Enter 7 : To Evaluate Polynomials      :              |");
    puts("| Enter 8 : To Exit programe             :              |");
    cout << "---------------------------------------------------------" << endl;
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

    string str;
    Polynomial first, second;
    bool programeExit = false;
    bool poly1 = false;
    bool poly2 = false;
    do
    {

        menu();
        cout << "Enter your choice : ";
        cin >> str;
        char choice = inputHandler(str);
        switch (choice)
        {
        case '1':
            first.Input();
            poly1 = true;
            break;
        case '2':
            second.Input();
            poly2 = true;
            break;
        case '3':
            if (!poly1)
            {
                cout << "Please Enter Polynomial 1 first " << endl;
            }
            else
            {
                cout << "Polynomila 1 : ";
                first.displayPolynomial();
                cout << endl;
            }
            break;
        case '4':
            if (!poly2)
            {
                cout << "Please Enter Polynomial 2 first " << endl;
            }
            else
            {
                cout << "Polynomila 2 : ";
                second.displayPolynomial();
                cout << endl;
            }
            break;
        case '5':
            if (!poly1)
            {
                cout << "Please Enter Polynomial 1 first " << endl;
            }
            else if (!poly2)
            {
                cout << "Please Enter Polynomial 2 first " << endl;
            }
            else
            {
                cout << "( ";
                first.displayPolynomial();
                cout << " ) + ( ";
                second.displayPolynomial();
                cout << " )" << " =  ";

                first + second;

                first.displayPolynomial();
                cout << endl;
            }
            break;
        case '6':
            if (!poly1)
            {
                cout << "Please Enter Polynomial 1 first " << endl;
            }
            else if (!poly2)
            {
                cout << "Please Enter Polynomial 2 first " << endl;
            }
            else
            {
                cout << "( ";
                first.displayPolynomial();
                cout << " ) * ( ";
                second.displayPolynomial();
                cout << " )" << " =  ";
                Polynomial *product = first * second;

                product->displayPolynomial();
                cout << endl;
                delete product;
                product = NULL;
            }
            break;
        case '7':
            if (!poly1)
            {
                cout << "Please Enter Polynomial 1 first " << endl;
            }
            else if (!poly2)
            {
                cout << "Please Enter Polynomial 2 first " << endl;
            }
            else
            {
                int n;
                cout << "Enter value for n : ";
                cin >> n;
                cout << endl;
                first.displayPolynomial();
                cout << " = " << first(n) << endl;
                second.displayPolynomial();
                cout << " = " << second(n) << endl;
            }
            break;
        case '8':
            programeExit = true;
            cout << "Programe is going to exit " << endl;
            break;

        default:
            cout << "Invalid Input . Please Enter a valid Input " << endl;
            break;
        }
    } while (!programeExit);
    system("pause");
    return 0;
}