cmake_minimum_required(VERSION 3.10)
project(cpp_simple_DB)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_simple_DB main.cpp db/btnode.hpp db/kvnode.hpp db/btree.hpp db/db.hpp tests/kvnode_test.cpp tests/btree_test.cpp tests/db_test.cpp tests/serialization_test.cpp tests/performance_order_test.cpp tests/performance_random_test.cpp tests/performance_io_test.cpp)