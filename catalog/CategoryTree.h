#ifndef CATEGORY_TREE_2025_H
#define CATEGORY_TREE_2025_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class CategoryNode {
public:
    string name;
    vector<CategoryNode*> children; // Allows sub-categories as each "CategoryNode" has its own vector-array.

    CategoryNode(string n = "");
};

class CategoryTree {
private:
    CategoryNode* root;

    CategoryNode* findNode(CategoryNode* current, const string& target) const;
    void destroy(CategoryNode* current);

public:
    CategoryTree();
    ~CategoryTree();

    CategoryNode* getRoot() const;
    void addCategory(const string& parent, const string& child);
    bool searchCategory(const string& name) const;
};

#endif