// Stage 3 / Milestone 2: use and test the converted string BST.
#include <iostream>
#include <string>
#include "IntBinaryTree3.h"
using namespace std;

// Test alphanumeric keys, leading zeros, duplicates, searches, and deletion.
bool testStringTree() {
    IntBinaryTree tree;
    string codes[] = {"M4", "B2", "T9", "0012", "10", "2"};
    for (const string& code : codes) {
        if (!tree.insertNode(code) || !tree.searchNode(code)) {
            cerr << "String insertion/search check failed.\n";
            return false;
        }
    }
    if (tree.insertNode("M4") || tree.insertNode("")
        || tree.searchNode("12") || tree.searchNode("missing")
        || tree.remove("missing") || tree.size() != 6) {
        cerr << "String key validation check failed.\n";
        return false;
    }
    if (!tree.remove("T9") || tree.searchNode("T9") || tree.size() != 5
        || !tree.insertNode("T9")) {
        cerr << "String deletion check failed.\n";
        return false;
    }
    cout << "String BST checks passed.\n";
    return true;
}

int main() {
    if (!testStringTree())
        return 1;

    IntBinaryTree tree;
    tree.insertNode("M4");
    tree.insertNode("B2");
    tree.insertNode("0012");
    tree.insertNode("10");
    tree.insertNode("2");
    cout << "Sample strings in order (10 comes before 2):\n";
    tree.displayInOrder();
    return 0;
}
