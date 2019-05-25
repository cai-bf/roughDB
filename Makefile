P = g++ -std=c++11

test: kvnode-test btree-test db-test serialization-test

kvnode-test:
	@$(P) -o tests/kvnode tests/kvnode_test.cpp
	@./tests/kvnode

btree-test:
	@$(P) -o tests/btree tests/btree_test.cpp
	@./tests/btree

db-test:
	@$(P) -o tests/db tests/db_test.cpp
	@./tests/db

serialization-test:
	@$(P) -o tests/serialization tests/serialization_test.cpp
	@./tests/serialization

performance-test: order-test random-test io-test

order-test:
	@$(P) -o tests/per-order tests/performance_order_test.cpp
	@./tests/per-order

random-test:
	@$(P) -o tests/per-random tests/performance_random_test.cpp
	@./tests/per-random

io-test:
	@$(P) -o tests/per-io tests/performance_io_test.cpp
	@./tests/per-io