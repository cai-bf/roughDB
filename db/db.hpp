#include "../dependencies/json.hpp"
using json = nlohmann::json;

#include "./kvnode.hpp"
#include "./btree.hpp"

class DB {
private:
    std::string name;
    std::string database;
    std::map<std::string, BTree<KVNode>> tables;

public:
    DB(std::string database):database(database){}

    ~DB() {
        tables.clear();
    }

    bool checkTable(std::string name) {
        for (std::map<std::string, BTree<KVNode>>::const_iterator it = tables.cbegin();
                it != tables.cend(); it++) {
            if (it->first == name)
                return true;
        }
        return false;
    }

    void addTable(std::string name) {
        if (checkTable(name))
            throw "the table name has already exists!\n";

        BTree<KVNode> tree;
        tables[name] = tree;
        return;
    }

    void removeTable(std::string name) {
        if (!checkTable(name))
            throw "the table doesn't exist!\n";

        tables.erase(name);
        return;
    }

    void changeTable(std::string name) {
        if (!checkTable(name))
            throw "the table doesn't exist!\n";

        this->name = name;
        return;
    }

    void select(json &data) {
        if (!checkTable(name))
            throw "table not exists!\n";
        tables[name].selectAll(data);
    }

    void insert(std::string key, json value) {
        if (!checkTable(name))
            throw "table not exists!\n";
        KVNode node(key, value);
        tables[name].insert(node);
        return;
    }

    void update(std::string key, json value) {
        if (!checkTable(name))
            throw "table not exists!\n";
        KVNode node(key, value);
        tables[name].update(node);
        return;
    }

    void updateOrInsert(std::string key, json value) {
        if (!checkTable(name))
            throw "table not exists!\n";
        KVNode node(key, value);
        tables[name].updateOrInsert(node);
        return;
    }

    void remove(std::string key) {
        if (!checkTable(name))
            throw "table not exists!\n";
        KVNode node(key);
        tables[name].remove(node);
        return;
    }

    int count() {
        if (!checkTable(name))
            throw "table not exists!\n";
        return tables[name].count();
    }

    bool exist(std::string key) {
        if (!checkTable(name))
            throw "table not exists!\n";
        KVNode node(key);
        return tables[name].exist(node);
    }

    json get(std::string key) {
        if (!checkTable(name))
            throw "table not exists!\n";
        return tables[name].get(key);
    }

    void traverse() {
        std::cout << "\n\n";

        for (auto it = tables.begin();
                it != tables.end(); it++) {
            std::cout << "\n";
            for (int i = 0; i < 60; ++i) {
                std::cout << "#";
            }
            std::cout << "\ntable: " << it->first;
            std::cout << "\ndata: ";
            it->second.traverse();
        }
        std::cout << "\n";
    }

    void dump(std::string path) {
        std::fstream out;
        out.open(path, std::ios::out);
        dump(out);
        out.close();
        return;
    }

    void dump(std::ostream &out) {
        json database;
        database["name"] = this->database;
        json _tables = json::array();
        for (auto it = tables.begin();
                it != tables.end(); it++) {
            json table;

            table["name"] = it->first;
            table["data"] = json::array();
            it->second.selectAll(table["data"]);

            _tables.push_back(table);
        }
        database["tables"] = _tables;
        out << database;
    }

    void recover(std::string path) {
        std::fstream in;
        in.open(path, std::ios_base::in);
        recover(in);
        in.close();
        return;
    }

    void recover(std::istream &in) {
        json database;
        in >> database;
        this->database = database["name"];
        for (int i = 0; i < database["tables"].size(); ++i) {
            json table = database["tables"][i];
            addTable(table["name"]);

            // insert into table for each recover data
            for (int j = 0; j < table["data"].size(); ++j) {
                json item = table["data"][j];
                tables[table["name"]].insert(KVNode(item["key"], item["value"]));
            }
        }
        return;
    }

    void showTables() {
        for (auto it = tables.cbegin();
                it != tables.cend(); it++) {
            std::cout << it->first << "\n";
        }
    }
};