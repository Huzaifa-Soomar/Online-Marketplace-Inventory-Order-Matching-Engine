#include "CategoryTree.h"

CategoryNode::CategoryNode(string n) : name(n) {}

CategoryTree::CategoryTree() {
    root = new CategoryNode("ROOT"); // Starts with a top-level ROOT so all categories can come under it.
}

CategoryTree::~CategoryTree() {
    destroy(root); // Destroys all children, then root.
    root = nullptr;
}

CategoryNode* CategoryTree::getRoot() const {
    return root;
}

void CategoryTree::addCategory(const string& parent, const string& child) {
    if (child == "") return;

    CategoryNode* parentNode = nullptr;

    if (parent == "" || parent == "ROOT")
        parentNode = root;
    else
        parentNode = findNode(root, parent);

    if (parentNode == nullptr) return;

    for (size_t i = 0; i < parentNode->children.size(); i++) {
        if (parentNode->children[i]->name == child) return;
    }

    parentNode->children.push_back(new CategoryNode(child));
}

bool CategoryTree::searchCategory(const string& name) const {
    return findNode(root, name) != nullptr; // Converts into true/false for bool return.
}

CategoryNode* CategoryTree::findNode(CategoryNode* current, const string& target) const {
    if (current == nullptr) return nullptr;
    if (current->name == target) return current; // Checks for match

    for (size_t i = 0; i < current->children.size(); i++) {
        CategoryNode* found = findNode(current->children[i], target); // Traverses to each child.
        if (found != nullptr) return found; // = current when matched.
    }
    return nullptr;
}

void CategoryTree::destroy(CategoryNode* current) {
    if (current == nullptr) return;

    for (size_t i = 0; i < current->children.size(); i++) {
        destroy(current->children[i]); // Traverses till the leaf/last child and then backtracks.
    }
    delete current;
}