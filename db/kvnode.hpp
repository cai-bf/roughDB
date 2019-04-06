class KVNode {
public:
    std::string key;
    json value;

    KVNode(std::string key, json value = NULL) {
        this->key = key;
        this->value = value;
    }

    ~KVNode() {}


};