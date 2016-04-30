#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct edge
{
    int index, weight;
};

vector< vector < edge > > edges;
vector< int > parent, distances;
vector< bool > visited;

void dijkstra(int start)
{
    parent.clear();
    visited.clear();
    distances.clear();

    for (int i = 0; i < edges.size(); i++)
    {
        parent.push_back(-1);
        visited.push_back(false);
        distances.push_back(numeric_limits< int >::max());
    }

    distances[start] = 0;
    while (visited[start] == false)
    {
        visited[start] = true;
        for (int i = 0; i < edges[start].size(); i++)
        {
            edge current = edges[start][i];
            if (visited[current.index] == false &&
                distances[start] + current.weight < distances[current.index])
            {
                distances[current.index] = distances[start] + current.weight;
                parent[current.index] = start;
            }
        }

        int minDistance = numeric_limits< int >::max();
        for (int i = 0; i < edges.size(); i++)
            if (visited[i] == false && minDistance > distances[i])
            {
                minDistance = distances[i];
                start = i;
            }
    }
}

int main(int argc, char *argv[])
{
    dijkstra(0);
    
    return 0;
}