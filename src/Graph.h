#if ! defined ( GRAPH_H )
#define GRAPH_H

#include <string>
#include <map>
using namespace std;

class Graph
{
public:
    Graph();
    virtual ~Graph();

    void AddNode(const string &node);

    void Top10NodeHits();

    void AddEdge(const string &nodeA, const string &nodeB);

    void CreateDotFile(const string &fileName);

protected:
    map<string,int> nodes;
    map<pair<string,string>,int> edges;
};

#endif // GRAPH_H