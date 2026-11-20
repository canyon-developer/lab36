// Stage 1 / Milestone 1: build the provided class and open the data file.
#include <fstream>
#include <iostream>
#include <string>
#include "IntBinaryTree1.h"
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
    string code;
    if (input >> code)
        cout << "First string record: " << code << '\n';
    else if (input.bad()) {
        cerr << "Error reading codes file.\n";
        return 1;
    } else
        cout << "The codes file is empty.\n";
    return 0;
}
