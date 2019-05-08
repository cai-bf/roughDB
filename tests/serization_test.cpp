//
// Created by cbf on 19-5-8.
//
#define CATCH_CONFIG_MAIN
#include "../dependencies/catch.hpp"

#include "../db/db.hpp"

TEST_CASE("serialization and deserialization test") {
    DB db("database");
    json data;
    SECTION("serialize test") {
        REQUIRE_NOTHROW(db.addTable("table"));
        REQUIRE_NOTHROW(db.addTable("table2"));
        REQUIRE_NOTHROW(db.changeTable("table"));
        data["foo"] = "bar";
        REQUIRE_NOTHROW(db.insert("key_1", data));
        REQUIRE_NOTHROW(db.insert("key_2", data));

        data["table"] = 2;
        REQUIRE_NOTHROW(db.changeTable("table2"));
        REQUIRE_NOTHROW(db.insert("key_1", data));
        REQUIRE_NOTHROW(db.insert("key_2", data));

        REQUIRE_NOTHROW(db.traverse());
        REQUIRE_NOTHROW(db.dump("serialization.json"));
    }

    SECTION("deserialization test") {
        REQUIRE_NOTHROW(db.recover("serialization.json"));
        REQUIRE_NOTHROW(db.traverse());

        REQUIRE_NOTHROW(db.changeTable("table"));
        data["recover"] = "bar";
        REQUIRE_NOTHROW(db.insert("new-test", data));
        REQUIRE_NOTHROW(db.traverse());
    }
}