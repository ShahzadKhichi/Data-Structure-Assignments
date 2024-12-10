#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int tsp(vector<vector<int>> &cost, vector<vector<char>> &name)
{

    int numNodes = cost.size();
    vector<int> nodes;

    for (int i = 1; i < numNodes; i++)
        nodes.push_back(i);

    int minCost = 200000;

    do
    {
        int currCost = 0;
        int currNode = 0;
        cout << name[currNode][0] << "-> ";
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << name[currNode][nodes[i]] << " -> ";
            currCost += cost[currNode][nodes[i]];
            currNode = nodes[i];
        }
        currCost += cost[currNode][0];
        cout << name[currNode][0] << " ";
        cout << " : " << currCost << endl;
        cout << endl;
        minCost = min(minCost, currCost);

    } while (next_permutation(nodes.begin(), nodes.end()));

    return minCost;
}
int main()
{

    vector<vector<int>> cost = {
        // p   q   r   s
        {0, 10, 15, 20}, // p
        {10, 0, 35, 25}, // q
        {15, 35, 0, 30}, // r
        {20, 25, 30, 0}  // s
    };
    vector<vector<char>> name = {
        {'p', 'q', 'r', 's'},
        {'p', 'q', 'r', 's'},
        {'p', 'q', 'r', 's'},
        {'p', 'q', 'r', 's'},
    };

    cout << "minimum cost : " << tsp(cost, name) << endl;
    return 0;
}