#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "btnode.hpp"
const int DEFAULT_ORDER = 6000;

template <typename T>
class BTree {
private:
    BTNode<T> *root;
    int order;

public:
    BTree(int order = DEFAULT_ORDER) {
        this->order = order;
        root = NULL;
    }

    ~BTree() {
        delete root;
    }

    void insert(T key) {
        if (!root)
            root = new BTNode<T>(order, true);

        if (root->keyNum == order - 1) {
            BTNode<T> *father = new BTNode<T>(order, false);
            father->children[0] = root;
            father->split(0, root);
            root = father;
        }

        root->insert(key);
        return;
    }

    void update(T key) {
        if (!root)
            throw "the tree is empty!\n";
        root->update(key);
        return;
    }

    void updateOrInsert(T key) {
        if(!root)
            insert(key);
        else if (exist(key)) {
            update(key);
        } else {
            insert(key);
        }
        return;
    }

    void remove(T key) {
        if(!root)
            throw "the tree is empty!\n";
        root->remove(key);

        if (root->keyNum == 0) {
            if (root->isLeaf)
                root = NULL;
            else
                root = root->children[0];
        }
        return;
    }

    void selectAll(json &data) {
        if(root != NULL)
            root->select(data);
        return;
    }

    void traverse() {
        if(root != NULL)
            root->traverse();
        std::cout << "\n";
    }

    bool exist(T key) {
        if (!root)
            return false;
        return root->exist(key);
    }

    int count() {
        if (!root)
            return 0;
        return root->count();
    }

    json get(std::string key) {
        return root->get(key);
    }

    void dump(std::ostream &out) {
        out << "[";
        if (root != NULL)
            root->dump(out);
        out.seekp(-1, std::ios_base::end);
        out << "]";
        return;
    }

    void restore(std::istream &in) {
        json data;
        in >> data;
        for (int i = 0; i < data.size(); ++i) {
            T item(data[i]["key"], data[i]["value"]);
            insert(item);
        }
        return;
    }
};