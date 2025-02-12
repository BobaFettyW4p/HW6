#include "HW6-2.h"
#include <iostream>
#include <cassert>

void testBasicOperations() {
    std::cout << "Testing basic operations...\n";
    
    btree<int> tree;
    
    // Test insertion
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    // Test search
    auto result1 = tree.search(5);
    assert(result1 && result1->key_value == 5 && "Failed to find root node (5)");
    std::cout << "Found 5\n";

    auto result2 = tree.search(3);
    assert(result2 && result2->key_value == 3 && "Failed to find node (3)");
    std::cout << "Found 3\n";

    auto result3 = tree.search(9);
    assert(result3 && result3->key_value == 9 && "Failed to find node (9)");
    std::cout << "Found 9\n";

    // Test searching for non-existent value
    auto result4 = tree.search(42);
    assert(result4 == nullptr && "Found non-existent node (42)");
    std::cout << "Correctly didn't find 42\n";
}

void testTemplateSupport() {
    std::cout << "\nTesting template support...\n";
    
    btree<std::string> stringTree;
    
    stringTree.insert("hello");
    stringTree.insert("world");
    stringTree.insert("test");

    auto result1 = stringTree.search("hello");
    assert(result1 && result1->key_value == "hello" && "Failed to find string node (hello)");
    std::cout << "Found 'hello'\n";

    auto result2 = stringTree.search("missing");
    assert(result2 == nullptr && "Found non-existent string node");
    std::cout << "Correctly didn't find 'missing'\n";
}

int main() {
    try {
        testBasicOperations();
        testTemplateSupport();
        std::cout << "\nAll tests passed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
} 