//
// Created by cbf on 19-5-8.
//
#define CATCH_CONFIG_MAIN
#include "../dependencies/catch.hpp"

#include "../db/db.hpp"

TEST_CASE("db test") {
    DB db("database");
    json data;

    SECTION("table test") {
        REQUIRE_NOTHROW(db.addTable("table"));
        REQUIRE_THROWS_WITH(
                db.addTable("table"),
                "the table name has already exists!\n"
        );
        REQUIRE(db.checkTable("table") == true);
        REQUIRE_NOTHROW(db.removeTable("table"));
        REQUIRE_THROWS_WITH(
                db.removeTable("table"),
                "the table doesn't exist!\n"
        );
        REQUIRE_NOTHROW(db.addTable("table"));
        REQUIRE_THROWS_WITH(
                db.changeTable("foo"),
                "the table doesn't exist!\n"
        );
        REQUIRE_NOTHROW(db.changeTable("table"));
    }

    SECTION("operations test") {
        REQUIRE_NOTHROW(db.addTable("table"));
        REQUIRE_NOTHROW(db.changeTable("table"));
        REQUIRE(db.count() == 0);
        data["foo"] = "bar";
        REQUIRE_NOTHROW(db.insert("foo", data));
        REQUIRE(db.get("foo") == data);
        REQUIRE_NOTHROW(db.update("foo", data));
        REQUIRE_NOTHROW(db.updateOrInsert("test", data));
        REQUIRE_NOTHROW(db.remove("test"));
        REQUIRE(db.exist("foo") == true);
        REQUIRE_NOTHROW(db.traverse());
        REQUIRE(db.get("foo") == data);
        REQUIRE(db.get("not-exist") == NULL);
        json result;
        REQUIRE_NOTHROW(db.select(result));
        std::cout << result << std::endl;
        REQUIRE_NOTHROW(db.addTable("table2"));
        REQUIRE_NOTHROW(db.showTables());
    }
}
