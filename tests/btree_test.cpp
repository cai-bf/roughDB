//
// Created by cbf on 19-5-7.
//
#define CATCH_CONFIG_MAIN
#include "../dependencies/catch.hpp"

#include "../dependencies/json.hpp"
using json = nlohmann::json;

#include "../db/kvnode.hpp"
#include "../db/btree.hpp"

TEST_CASE("BTree test") {
    BTree<KVNode> tree(4);

    json data;
    data["foo"] = "bar";
    KVNode k("1", data);

    REQUIRE_NOTHROW(tree.insert(k)); // test insert

    data["foo"] = "not_bar";
    KVNode k_sec("1", data);

    REQUIRE_NOTHROW(tree.update(k_sec)); // test update

    REQUIRE(tree.exist(k_sec) == true); // test exist

    REQUIRE_NOTHROW(tree.updateOrInsert(KVNode("2", data))); // test updateOrInsert
    REQUIRE_NOTHROW(tree.updateOrInsert(KVNode("3", data)));
    REQUIRE_NOTHROW(tree.updateOrInsert(KVNode("4", data))); // test split
    REQUIRE_NOTHROW(tree.traverse());

    REQUIRE_NOTHROW(tree.remove(KVNode("1", data))); // test remove

    REQUIRE_NOTHROW(tree.updateOrInsert(KVNode("1", data)));
    REQUIRE_NOTHROW(tree.updateOrInsert(KVNode("0", data)));
    REQUIRE_NOTHROW(tree.remove(KVNode("4", data))); // test remove
    REQUIRE_NOTHROW(tree.traverse());

    REQUIRE(tree.count() == 4); // test count

    json all;
    tree.selectAll(all);
    std::cout << all << std::endl;
}

TEST_CASE("BTree throw test") {
    BTree<KVNode> tree(4);

    SECTION("empty tree remove") {
        json data = NULL;
        REQUIRE_THROWS_WITH(
                tree.remove(KVNode("foo", data)),
                "the tree is empty!\n"
        );
    }

    SECTION("remove not exist item from tree") {
        json data = NULL;
        tree.insert(KVNode("foo", data));
        REQUIRE_THROWS_WITH(
                tree.remove(KVNode("bar", data)),
                "the key is not in the tree!\n"
        );
    }

    SECTION("empty tree update") {
        json data = NULL;
        REQUIRE_THROWS_WITH(
                tree.update(KVNode("foo", data)),
                "the tree is empty!\n"
        );
    }

    SECTION("update the not existing item from tree") {
        json data = NULL;
        tree.insert(KVNode("foo", data));
        REQUIRE_THROWS_WITH(
                tree.update(KVNode("bar", data)),
                "the key is not in the tree\n"
        );
    }

    SECTION("exist item insert") {
        json data = NULL;
        tree.insert(KVNode("foo", data));
        REQUIRE_THROWS_WITH(
                tree.insert(KVNode("foo", data)),
                "the key already exists in the tree\n"
        );
    }
}