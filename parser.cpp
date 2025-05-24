#include "parser_db.h"
#include <fstream>
#include <sstream>

//解析input然后加载到数据结构里
void ParserDB::parseInput(const string& filename)
{
    ifstream file(filename);
    string line;
    Net current_net;

    //逐行读取文件
    while (getline(file, line))
    {
        if (line.empty())   continue;

        istringstream iss(line);
        string token;
        iss >> token;

        if (token == "DieSize")
        {
            iss >> rows >> cols;
        }

        else if(token == "NumInstances")
        {
            int count;
            iss >> count;
            instances.reserve(count);
        }

        else if (token == "Inst")
        {
            string name;
            iss >> name;
            addInstance(name);
        }

        else if (token == "NumNets")
        {
            int count;
            iss >> count;
            nets.reserve(count);
        }

        else if (token == "Net")
        {
            string net_name;
            int pin_count;
            iss >> net_name >> pin_count;

            current_net = {net_name, {}};
            
            for (int i = 0; i < pin_count; ++i)
            {
                getline(file, line);
                istringstream pin_iss(line);
                string Pin, inst_name;
                pin_iss >> Pin >> inst_name;
                if (Pin == "Pin")
                {
                    current_net.connected_instances.push_back(inst_name);
                }
            }
            addNet(net_name, current_net.connected_instances);
        }
    }
}

//添加单元到数据库
void ParserDB::addInstance(const string& name)
{
    instances.push_back(Instance{name});
}

//添加线网到数据库
void ParserDB::addNet(const string& name, const vector<string>& pins)
{
    nets.push_back(Net{name, pins});
}
