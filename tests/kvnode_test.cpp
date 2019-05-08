//
// Created by cbf on 19-5-7.
//

#define CATCH_CONFIG_MAIN
#include "../dependencies/catch.hpp"

#include "../dependencies/json.hpp"
using json = nlohmann::json;

#include "../db/kvnode.hpp"


TEST_CASE("KvNode Test") {
    json data;
    data["foo"] = "bar";
    KVNode node1("first", data);
    KVNode node2("second", data);
    data["foo"] = "test";
    KVNode node3("third", data);
    KVNode node4("first", data);

    REQUIRE(node1 == node4);
    REQUIRE(node1 < node2);
    REQUIRE(node3 >= node1);
}