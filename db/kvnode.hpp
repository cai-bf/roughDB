class KVNode {
public:
    std::string key;
    json value;

    KVNode() {}

    KVNode(std::string key, json value = NULL) {
        this->key = key;
        this->value = value;
    }

    ~KVNode() {}

    KVNode& operator =(const KVNode& node) {
        key = node.key;
        value = node.value;
        return *this;
    }

    friend bool operator<(const KVNode &first, const KVNode &second) {
        return first.key < second.key;
    }

    friend bool operator>(const KVNode &first, const KVNode &second) {
        return second.key < first.key;
    }

    friend bool operator==(const KVNode &first, const KVNode &second) {
        return first.key == second.key;
    }

    friend bool operator!=(const KVNode &first, const KVNode &second) {
        return first.key != second.key;
    }

    friend bool operator<=(const KVNode &first, const KVNode &second) {
        return !(second < first);
    }

    friend bool operator>=(const KVNode &first, const KVNode &second) {
        return !(first < second);
    }

    friend std::ostream& operator<<(std::ostream &out, const KVNode& node) {
        out << "\nkey: " << node.key;
        out << "\tvalue: " << node.value;
        return out;
    }

    void dump(std::ostream &out) {
        json data;
        data["key"] = key;
        data["value"] = value;

        out << data << ",";
        return;
    }
};