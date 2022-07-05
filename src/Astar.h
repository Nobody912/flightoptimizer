#include <iostream>
#include <string>
#include <queue>
#include <climits>
#include <map>
#include <algorithm>


#include "Graph.h"

using namespace std;

struct minHeap {
  vector<pair<double, string>> q;
  void push(pair<double, string> i) {
    q.push_back(i);
    sort(q.begin(), q.end());
  }
  pair<double, string> pop(){
    auto t = q[0];
    q.erase(q.begin());
    return t;
  }
};

class Astar {
    public:
        Astar(DEA::Graph* g);
        vector<string> getCheapest(string start, string end);
    private:
        DEA::Graph* graph;
        vector<string> keys;

        std::map<std::string, std::vector<std::pair<std::string, double>>> adj;


};

