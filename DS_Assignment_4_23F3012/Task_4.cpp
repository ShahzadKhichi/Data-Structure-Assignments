#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;
int minKey(vector<pair<int, int>> &keyValues, vector<bool> &visited)
{

    int min = INT_MAX, min_index;

    // cout << "Key vales : ";
    for (int v = 0; v < keyValues.size(); v++)
    {
        // cout << "(" << keyValues[v].first << " , " << keyValues[v].second << ")" << " ";
        if (visited[v] == false && keyValues[v].first < min)
        {
            min = keyValues[v].first;
            min_index = v;
        }
    }
    // cout << endl;

    // cout << "Min : ";
    // cout << "(" << keyValues[min_index].first << " , " << keyValues[min_index].second << ")" << " ";
    // cout << endl;

    return min_index;
}

void printEgdesAndWieghts(vector<pair<int, int>> &parent, vector<vector<int>> &graph)
{
    int total = 0;
    cout << " Edges    Weights" << endl;
    for (int i = 1; i < graph.size(); i++)
    {
        cout << parent[i].second << " <-> " << i << "     " << graph[parent[i].second][i] << endl;
        total += graph[parent[i].second][i];
    }
    cout << "Total cost or weight : " << total << endl;
}
void primsAlgo(vector<vector<int>> &graph)
{

    vector<pair<int, int>> keyValues(graph.size());
    vector<bool> visited(graph.size());
    for (int i = 0; i < graph.size(); i++)
    {
        keyValues[i].first = INT_MAX;
        keyValues[i].second = -1;
        visited[i] = false;
    }
    keyValues[0].first = 0;
    for (int count = 0; count < graph.size() - 1; count++)
    {

        int j = minKey(keyValues, visited);

        visited[j] = true;

        for (int k = 0; k < graph.size(); k++)
        {

            if (graph[j][k] && graph[j][k] < keyValues[k].first)
            {
                keyValues[k].second = j;
                keyValues[k].first = graph[j][k];
            }
        }
    }

    printEgdesAndWieghts(keyValues, graph);
}

int main()
{
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0}, // 0
        {2, 0, 3, 8, 5}, // 1
        {0, 3, 0, 0, 7}, // 2
        {6, 8, 0, 0, 9}, // 3
        {0, 5, 7, 9, 0}  // 4
    };
    primsAlgo(graph);

    return 0;
}