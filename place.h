#ifndef PLACE_H
#define PLACE_H

#include "parser_db.h"
#include <vector>
#include <algorithm>
#include <climits>  //提供 INT_MAX 的定义


//布局器类
class Placer
{
public:
    Placer(ParserDB& database) : db(database) {}    //构造函数，输入解析后的数据库
    void bruteForcePlacement();
    std::vector<Instance> getBestSolution() const { return best_solution; }

private:
    ParserDB& db;   //database的引用
    std::vector<Instance> best_solution;
    int min_total_length = INT_MAX;

    int calculateWireLength(const std::vector<Instance>& placement);
    int manhattanDistance(const Instance& a, const Instance& b);
};

#endif
