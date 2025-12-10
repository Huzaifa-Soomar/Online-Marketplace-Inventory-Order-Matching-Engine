#ifndef CATEGORY_TREE_2025_H
#define CATEGORY_TREE_2025_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class CategoryNode {
public:
    string name;
    vector<CategoryNode*> children;

    CategoryNode(string n = "");
};

class CategoryTree {
private:
    CategoryNode* root;

public:
    CategoryTree();
    CategoryNode* getRoot() const;
    void addCategory(const string& parent, const string& child);
    bool searchCategory(const string& name) const;
};

#endif
