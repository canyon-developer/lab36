// Stage 8: add modifyNode to replace keys while preserving BST order.
// IntBinaryTree adapted from integers to string code records.
#ifndef INTBINARYTREE8_H
#define INTBINARYTREE8_H

#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

// Keep the supplied class name, but store and compare strings throughout.
class IntBinaryTree {
private:
    struct TreeNode {
        string value;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode *root;
    size_t nodeCount;

    void insert(TreeNode *&, TreeNode *&);
    void destroySubTree(TreeNode *);
    bool deleteNode(const string&, TreeNode *&);
    void makeDeletion(TreeNode *&);
    void displayInOrder(TreeNode *) const;
    void displayPreOrder(TreeNode *) const;
    void displayPostOrder(TreeNode *) const;

public:
    IntBinaryTree() { root = nullptr; nodeCount = 0; }
    ~IntBinaryTree() { destroySubTree(root); }

    // The tree owns its nodes, so do not allow shallow pointer copies.
    IntBinaryTree(const IntBinaryTree&) = delete;
    IntBinaryTree& operator=(const IntBinaryTree&) = delete;

    bool insertNode(const string&);
    bool searchNode(const string&) const;
    bool remove(const string&);
    bool modifyNode(const string&, const string&);
    size_t size() const { return nodeCount; }

    void displayInOrder() const { displayInOrder(root); }
    void displayPreOrder() const { displayPreOrder(root); }
    void displayPostOrder() const { displayPostOrder(root); }
};

inline void IntBinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
    if (!nodePtr)
        nodePtr = newNode;
    else if (newNode->value < nodePtr->value)
        insert(nodePtr->left, newNode);
    else
        insert(nodePtr->right, newNode);
}

// Codes are unique keys. Reject duplicates and empty strings.
inline bool IntBinaryTree::insertNode(const string& code) {
    if (code.empty() || searchNode(code))
        return false;

    TreeNode *newNode = new TreeNode;
    newNode->value = code;
    newNode->left = newNode->right = nullptr;
    insert(root, newNode);
    ++nodeCount;
    return true;
}

inline void IntBinaryTree::destroySubTree(TreeNode *nodePtr) {
    if (nodePtr) {
        destroySubTree(nodePtr->left);
        destroySubTree(nodePtr->right);
        delete nodePtr;
    }
}

inline bool IntBinaryTree::searchNode(const string& code) const {
    TreeNode *nodePtr = root;
    while (nodePtr) {
        if (nodePtr->value == code)
            return true;
        else if (code < nodePtr->value)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    return false;
}

inline bool IntBinaryTree::remove(const string& code) {
    if (!deleteNode(code, root))
        return false;
    --nodeCount;
    return true;
}

inline bool IntBinaryTree::deleteNode(const string& code, TreeNode *&nodePtr) {
    if (!nodePtr)
        return false;
    if (code < nodePtr->value)
        return deleteNode(code, nodePtr->left);
    if (code > nodePtr->value)
        return deleteNode(code, nodePtr->right);

    makeDeletion(nodePtr);
    return true;
}

inline void IntBinaryTree::makeDeletion(TreeNode *&nodePtr) {
    TreeNode *tempNodePtr;
    if (!nodePtr)
        return;
    if (!nodePtr->right) {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->left;
        delete tempNodePtr;
    } else if (!nodePtr->left) {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    } else {
        // Attach the left subtree below the smallest node on the right.
        tempNodePtr = nodePtr->right;
        while (tempNodePtr->left)
            tempNodePtr = tempNodePtr->left;
        tempNodePtr->left = nodePtr->left;
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    }
}

inline bool IntBinaryTree::modifyNode(const string& oldCode,
                                      const string& newCode) {
    if (!searchNode(oldCode) || newCode.empty())
        return false;
    if (oldCode == newCode)
        return true;
    // Insert first so a duplicate or failed allocation leaves the old code.
    // Removing and reinserting a key preserves the BST ordering.
    if (!insertNode(newCode))
        return false;
    remove(oldCode);
    return true;
}

inline void IntBinaryTree::displayInOrder(TreeNode *nodePtr) const {
    if (nodePtr) {
        displayInOrder(nodePtr->left);
        cout << nodePtr->value << '\n';
        displayInOrder(nodePtr->right);
    }
}

inline void IntBinaryTree::displayPreOrder(TreeNode *nodePtr) const {
    if (nodePtr) {
        cout << nodePtr->value << '\n';
        displayPreOrder(nodePtr->left);
        displayPreOrder(nodePtr->right);
    }
}

inline void IntBinaryTree::displayPostOrder(TreeNode *nodePtr) const {
    if (nodePtr) {
        displayPostOrder(nodePtr->left);
        displayPostOrder(nodePtr->right);
        cout << nodePtr->value << '\n';
    }
}

#endif
