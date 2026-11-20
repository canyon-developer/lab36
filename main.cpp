// Stage 5 / Milestone 3: display the populated BST using inorder traversal.
#include <fstream>
#include <iostream>
#include <string>
#include "IntBinaryTree5.h"
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

// Read whitespace-separated codes in their original file order.
bool loadCodes(const string& filename, IntBinaryTree& tree) {
    ifstream input(filename);
    if (!input) {
        cerr << "Cannot open codes file: " << filename << '\n';
        return false;
    }
    size_t records = 0;
    size_t duplicates = 0;
    string code;
    while (input >> code) {
        ++records;
        if (!tree.insertNode(code))
            ++duplicates;
    }
    if (input.bad()) {
        cerr << "Error reading codes file: " << filename << '\n';
        return false;
    }
    cout << "Loaded " << tree.size() << " unique codes from " << filename
         << " (" << records << " records read, " << duplicates
         << " duplicates skipped).\n";
    return true;
}

void displayRecords(const IntBinaryTree& tree) {
    cout << "Records in sorted order (" << tree.size() << "):\n";
    if (tree.size() == 0)
        cout << "The tree is empty.\n";
    else
        tree.displayInOrder();
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [codes-file]\n";
        return 1;
    }
    string filename = argc == 2 ? argv[1] : "codes.txt";
    if (!testStringTree())
        return 1;
    IntBinaryTree tree;
    if (!loadCodes(filename, tree))
        return 1;
    displayRecords(tree);
    return 0;
}
