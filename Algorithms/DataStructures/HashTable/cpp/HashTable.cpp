#include <iostream>
#include <vector>
#include <list>
#include <string>

/**
 * HashTable Data Structure
 * 
 * Concept:
 * A Hash Table is a data structure that maps keys to values using a hash function.
 * It uses the hash to compute an index into an array of buckets, from which
 * the desired value can be found. This implementation uses separate chaining (using lists)
 * to handle collisions.
 * 
 * Complexity:
 * - Access: N/A
 * - Search: O(1) average, O(n) worst case (all keys hash to same bucket).
 * - Insertion: O(1) average.
 * - Deletion: O(1) average.
 */

class InteractiveHashTable {
public:
    InteractiveHashTable(int size) : tableSize(size) {
        table.resize(size);
    }

    /**
     * @brief Inserts a key into the hash table.
     * 
     * @param key The key to insert.
     */
    void insert(const std::string& key) {
        int index = hashFunction(key);
        std::cout << "\n>>> Inserting '" << key << "' into the hash table.\n";
        std::cout << "    [H] Hash of '" << key << "' maps to index: " << index << "\n";
        
        table[index].push_back(key);

        printTable();
        std::cout << "    [✓] '" << key << "' added to the chain at index " << index << ".\n";
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

    /**
     * @brief Searches for a key in the hash table.
     * 
     * @param key The key to search for.
     */
    void search(const std::string& key) {
        int index = hashFunction(key);
        std::cout << "\n>>> Searching for '" << key << "'...\n";
        std::cout << "    [H] Hash of '" << key << "' is " << index << ". Checking bucket " << index << ".\n";

        bool found = false;
        for (const auto& item : table[index]) {
            if (item == key) {
                found = true;
                break;
            }
        }

        if (found) {
            std::cout << "    [✓] Found '" << key << "' at index " << index << "!\n";
        } else {
            std::cout << "    [!] '" << key << "' not found in index " << index << ".\n";
        }
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

private:
    int tableSize;
    std::vector<std::list<std::string>> table;

    /**
     * @brief A simple hash function that sums character values.
     */
    int hashFunction(const std::string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % tableSize;
    }

    /**
     * @brief Prints the current state of the hash table.
     */
    void printTable() {
        std::cout << "    Table State:\n";
        for (int i = 0; i < tableSize; i++) {
            std::cout << "    [" << i << "]: ";
            for (const auto& item : table[i]) {
                std::cout << item << " -> ";
            }
            std::cout << "nullptr\n";
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        HASH TABLE INTERACTIVE\n";
    std::cout << "==========================================\n";

    InteractiveHashTable ht(5);

    ht.insert("Apple");
    ht.insert("Banana");
    ht.insert("Cherry");
    ht.insert("Date");
    ht.insert("Elderberry");

    ht.search("Cherry");
    ht.search("Fig");

    std::cout << "\nStructure visualization completed. Thank you for learning!\n";
    return 0;
}
