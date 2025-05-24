#include "place.h"
#include <iostream>
#include <algorithm>

//曼哈顿距离
int Placer::manhattanDistance(const Instance& a, const Instance& b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

//计算当前布局的总线长
int Placer::calculateWireLength(const std::vector<Instance>& instancePerm)
{
    int total = 0;
    for (const Net& net : db.nets)
    {
        std::vector<Instance> connected;
        for (const std::string& inst_name : net.connected_instances)
        {
            //在当前排列中查找名字为inst_name的单元（instancePerm非顺序传入）
            auto it = std::find_if(
                instancePerm.begin(),
                instancePerm.end(),
                [&](const Instance& inst) { return inst.name == inst_name; }
            );
            if (it != instancePerm.end())
            {
                connected.push_back(*it);
            }
        }

        for (int i = 0; i < connected.size(); i++)
        {
            for (int j = i + 1; j < connected.size(); j++)
            {
                total += manhattanDistance(connected[i], connected[j]);
            }
        }
    }
    return total;
}

//穷举布局
void Placer::bruteForcePlacement()
{
    int N = db.instances.size();
    int M = db.rows * db.cols;

    std::vector<std::pair<int, int>> all_cells;
    for (int i = 0; i < db.rows; i++)
        for (int j = 0; j < db.cols; j++)
            all_cells.push_back({i, j});

    std::vector<int> select_mask(M, 0);
    std::fill(select_mask.end() - N, select_mask.end(), 1);

    best_solution.clear();

    do {
        std::vector<std::pair<int, int>> selected_cells;
        for (int i = 0; i < M; i++)
            if (select_mask[i]) selected_cells.push_back(all_cells[i]);


        //单元全排列
        std::vector<Instance> instance_perm = db.instances;
        std::sort(
            instance_perm.begin(),
            instance_perm.end(),
            [](const Instance& a, const Instance& b) { return a.name < b.name; }
        );
        do {
            for (int k = 0; k < N; ++k)
            {
                instance_perm[k].x = selected_cells[k].first;
                instance_perm[k].y = selected_cells[k].second;
            }
            int current_length = calculateWireLength(instance_perm);
            if (current_length < min_total_length)
            {
                min_total_length = current_length;
                best_solution = instance_perm;
            }
        } while (std::next_permutation(instance_perm.begin(), instance_perm.end(), [](const Instance& a, const Instance& b) { return a.name < b.name; }));

    } while (std::next_permutation(select_mask.begin(), select_mask.end()));
}
