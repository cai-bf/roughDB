template <typename T>
class BTNode {
public:
    int keyNum, order; // order should be a even numbers
    BTNode<T> **children;
    T *keys;
    bool isLeaf;

    BTNode(int order, bool isLeaf):order(order),keyNum(0),isLeaf(isLeaf) {
        this->children = new BTNode *[order]{};
        this->keys = new T[order - 1];
    }

    ~BTNode() {
        delete[] children;
        delete[] keys;
    }

    void insert(T key) {
        int i = keyNum - 1;
        if (isLeaf) {
            if (exist(key))
                throw "the key already exists in the tree\n";

            while (i >= 0 && key < keys[i]) {
                keys[i+1] = keys[i];
                --i;
            }
            keys[i+1] = key;
            ++keyNum;
        } else {
            while (i >= 0 && key < keys[i])
                --i;
            if (key == keys[i])
                throw "the key already exists in the tree\n";
            if (children[i + 1]->keyNum == order - 1) {
                split(i + 1, children[i + 1]); // previously split child into two children when child's keyNum catch up order-1
                if(key > keys[i + 1])
                    ++i;
            }
        }
        children[i + 1]->insert(key);
        return;
    }

    // split child into two children and set the new child in keys[pos]
    void split(int pos, BTNode *child) {
        BTNode *brother = new BTNode(child->order, child->isLeaf);

        brother->keyNum = order / 2 - 1;
        for (int i = 0; i < order / 2 - 1; ++i) {
            brother->keys[i] = child->keys[i + order / 2];
        }
        if (!child->isLeaf) {
            for (int i = 0; i < order / 2; ++i) {
                brother->children[i] = child->children[i + order / 2];
            }
        }
        child->keyNum = order / 2 - 1;

        for (int j = keyNum; j > pos; --j) {
            keys[j] = keys[j - 1];
        }
        keys[pos] = child->keys[child->keyNum];

        for (int k = keyNum + 1; k > pos + 1; --k) {
            children[k] = children[k - 1];
        }
        children[pos + 1] = brother;
        ++keyNum;
        return;
    }

    // find the first element >= key index
    int findIndex(T key) {
        int i = 0;
        for (; i < keyNum && keys[i] < key; ++i);
        return i;
    }

    void remove(T key) {
        int index = findIndex(key);
        if (index < keyNum && key == keys[index]) {
            if(isLeaf)
                removeFromLeaf(index);
            else
                removeFromNotLeaf(index);
        } else {
            if (isLeaf)
                throw "the key is not in the tree!\n";

            if (children[index]->keyNum < order / 2)
                supply(index);

            if(index > keyNum)
                children[index - 1]->remove(key);
            else
                children[index]->remove(key);
        }
        return;
    }

    void supply(int index) {
        if (index > 0 && children[index - 1]->keyNum >= order / 2)
            borrowFromLeft(index);
        else {
            if (index != keyNum && children[index + 1]->keyNum >= order / 2)
                borrowFromRight(index);
            else {
                if (index == keyNum)
                    merge(index - 1);
                else
                    merge(index);
            }
        }
        return;
    }

    void borrowFromLeft(int index) {
        BTNode<T> *borrow = children[index];
        BTNode<T> *lend = children[index - 1];

        for (int i = borrow->keyNum; i > 0; --i) {
            borrow->keys[i] = borrow->keys[i - 1];
        }
        if (!borrow->isLeaf) {
            for (int j = borrow->keyNum; j >= 0; --j) {
                borrow->children[j + 1] = borrow->children[j];
            }
            borrow->children[0] = lend->children[lend->keyNum];
        }

        borrow->keys[0] = keys[index - 1];
        keys[index - 1] = lend->keyNum[lend->keyNum - 1];

        lend->keyNum--;
        borrow->keyNum++;
        return;
    }

    void borrowFromRight(int index) {
        BTNode<T> *borrow = children[index];
        BTNode<T> *lend = children[index + 1];

        borrow->keys[borrow->keyNum] = keys[index];
        if(!borrow->isLeaf)
            borrow->children[borrow->keyNum + 1] = lend->children[0];

        keys[index] = lend->keys[0];

        for (int i = 0; i < lend->keyNum-1; ++i) {
            lend->keys[i] = lend->keys[i + 1];
            lend->children[i] = lend->children[i + 1];
        }
        lend->children[lend->keyNum - 1] = lend->children[lend->keyNum];

        borrow->keyNum++;
        lend->keyNum--;
        return;
    }

    void merge(int index) {
        BTNode<T> *child = children[index];
        BTNode<T> *forbid = children[index + 1];

        int prevKeyNum = child->keyNum + 1;

        child->keys[child->keyNum++] = keys[index];

        for (int i = 0; i < forbid->keyNum; ++i) {
            child->keys[child->keyNum++] = forbid->keys[i];
        }
        if (!child->isLeaf) {
            for (int j = 0; j <= forbid->keyNum; ++j) {
                child->children[prevKeyNum++] = forbid->children[j];
            }
        }

        for (int k = index; k < keyNum - 1; ++k) {
            keys[k] = keys[k + 1];
        }
        for (int l = index + 1; l < keyNum; ++l) {
            children[l] = children[l + 1];
        }
        --keyNum;

        delete forbid;
        return;
    }

    void removeFromLeaf(int index) {
        for (int i = index; i < keyNum - 1; ++i) {
            keys[i] = keys[i + 1];
        }
        --keyNum;
        return;
    }

    void removeFromNotLeaf(int index) {
        T key = keys[index];
        if (children[index]->keyNum >= order / 2) {
            T pre = getLast(index);
            keys[index] = pre;
            children[index]->remove(pre);
        } else if (children[index + 1]->keyNum >= order / 2) {
            T next = getNext(index);
            keys[index] = next;
            children[index + 1]->remove(next);
        } else {
            merge(index);
            children[index]->remove(key);
        }
        return;
    }

    T getLast(int index) {
        BTNode<T> *pre = children[index];
        while (!pre->isLeaf) {
            pre = pre->children[pre->keyNum];
        }
        return pre->keys[pre->keyNum - 1];
    }

    T getNext(int index) {
        BTNode<T> *next = children[index + 1];
        while (!next->isLeaf) {
            next = next->children[0];
        }
        return next->keys[0];
    }

    void update(T key) {
        int i = 0;
        while (i < keyNum && keys[i] < key)
            ++i;

        if (i < keyNum && keys[i] == key) {
            keys[i] = key;
            return;
        }

        if (isLeaf)
            throw "the key is not in the tree\n";

        children[i]->update(key);
        return;
    }

    void updateOrInsert(T key) {
        int i = keyNum - 1;
        if (isLeaf) {
            if (exist(key)) {
                update(key);
                return;
            }

            while (i >= 0 && key < keys[i]) {
                keys[i+1] = keys[i];
                --i;
            }
            keys[i+1] = key;
            ++keyNum;
        } else {
            while (i >= 0 && key < keys[i])
                --i;
            if (key == keys[i]) {
                update(key);
                return;
            }
            if (children[i + 1]->keyNum == order - 1) {
                split(i + 1, children[i + 1]);
                if(key > keys[i + 1])
                    ++i;
            }
        }
        children[i + 1]->updateOrInsert(key);
        return;
    }


    void traverse() {
        for (int i = 0; i < keyNum; ++i) {
            if (!isLeaf)
                children[i]->traverse();
            std::cout << keys[i] << " ";
        }
        if (!isLeaf)
            children[keyNum]->traverse();
    }

    bool exist(const T &key) {
        int i = 0;
        while (i < keyNum && keys[i] < key)
            ++i;
        if (i < keyNum && keys[i] == key)
            return true;
        if (isLeaf)
            return false;
        return children[i]->exist(key);
    }

    T find(T &key) {
        int i = 0;
        while (i < keyNum && keys[i] < key)
            ++i;
        if (i < keyNum && keys[i] == key)
            return keys[i];
        if (isLeaf)
            return NULL;
        return children[i]->find(key);
    }

    void select(json &data) {
        for (int i = 0; i < keyNum; ++i) {
            if (!isLeaf)
                children[i]->select(data);
            json item;
            item["key"] = keys[i].key;
            item["value"] = keys[i].value;
            data.push_back(item);
        }
        if (!isLeaf)
            children[keyNum]->select(data);
    }

    int count() {
        int sum = keyNum;
        if (isLeaf)
            return sum;
        for(int i = 0; i <= keyNum; ++i) {
            sum += children[i]->count();
        }
        return sum;
    }

    void dump(std::ostream &out) {
        for (int i = 0; i < keyNum; ++i) {
            if (!isLeaf)
                children[i]->dump(out);
            keys[i].dump(out);
        }
        if (!isLeaf)
            children[keyNum]->dump(out);
        return;
    }

};