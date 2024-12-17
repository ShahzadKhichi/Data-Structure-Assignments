#include <iostream>
#include <vector>
#include <string>
using namespace std;

void heapify(vector<pair<int, string>> &heap, int i)
{
    int size = heap.size();
    int l = 2 * i;
    int r = 2 * i + 1;
    int smallest = i;

    if (l < size && heap[l].first < heap[i].first)
        smallest = l;

    if (r < size && heap[r].first < heap[i].first)
        smallest = r;

    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        heapify(heap, smallest);
    }
}
void buildHeap(vector<pair<int, string>> &heap)
{
    for (int i = heap.size() / 2; i >= 0; i--)
    {
        heapify(heap, i);
    }
}
int main() // a 1 15 a 2 10 a 3 20 a 4 8 a 5 12 a 6 25 a 7 18 a 8 5
{
    char i;
    int priority;
    string task;
    bool exit = false;
    vector<pair<int, string>> Tasks;
    do
    {

        cout << "        Task Scheduling System " << endl;
        cout << "a. Enter new Task " << endl;
        cout << "b. Extract Task with max Priority" << endl;
        cout << "c. Get top 3 Task " << endl;
        cout << "d. Exit" << endl;
        cout << "Enter choice : ";
        cin >> i;
        switch (i)
        {
        case 'a':
            cout << "Enter Task     : ";
            cin >> task;
            cout << "Enter Priority : ";
            cin >> priority;
            Tasks.push_back({priority, task});
            buildHeap(Tasks);
            break;
        case 'b':
            if (!Tasks.empty())
            {
                cout << "Task Name     : " << Tasks[0].second << endl;
                cout << "Task Priority : " << Tasks[0].first << endl;
                Tasks.erase(Tasks.begin());
                buildHeap(Tasks);
            }
            else
            {
                cout << "There are no Tasks" << endl;
            }
            break;
        case 'c':
            if (Tasks.size() > 3)
            {
                int count = 3;
                cout << "          Tasks " << endl;

                while (count--)
                {
                    cout << "Task Name     : " << Tasks[0].second << endl;
                    cout << "Task Priority : " << Tasks[0].first << endl;
                    Tasks.erase(Tasks.begin());
                    buildHeap(Tasks);
                }
            }
            else
            {
                cout << "Tasks are less than 3 " << endl;
            }
            break;
        case 'd':
            exit = true;
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
        cout << "Heap : ";
        for (auto i : Tasks)
        {
            cout << i.first << " ";
        }
        cout << endl;
    } while (!exit);

    return 0;
}