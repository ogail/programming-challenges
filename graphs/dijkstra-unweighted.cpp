#include <queue>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <assert.h>
#include <algorithm>
#include <functional>

using namespace std;

typedef vector<vector<int>> graph;

vector<int> dijkstra_unweighted(graph g, int start, int end)
{
    unordered_map<int, int> paths;
    vector<int> path;
    unordered_set<int> visited;
    queue<int> nodes;

    nodes.push(start);

    while (!nodes.empty())
    {
        if (nodes.front() == end)
        {
            break;
        }

        int current = nodes.front();
        nodes.pop();
        visited.insert(current);
        for (int node : g[current])
        {
            if (visited.count(node) == 0)
            {
                paths[node] = current;
                nodes.push(node);
            }
        }
    }

    if (nodes.front() == end)
    {
        int current = nodes.front();

        while (current != start)
        {
            path.push_back(current);
            current = paths[current];
        }
        path.push_back(start);
    }

    return path;
}

void run_tests()
{
    graph adjList =
    {
        { 1, 2 },
        { 0, 3 },
        { 0, 3, 4 },
        { 1, 2 },
        { 2 },
    };
    vector<int> expected = { 3, 2, 0 };
    vector<int> actual = dijkstra_unweighted(adjList, 0, 3);
    
    assert(expected.size() == actual.size());

    for (int i = 0; i < expected.size(); ++i)
    {
        assert(expected[i] == actual[i]);
    }

    printf("test case PASSED!\n");
}

int main()
{
    run_tests();
    return 0;
}