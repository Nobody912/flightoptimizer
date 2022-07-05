#include <stdio.h>
#include <iostream>
#include "Graph.h"

using namespace DEA;

Graph::Graph() {
    numNodes = 0;
    adjMap.clear();
}

Graph::Graph(std::vector<Route> const &routes) {
    for (unsigned i = 0; i < routes.size(); i++) {
        addEdge(routes[i].origin, routes[i].state, routes[i].destination, routes[i].price);
    }
    numNodes = adjMap.size();
}

void Graph::addEdge(std::string origin, std::string state, std::string destination, double price) {
    if (adjMap.find(origin) == adjMap.end()) {
        std::vector<std::pair<std::string, double>> newVector;
        newVector.push_back(std::make_pair(destination, price));
        adjMap.insert(std::make_pair(origin, newVector));
    }
    else {
        adjMap[origin].push_back(std::make_pair(destination, price));
    }
    numNodes = adjMap.size();

    if (stateMap.find(state) == stateMap.end()) {
        stateMap.insert(std::make_pair(origin, state));
    }
    else {
        stateMap[origin] = state;
    }
}

std::string Graph::getState(std::string origin) {
    return stateMap[origin];
}

double Graph::getPrice(std::string origin, std::string destination) {
    for (unsigned i = 0; i < adjMap[origin].size(); i++) {
        if (adjMap[origin][i].first == destination) {
            return adjMap[origin][i].second;
        }
    }
    return 0;
}

void Graph::printGraph()
{
    std::cout << "----- AIRPORT GRAPH -----" << std::endl;
    for (auto it = adjMap.begin(); it != adjMap.end(); ++it) {
        std::cout << it->first << ": ";
        for (unsigned i = 0; i < it->second.size(); i++) {
            std::cout << "\t" << it->second[i].first << " ($" << it->second[i].second << ") " << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}