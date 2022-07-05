#include <fstream>
#include <iostream>
#include <string>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "json.hpp"
#include "BFSTraversal.h"
#include "MapProjection.h"
#include "Graph.h"
#include "Astar.h"

using namespace DEA;
using json = nlohmann::json;

std::vector<std::pair<std::string, std::string>> pairize(std::vector<std::string> path) {
    std::vector<std::pair<std::string, std::string>> result;
    for (unsigned i = 0; i < path.size() - 1; i++) {
        result.push_back(std::make_pair(path[i], path[i + 1]));
    }
    return result;
}

void printPaths(Graph* g, std::vector<std::string> BFSRawPath, std::vector<std::string> DijPath) {
    std::vector<std::pair<std::string, std::string>> path = pairize(BFSRawPath);
    if (BFSRawPath[0] != "DNE" || DijPath[0] != "DNE") {
        // FLIGHT INFO PRINTER
        double price = 0.0;

        std::cout << "----------------------------" << std::endl;
        std::cout << "Fewest Stops Route" << std::endl;
        std::cout << "----- FLIGHT ITINERARY -----" << std::endl;
        std::cout << "Departing: " << path.front().first << std::endl;
        std::cout << "Arriving: " << path.back().second << std::endl;
        std::cout << "----------------------------" << std::endl;

        for (unsigned i = 0; i < path.size(); i++) {
            std::cout << "FLIGHT " << i + 1 << ": " << path[i].first << " → " << path[i].second << std::endl;
            std::cout << "  PRICE: $" << g->getPrice(path[i].first, path[i].second) << std::endl;
            price += g->getPrice(path[i].first, path[i].second);
        }
        std::cout << "----------------------------" << std::endl;
        std::cout << "TOTAL PRICE: $" << price << std::endl;

        price = 0.0;
        
        std::cout << "Cheapest Route" << std::endl;
        std::cout << "----- FLIGHT ITINERARY -----" << std::endl;
        std::cout << "Departing: " << DijPath.front() << std::endl;
        std::cout << "Arriving: " << DijPath.back() << std::endl;
        std::cout << "----------------------------" << std::endl;

        for (unsigned i = 0; i < DijPath.size() - 1; i++) {
            std::cout << "FLIGHT " << i + 1 << ": " << DijPath[i] << " → " << DijPath[i+1] << std::endl;
            std::cout << "  PRICE: $" << g->getPrice(DijPath[i], DijPath[i+1]) << std::endl;
            price += g->getPrice(DijPath[i], DijPath[i+1]);
        }
        std::cout << "----------------------------" << std::endl;
        std::cout << "TOTAL PRICE: $" << price << std::endl;
        std::cout << "----------------------------" << std::endl;
    } else {
        std::cout << "[!] INVALID AIRPORT CODE, CANNOT PROCESS!" << std::endl;
    }
}

void drawPaths(Graph* g, std::vector<std::string> BFSRawPath, std::vector<std::string> DijPath) {
    std::vector<std::pair<std::string, std::string>> path = pairize(BFSRawPath);
    if (BFSRawPath[0] != "DNE" || DijPath[0] != "DNE") {
        // Map Drawing
        MapProjection* testMapProjection = new MapProjection();

        // Fill in states
        std::vector<std::string> commonAirports;
        if (BFSRawPath[0] != "DNE" || DijPath[0] != "DNE") {
            for (auto airport1 : BFSRawPath) {
                for (auto airport2 : DijPath) {
                    if (airport1 == airport2) {
                        commonAirports.push_back(airport1);
                    }
                }
            }
            for (auto state : commonAirports) {
                testMapProjection->floodFill(g->getState(state), 271.0, 0.84, 0.67);
            }
        }

        if (BFSRawPath[0] != "DNE") {
            for (auto origin : path) {
                testMapProjection->floodFill(g->getState(origin.first), 0.0, 0.84, 0.6);
            }
            testMapProjection->floodFill(g->getState(path[path.size() - 1].second), 0.0, 0.84, 0.6);
        }

        if (DijPath[0] != "DNE") {
            for (auto state : DijPath) {
                testMapProjection->floodFill(g->getState(state), 217.0, 0.91, 0.6);
            }
        }

        // Draw lines
        if (BFSRawPath[0] != "DNE") {
            for (auto pair : path) {
                testMapProjection->drawLine(g->getState(pair.first), g->getState(pair.second), 0.0, 0.7, 0.35);
            }
        }

        if (DijPath[0] != "DNE") {
            for (auto pair : pairize(DijPath)) {
                testMapProjection->drawLine(g->getState(pair.first), g->getState(pair.second), 226.0, 0.71, 0.4);
            }
        }

        // Draw origin and destination
        if (BFSRawPath[0] != "DNE" || DijPath[0] != "DNE") {
            testMapProjection->drawOrigin(g->getState(DijPath.front()));
            testMapProjection->drawDestination(g->getState(DijPath.back()));
        }

        testMapProjection->exportImage("flightmap-test.png");
    } else {
        std::cout << "[!] INVALID AIRPORT CODE, CANNOT PROCESS!" << std::endl;
    }
    std::cout << std::endl;
}

Graph* createGraph() {
    Graph* graph = new Graph();

    std::ifstream ifs("data.json");
    json jf = json::parse(ifs);

    for(auto origin : jf) {
        for(auto destination : origin["validDestinations"].items()) {
            graph->addEdge(origin["code"], origin["state"], destination.key(), destination.value());
        }
    }
    return graph;
}


// /**
//  * @brief print BFS and Dij results
//  * 
//  * @param g graph
//  * @param BFSPath path of BFS
//  * @param DijPath path of Dij
//  */
// void test(Graph* g, std::vector<std::pair<std::string, std::string>> BFSPath, std::vector<std::string> DijPath) {
//     double price = 0.0;

//     std::cout << "----------------------------" << std::endl;
//     std::cout << "Fewest Stops Route" << std::endl;
//     std::cout << "----- FLIGHT ITINERARY -----" << std::endl;
//     std::cout << "Departing: " << BFSPath.front().first << std::endl;
//     std::cout << "Arriving: " << BFSPath.back().second << std::endl;
//     std::cout << "----------------------------" << std::endl;

//     for (unsigned i = 0; i < BFSPath.size(); i++) {
//         std::cout << "FLIGHT " << i + 1 << ": " << BFSPath[i].first << " → " << BFSPath[i].second << std::endl;
//         std::cout << "  PRICE: $" << g->getPrice(BFSPath[i].first, BFSPath[i].second) << std::endl;
//         price += g->getPrice(BFSPath[i].first, BFSPath[i].second);
//     }
//     std::cout << "----------------------------" << std::endl;
//     std::cout << "TOTAL PRICE: $" << price << std::endl;

//     price = 0.0;
    
//     std::cout << "----------------------------" << std::endl;
//     std::cout << "Cheapest Route" << std::endl;
//     std::cout << "----- FLIGHT ITINERARY -----" << std::endl;
//     std::cout << "Departing: " << DijPath.front() << std::endl;
//     std::cout << "Arriving: " << DijPath.back() << std::endl;
//     std::cout << "----------------------------" << std::endl;

//     for (unsigned i = 0; i < DijPath.size() - 1; i++) {
//         std::cout << "FLIGHT " << i + 1 << ": " << DijPath[i] << " → " << DijPath[i+1] << std::endl;
//         std::cout << "  PRICE: $" << g->getPrice(DijPath[i], DijPath[i+1]) << std::endl;
//         price += g->getPrice(DijPath[i], DijPath[i+1]);
//     }
//     std::cout << "----------------------------" << std::endl;
//     std::cout << "TOTAL PRICE: $" << price << std::endl;
//     std::cout << "----------------------------" << std::endl;
//     std::cout << std::endl;
// }


int main() {
    Graph* g = createGraph();

    BFSTraversal* testBFSTraversal = new BFSTraversal(g);
    Astar* testDij = new Astar(g);

    /**
     * @brief BFS and Dij result in same path, one stop, total of $210
     * SFO -> LAS -> MKT
     */
    std::string start = "SFO";
    std::string dest = "MKT";
    std::vector<std::string> BFSPath = testBFSTraversal->getShortestPath(start, dest);
    std::vector<std::string> Dijpath = testDij->getCheapest(start, dest);
    std::cout << "-------testOneStop----------" << std::endl;
    printPaths(g, BFSPath, Dijpath);

    /**
     * @brief BFS and Dij result in same path, non stop, total of $168
     * CAE -> MCO
     */
    start = "CAE";
    dest = "MCO";
    BFSPath = testBFSTraversal->getShortestPath(start, dest);
    Dijpath = testDij->getCheapest(start, dest);
    std::cout << "-------testNonStop----------" << std::endl;
    printPaths(g, BFSPath, Dijpath);

    /**
     * @brief BFS and Dij result in different path,
     *      BFS: SFO -> LGA, total: $245
     *      Dij: SFO -> MDW -> LGA, total: $184
     * 
     */
    start = "SFO";
    dest = "LGA";
    BFSPath = testBFSTraversal->getShortestPath(start, dest);
    Dijpath = testDij->getCheapest(start, dest);
    std::cout << "-------testDifferent--------" << std::endl;
    printPaths(g, BFSPath, Dijpath);

    /**
     * @brief BFS and Dij result in same path, non stop, total of $168
     * CAE -> MCO
     */
    start = "AAA";
    dest = "SFO";
    BFSPath = testBFSTraversal->getShortestPath(start, dest);
    Dijpath = testDij->getCheapest(start, dest);
    std::cout << "----testNonexistentStart----" << std::endl;
    printPaths(g, BFSPath, Dijpath);

    /**
     * @brief BFS and Dij result in same path, non stop, total of $168
     * CAE -> MCO
     */
    start = "SFO";
    dest = "AAA";
    BFSPath = testBFSTraversal->getShortestPath(start, dest);
    Dijpath = testDij->getCheapest(start, dest);
    std::cout << "------testNonexistentEnd----" << std::endl;
    printPaths(g, BFSPath, Dijpath);

    /**
     * @brief BFS and Dij result in same path, non stop, total of $168
     * CAE -> MCO
     */
    start = "SFO";
    dest = "LGA";
    BFSPath = testBFSTraversal->getShortestPath(start, dest);
    Dijpath = testDij->getCheapest(start, dest);
    std::cout << "-------testDraw-------------" << std::endl;
    printPaths(g, BFSPath, Dijpath);
    drawPaths(g, BFSPath, Dijpath);
}