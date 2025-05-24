#include "parser_db.h"
#include <fstream>

void exporter(const std::vector<Instance>& instances, const std::string& filename)
{
    std::ofstream output(filename);
    for (const Instance& inst : instances)
    {
        output << inst.name << " " << inst.x << " " << inst.y << "\n";
    }
}