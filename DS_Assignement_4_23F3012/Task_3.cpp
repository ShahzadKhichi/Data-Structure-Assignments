#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <list>
using namespace std;
class Graph
{
private:
    map<char, list<char>> graph;
    void DFS(map<char, bool> &visited, char source)
    {
        cout << source << " -> ";
        for (auto i : graph[source])
        {
            if (!visited[i])
            {
                visited[i] = true;
                DFS(visited, i);
            }
        }
    }

public:
    void insertUser(char user)
    {
        graph[user];
    }
    void insertConnection(pair<char, char> connection)
    {
        graph[connection.first].push_back(connection.second);
        graph[connection.second].push_back(connection.first);
    }
    void bfs(char source)
    {
        map<char, bool> visited;

        queue<char> q;
        q.push(source);
        visited[source] = true;
        cout << "BFS : ";
        while (!q.empty())
        {
            char cur = q.front();
            q.pop();
            cout << cur << " -> ";

            for (auto i : graph[cur])
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }
    void dfs(char source)
    {
        cout << "DFS : ";
        map<char, bool> visited;
        visited[source] = true;
        DFS(visited, source);
        cout << endl;
    }
};
int main()
{
    Graph graph;
    string Users = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<pair<char, char>> Connections = {{'A', 'B'}, {'A', 'C'}, {'B', 'D'}, {'B', 'E'}, {'C', 'F'}};
    for (auto i : Users)
    {
        graph.insertUser(i);
    }
    for (auto i : Connections)
    {
        graph.insertConnection(i);
    }
    // graph.insertConnection({'B', 'C'});
    graph.bfs('A');
    graph.dfs('A');
    return 0;
}