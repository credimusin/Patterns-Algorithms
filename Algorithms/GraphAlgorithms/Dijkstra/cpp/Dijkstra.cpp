#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>

/**
 * Dijkstra's Shortest Path Algorithm
 * 
 * Concept:
 * Dijkstra's algorithm finds the shortest path between a starting node and all
 * other nodes in a weighted graph with non-negative edge weights. It uses a
 * priority queue to always explore the node with the smallest known distance.
 * 
 * Complexity:
 * - Time: O((V + E) log V) with a priority queue.
 * - Space: O(V + E) to store the graph and distances.
 */

const int INF = std::numeric_limits<int>::max();

struct Edge {
    int target;
    int weight;
};

class Graph {
    int vertices;
    std::map<int, std::vector<Edge>> adj;

public:
    Graph(int v) : vertices(v) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Undirected graph
    }

    void dijkstra(int startNode) {
        std::map<int, int> dist;
        for (int i = 0; i < vertices; ++i) dist[i] = INF;

        // priority_queue with (distance, node) pairs
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        dist[startNode] = 0;
        pq.push({0, startNode});

        std::cout << "Starting Dijkstra from node " << startNode << "...\n";

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            std::cout << "\n[!] Processing node: " << u << " (Current shortest distance: " << d << ")\n";
            printDistances(dist);

            std::cout << "    Checking neighbors of " << u << ":\n";
            for (auto& edge : adj[u]) {
                int v = edge.target;
                int weight = edge.weight;

                if (dist[u] + weight < dist[v]) {
                    std::cout << "        - Path to " << v << " via " << u << " is shorter (" 
                              << dist[u] << " + " << weight << " = " << dist[u] + weight 
                              << " < " << (dist[v] == INF ? "INF" : std::to_string(dist[v])) << ")\n";
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                } else {
                    std::cout << "        - Path to " << v << " via " << u << " is not shorter. Skipping.\n";
                }
            }

            std::cout << "    (Press Enter to continue to next node...)";
            std::cin.get();
        }

        std::cout << "------------------------------------------\n";
        std::cout << "Final Shortest Distances from node " << startNode << ":\n";
        printDistances(dist);
    }

private:
    void printDistances(const std::map<int, int>& dist) {
        std::cout << "    Distances: [ ";
        for (auto const& [node, d] : dist) {
            std::cout << node << ":" << (d == INF ? "INF" : std::to_string(d)) << " ";
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        DIJKSTRA INTERACTIVE VISUALIZATION\n";
    std::cout << "==========================================\n";

    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);

    std::cout << "Graph structure (Weighted, Undirected):\n";
    std::cout << "  0 --(4)-- 1 --(5)-- 3 --(6)-- 5\n";
    std::cout << "  |       / |       / |       /\n";
    std::cout << " (2)   (1) (8)   (2) (10)  (3)\n";
    std::cout << "  |   /     |   /     |   /\n";
    std::cout << "  2 -------- 4 --------\n\n";

    g.dijkstra(0);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
