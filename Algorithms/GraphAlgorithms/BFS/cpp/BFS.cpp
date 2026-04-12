#include <iostream>
#include <vector>
#include <queue>
#include <map>

/**
 * Breadth-First Search (BFS) Algorithm
 * 
 * Concept:
 * BFS starts at a chosen node and explores all of its neighbors at the current
 * depth before moving on to the nodes at the next depth level. It uses a queue
 * to keep track of the next nodes to visit.
 * 
 * Complexity:
 * - Time: O(V + E) where V is vertices and E is edges.
 * - Space: O(V) to store the visited nodes and the queue.
 */

class Graph {
    int vertices;
    std::map<int, std::vector<int>> adj;

public:
    Graph(int v) : vertices(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void bfs(int startNode) {
        std::map<int, bool> visited;
        std::queue<int> q;

        std::cout << "Starting BFS from node " << startNode << "...\n";
        visited[startNode] = true;
        q.push(startNode);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            std::cout << "\n[!] Visiting node: " << current << "\n";
            std::cout << "    Current Queue: ";
            printQueue(q);

            std::cout << "    Exploring neighbors of " << current << ":\n";
            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    std::cout << "        - Found unvisited neighbor: " << neighbor << ". Adding to queue.\n";
                    visited[neighbor] = true;
                    q.push(neighbor);
                } else {
                    std::cout << "        - Neighbor " << neighbor << " already visited. Skipping.\n";
                }
            }

            std::cout << "    (Press Enter to continue to next node...)";
            std::cin.get();
        }

        std::cout << "------------------------------------------\n";
        std::cout << "BFS traversal complete.\n";
    }

private:
    void printQueue(std::queue<int> q) {
        std::cout << "[ ";
        while (!q.empty()) {
            std::cout << q.front() << " ";
            q.pop();
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        BFS INTERACTIVE VISUALIZATION\n";
    std::cout << "==========================================\n";

    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    std::cout << "Graph structure (Undirected):\n";
    std::cout << "  0 -- 1 -- 3\n";
    std::cout << "  |    |\n";
    std::cout << "  2 -- 4\n";
    std::cout << "  |\n";
    std::cout << "  5\n\n";

    g.bfs(0);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
