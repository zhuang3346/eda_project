#ifndef PARSER_DB_H
#define PARSER_DB_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Instance
{
    string name;
    int x = -1;
    int y = -1;
};

struct Net
{
    string name;
    vector<string> connected_instances;
};

class ParserDB 
{
public:
    int rows = 0;
    int cols = 0;
    vector<Instance> instances;
    vector<Net> nets;
    
    void parseInput(const string& filename);

    void addInstance(const string& name);

    void addNet(const string& name, const vector<string>& pins);
};

#endif
