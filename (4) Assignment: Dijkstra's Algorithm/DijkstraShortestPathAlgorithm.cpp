#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

#define INF INT_MAX

typedef pair<int, int> iPair;

class Graph {
    int vertices;
    list<iPair>* adjacencyList;

public:
    Graph(int vertices);
    void addEdge(int u, int v, int w);
    void findShortestPath(int source, int destination);
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjacencyList = new list<iPair>[vertices];
}

void Graph::addEdge(int u, int v, int w) {
    adjacencyList[u].push_back(make_pair(v, w));
    adjacencyList[v].push_back(make_pair(u, w));
}

void Graph::findShortestPath(int source, int destination) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> distances(vertices, INF);
    vector<int> predecessors(vertices, -1);

    pq.push(make_pair(0, source));
    distances[source] = 0;

    while (!pq.empty()) {
        int currentVertex = pq.top().second;
        pq.pop();

        for (auto i = adjacencyList[currentVertex].begin(); i != adjacencyList[currentVertex].end(); ++i) {
            int adjacentVertex = (*i).first;
            int weight = (*i).second;

            if (distances[adjacentVertex] > distances[currentVertex] + weight) {
                distances[adjacentVertex] = distances[currentVertex] + weight;
                predecessors[adjacentVertex] = currentVertex;
                pq.push(make_pair(distances[adjacentVertex], adjacentVertex));
            }
        }
    }

    cout << "Vertex\tDistance from Source:\n";
    for (int i = 0; i < vertices; ++i)
        cout << i << "\t" << distances[i] << endl;

    cout << "Shortest path from " << source << " to " << destination << ": ";
    vector<int> path;
    for (int v = destination; v != -1; v = predecessors[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    for (int p : path) {
        cout << p << " ";
    }
    cout << "\nTotal cost of the path: " << distances[destination] << endl;
}

int main() {
    int vertexCount = 5;
    Graph g(vertexCount);

    int A = 0, B = 1, C = 2, D = 3, E = 4;

    g.addEdge(A, B, 10);
    g.addEdge(A, E, 3);
    g.addEdge(B, C, 2);
    g.addEdge(B, E, 4);
    g.addEdge(E, B, 1);
    g.addEdge(E, C, 8);
    g.addEdge(E, D, 2);
    g.addEdge(D, C, 7);
    g.addEdge(C, D, 9);

    int startNode, endNode;
    cout << "Enter the source node (0 to " << vertexCount - 1 << "): ";
    cin >> startNode;
    cout << "Enter the destination node (0 to " << vertexCount - 1 << "): ";
    cin >> endNode;

    g.findShortestPath(startNode, endNode);

    return 0;
}
