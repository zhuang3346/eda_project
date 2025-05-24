#include "parser_db.h"
#include "place.h"
#include "exporter.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "用法: " << argv[0] << " 输入文件 输出文件" << std::endl;
        return 1;
    }

    ParserDB db;
    db.parseInput(argv[1]);
    Placer placer(db);
    placer.bruteForcePlacement();
    exporter(placer.getBestSolution(), argv[2]);

    std::cout << "布局完成，结果已保存到 " << argv[2] << std::endl;
    return 0;
}