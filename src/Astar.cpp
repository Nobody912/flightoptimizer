#include "Astar.h"

using namespace std;

Astar::Astar(DEA::Graph* g) {
    graph = g;
    adj = g->adjMap;
    for(map<string, vector<pair<string, double>>>::iterator it = adj.begin(); it != adj.end(); ++it)
        keys.push_back(it->first);
}

vector<string> Astar::getCheapest(string start, string end) {
  map<string, double> dist;
  map<string, string> prev;

  // priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>>  q;
  minHeap h;

  if (adj.find(start) == adj.end() || adj.find(end) == adj.end()) {
    return vector<string>({"DNE"});
  }

  for(string v : keys) {
    dist.insert(make_pair(v, INT_MAX));
    prev.insert(make_pair(v, ""));
    if (v != start)
      h.push(pair<double, string>(INT_MAX, v));
    else
      h.push(pair<double, string>(0, start));
  }

  dist[start] = 0;

  while(h.q.size() != 0) {
    pair<double, string> u = h.pop();
    for (pair<double, string> v : h.q) {
      vector<pair<string, double>> adjV = adj[u.second];
      int index = -1;
      for (size_t i = 0; i < adjV.size(); i++) {
        auto p = adjV[i];
        if (p.first == v.second) {
          index = i;
          break;
        }
      }
      // auto it = find(adjV.begin(), adjV.end(), v.second);
      // if (it != adjV.end()) {
      if (index != -1) {
        // double temp = dist[u.second] + adjV[distance(adjV.begin(), it)].second;
        double temp = dist[u.second] + adjV[index].second;
        if (temp < dist[v.second]) {
          dist[v.second] = temp;
          prev[v.second] = u.second;
          for(size_t i = 0; i < h.q.size(); i++) {
            if (h.q[i].second == v.second) {
              h.q[i].first = temp;
              sort(h.q.begin(), h.q.end());
            }
          }
        }
      }
    }
  }

  string a = end;
  vector<string> path;
  while(a != "") {
    path.insert(path.begin(), a);
    a = prev[a];
  }
  if (path.size() == 1) {
    return vector<string>({start});
  }
  return path;
}
