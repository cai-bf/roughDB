//
// Created by cbf on 19-5-13.
//
#include "../db/db.hpp"

class PerformanceOrderTest {
public:
    PerformanceOrderTest(){}
     void runTime(int times) {
        double insert_total = 0.0;
        DB db("test_db");
        db.addTable("test_");
        db.changeTable("test_");
        json val;
        val["test_str"] = "test";
        val["test_int"] = 100;
        val["test_double"] = 1000.0;
        clock_t start = clock();
        for (int i = 0; i < times; ++i) {
            std::string str = std::to_string(i);
            db.insert(str, val);
        }
        insert_total += (double)(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "insert " << times << " times costs " << insert_total << "seconds" << std::endl;

        srand(time(NULL));
        start = clock();
        double get_total = 0.0;
        for (int j = 0; j < times; ++j) {
            db.get(std::to_string(rand() / times));
        }
        get_total += (double)(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "rand get " << times << "times costs" << get_total << "seconds" << std::endl;

    }
};

int main() {
    int small = 10000;
    int middle = 100000;
    int large = 1000000;
    std::cout << "test 10000 items" << std::endl;
    PerformanceOrderTest *s = new PerformanceOrderTest();
    s->runTime(small);
    delete s;
    std::cout << "test 100000 items" << std::endl;
    PerformanceOrderTest *m = new PerformanceOrderTest();
    m->runTime(middle);
    delete m;
    std::cout << "test 1000000 items" << std::endl;
    PerformanceOrderTest *l = new PerformanceOrderTest();
    l->runTime(large);
    delete l;

    return 0;
}