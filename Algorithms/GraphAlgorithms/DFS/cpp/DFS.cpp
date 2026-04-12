#include <iostream>
#include <vector>
#include <stack>
#include <map>

/**
 * Depth-First Search (DFS) Algorithm
 * 
 * Concept:
 * DFS starts at a chosen node and explores as far as possible along each branch
 * before backtracking. It uses a stack (either explicitly or via recursion)
 * to keep track of the path taken.
 * 
 * Complexity:
 * - Time: O(V + E) where V is vertices and E is edges.
 * - Space: O(V) to store the visited nodes and the recursion stack.
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

    void dfs(int startNode) {
        std::map<int, bool> visited;
        std::cout << "Starting DFS from node " << startNode << "...\n";
        dfsRecursive(startNode, visited, 0);
        std::cout << "------------------------------------------\n";
        std::cout << "DFS traversal complete.\n";
    }

private:
    void dfsRecursive(int current, std::map<int, bool>& visited, int depth) {
        visited[current] = true;
        
        std::string indent(depth * 4, ' ');
        std::cout << "\n" << indent << "[!] Visiting node: " << current << "\n";
        
        std::cout << indent << "    Exploring neighbors of " << current << ":\n";
        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                std::cout << indent << "        - Found unvisited neighbor: " << neighbor << ". Recursing...\n";
                std::cout << indent << "        (Press Enter to go deeper into " << neighbor << "...)";
                std::cin.get();
                dfsRecursive(neighbor, visited, depth + 1);
            } else {
                std::cout << indent << "        - Neighbor " << neighbor << " already visited. Skipping.\n";
            }
        }
        
        std::cout << indent << "    [Backtracking from " << current << "]\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        DFS INTERACTIVE VISUALIZATION\n";
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

    g.dfs(0);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
