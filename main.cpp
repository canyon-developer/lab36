// Stage 6: add a menu with display, add, and search options.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "IntBinaryTree6.h"
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

// Read a whole line so invalid menu input does not leave cin in a failed state.
bool readInteger(const string& prompt, int minimum, int maximum, int& value) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line))
            return false;
        istringstream input(line);
        char extra;
        if ((input >> value) && !(input >> extra)
            && value >= minimum && value <= maximum)
            return true;
        cout << "Enter a whole number from " << minimum << " to " << maximum << ".\n";
    }
}

// A record is one nonempty code. Keep its spelling and leading zeros.
bool readCode(const string& prompt, string& code) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line))
            return false;
        istringstream input(line);
        string extra;
        if ((input >> code) && !(input >> extra))
            return true;
        cout << "Enter one nonempty code without spaces.\n";
    }
}

// Return false only when the user closes the input stream.
bool addRecord(IntBinaryTree& tree) {
    string code;
    if (!readCode("Code to add: ", code))
        return false;
    if (tree.insertNode(code))
        cout << "Added: " << code << '\n';
    else
        cout << "Code already exists: " << code << '\n';
    return true;
}

bool searchRecord(const IntBinaryTree& tree) {
    string code;
    if (!readCode("Code to search: ", code))
        return false;
    if (tree.searchNode(code))
        cout << "Found: " << code << '\n';
    else
        cout << "Not found: " << code << '\n';
    return true;
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
    while (true) {
        cout << "\nString Code BST Menu:\n"
             << "[1] Display records\n"
             << "[2] Add a record\n"
             << "[3] Search for a record\n"
             << "[0] Exit\n";
        int choice;
        if (!readInteger("Enter your choice: ", 0, 3, choice) || choice == 0)
            break;
        bool keepRunning = true;
        switch (choice) {
            case 1: displayRecords(tree); break;
            case 2: keepRunning = addRecord(tree); break;
            case 3: keepRunning = searchRecord(tree); break;
        }
        if (!keepRunning)
            break;
    }
    cout << "Goodbye!\n";
    return 0;
}
