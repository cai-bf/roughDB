#include <string>

class BTNode {
public:
    int keyNum, order;
    BTNode **children;
    KVNode *keys;
    bool isLeaf;

    BTNode(int order, bool isLeaf) {
        this->order = order;
        this->keyNum = 0;
        this->isLeaf = isLeaf;
        this->children = new BTNode *[order];
        this->keys = new KVNode[order - 1];
    }

    ~BTNode() {
        delete[] children;
        delete[] keys;
    }


};