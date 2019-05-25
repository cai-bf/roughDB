//
// Created by cbf on 19-5-13.
//
#include "../db/db.hpp"

class PerformanceIOTest {
public:
    PerformanceIOTest(){}
    void runTime(int times) {
        DB db("test_db");
        db.addTable("test_");
        db.changeTable("test_");
        json val;
        val["test_str"] = "test";
        val["test_int"] = 100;
        val["test_double"] = 1000.0;

        srand(time(NULL));


        for (int i = 0; i < times; ++i) {
            std::string str = std::to_string(rand() / 1000);
            db.updateOrInsert(str, val);
        }

        clock_t start = clock();
        db.dump("io_test.json");
        double dump_time = (double)(clock() - start) / CLOCKS_PER_SEC;

        db.removeTable("test_");

        start = clock();
        db.recover("io_test.json");
        double recover_time = (double)(clock() - start) / CLOCKS_PER_SEC;

        if (remove("io_test.json") == 1) {
            // pass
        }

        std::cout << "random update or insert " + times << std::endl;
        std::cout << "dump to file costs " << dump_time << " seconds" << std::endl;
        std::cout << "recover from file costs " << recover_time << " seconds" << std::endl;
    }
};

int main() {
    int small = 10000;
    int middle = 100000;
    int large = 1000000;
//    std::cout << "test 10000 items" << std::endl;
//    PerformanceIOTest *s = new PerformanceIOTest();
//    s->runTime(small);
//    delete s;
    std::cout << "test 100000 items" << std::endl;
    PerformanceIOTest *m = new PerformanceIOTest();
    m->runTime(middle);
    delete m;
//    std::cout << "test 1000000 items" << std::endl;
//    PerformanceIOTest *l = new PerformanceIOTest();
//    l->runTime(large);
//    delete l;

    return 0;
}