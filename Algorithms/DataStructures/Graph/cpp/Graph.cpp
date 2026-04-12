#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

/**
 * Graph Data Structure (Adjacency List)
 * 
 * Concept:
 * A Graph is a collection of nodes (vertices) and edges that connect them.
 * An Adjacency List represents a graph by storing a list of neighbors for each node.
 * 
 * Complexity:
 * - Search (BFS/DFS): O(V + E) where V is vertices and E is edges.
 * - Adjacency Check: O(V) worst case for adjacency list.
 * - Insertion: O(1) for nodes or edges.
 */

class InteractiveGraph {
public:
    InteractiveGraph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    /**
     * @brief Adds an undirected edge between two vertices.
     */
    void addEdge(int u, int v) {
        std::cout << "\n>>> Adding edge between " << u << " and " << v << ".\n";
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since it's undirected

        printAdjList();
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

    /**
     * @brief Performs a Breadth-First Search (BFS) starting from a vertex.
     */
    void bfs(int startNode) {
        std::cout << "\n>>> Starting Breadth-First Search (BFS) from node " << startNode << ".\n";
        std::vector<bool> visited(numVertices, false);
        std::queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            std::cout << "    [*] Visited node " << current << ". Checking its neighbors...\n";

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    std::cout << "    [+] Neighbor " << neighbor << " added to the queue.\n";
                } else {
                    std::cout << "    [ ] Neighbor " << neighbor << " already visited. Skipping.\n";
                }
            }
            
            std::cout << "    (Press Enter to continue traversal...)";
            std::cin.get();
        }
        std::cout << "    [✓] BFS traversal complete.\n";
    }

private:
    int numVertices;
    std::vector<std::list<int>> adjList;

    /**
     * @brief Prints the current state of the adjacency list.
     */
    void printAdjList() {
        std::cout << "    Adjacency List:\n";
        for (int i = 0; i < numVertices; i++) {
            std::cout << "    " << i << ": ";
            for (int neighbor : adjList[i]) {
                std::cout << neighbor << " -> ";
            }
            std::cout << "nullptr\n";
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          GRAPH INTERACTIVE\n";
    std::cout << "==========================================\n";

    InteractiveGraph graph(5);

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    graph.bfs(0);

    std::cout << "\nStructure visualization completed. Thank you for learning!\n";
    return 0;
}
