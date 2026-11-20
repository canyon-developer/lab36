// Stage 2: read all records as strings before converting the tree.
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "IntBinaryTree2.h"
using namespace std;

// Exercise the supplied integer class before changing the stored type.
bool testIntegerTree() {
    IntBinaryTree tree;
    tree.insertNode(5);
    tree.insertNode(3);
    tree.insertNode(8);
    if (!tree.searchNode(3) || tree.searchNode(99)) {
        cerr << "Integer search check failed.\n";
        return false;
    }
    tree.remove(3);
    tree.remove(99);
    if (tree.searchNode(3)) {
        cerr << "Integer deletion check failed.\n";
        return false;
    }
    cout << "Integer BST checks passed. Remaining values:\n";
    tree.displayInOrder();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [codes-file]\n";
        return 1;
    }
    string filename = argc == 2 ? argv[1] : "codes.txt";
    if (!testIntegerTree())
        return 1;

    ifstream input(filename);
    if (!input) {
        cerr << "Cannot open codes file: " << filename << '\n';
        return 1;
    }
    vector<string> codes;
    string code;
    while (input >> code)
        codes.push_back(code);
    if (input.bad()) {
        cerr << "Error reading codes file.\n";
        return 1;
    }
    cout << "Read " << codes.size() << " string records. First five:\n";
    for (size_t index = 0; index < codes.size() && index < 5; ++index)
        cout << codes[index] << '\n';
    return 0;
}
