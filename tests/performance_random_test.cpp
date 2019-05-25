//
// Created by cbf on 19-5-13.
//
#include "../db/db.hpp"

class PerformanceRandomTest {
public:
    PerformanceRandomTest(){}
    void runTime(int times) {
        double insert_total = 0.0;
        DB db("test_db");
        db.addTable("test_");
        db.changeTable("test_");
        json val;
        val["test_str"] = "test";
        val["test_int"] = 100;
        val["test_double"] = 1000.0;

        srand(time(NULL));

        clock_t start = clock();
        for (int i = 0; i < times; ++i) {
            std::string str = std::to_string(rand() / 100);
            db.updateOrInsert(str, val);
        }
        insert_total += (double)(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "random update or insert " << times << " times costs " << insert_total << "seconds" << std::endl;


        start = clock();
        double get_total = 0.0;
        for (int j = 0; j < times; ++j) {
            auto key = std::to_string(rand() / 100);
            if (db.exist(key))
                db.get(key);
        }
        get_total += (double)(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "while exists random get " << times << " times costs " << get_total << "seconds" << std::endl;

    }
};

int main() {
    int small = 10000;
    int middle = 100000;
    int large = 1000000;
    int super = 10000000;
    std::cout << "test 10000 items" << std::endl;
    PerformanceRandomTest *s = new PerformanceRandomTest();
    s->runTime(small);
    delete s;
    std::cout << "test 100000 items" << std::endl;
    PerformanceRandomTest *m = new PerformanceRandomTest();
    m->runTime(middle);
    delete m;
    std::cout << "test 1000000 items" << std::endl;
    PerformanceRandomTest *l = new PerformanceRandomTest();
    l->runTime(large);
    delete l;

    std::cout << "test 10000000 items" << std::endl;
    PerformanceRandomTest *su = new PerformanceRandomTest();
    su->runTime(super);
    delete su;

    return 0;
}