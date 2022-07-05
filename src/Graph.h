#pragma once

#include <string>
#include <vector>
#include <map>

namespace DEA {
    typedef struct Route {
      std::string origin;
      std::string state;
      std::string destination;
      double price;
  } Route;

  class Graph {
    public:
      int numNodes;
      std::map<std::string, std::vector<std::pair<std::string, double>>> adjMap;
      std::map<std::string, std::string> stateMap;

      Graph();
      Graph(std::vector<Route> const &routes);
      //~Graph();
      std::string getState(std::string origin);
      void addEdge(std::string origin, std::string state, std::string destination, double price);
      void printGraph();
      double getPrice(std::string origin, std::string destination);
      
    private:
    protected:  
  };
}