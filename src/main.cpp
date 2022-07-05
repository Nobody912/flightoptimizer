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

using cs225::HSLAPixel;

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

        std::cout << std::endl;
        std::cout << "----------------------------" << std::endl;

        price = 0.0;
        
        std::cout << std::endl;
        std::cout << "----------------------------" << std::endl;
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
    }
}

void drawPaths(Graph* g, std::vector<std::string> BFSRawPath, std::vector<std::string> DijPath, std::string filename) {
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

        testMapProjection->exportImage(filename);
    } else {
        std::cout << "[!] INVALID AIRPORT CODE, CANNOT PROCESS!" << std::endl;
    }
}

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cerr << "Missing arguments [ORIGIN], [DESTINATION], or [FILENAME]." << std::endl;
        return -1;
    }

    Graph* testGraph1 = new Graph();

    std::ifstream ifs("data.json");
    json jf = json::parse(ifs);

    for (auto origin : jf) {
        for (auto destination : origin["validDestinations"].items()) {
            // std::cout << origin["code"] << " " << destination.key() << " " << destination.value() << std::endl;
            testGraph1->addEdge(origin["code"], origin["state"], destination.key(), destination.value());
        }
    }

    // DANGER!! THIS LINE OF CODE WILL FLOOD YOUR TERMINAL
    // testGraph1->printGraph();

    BFSTraversal* testBFSTraversal = new BFSTraversal(testGraph1);
    std::vector<std::string> raw_path = testBFSTraversal->getShortestPath(argv[1], argv[2]);
    // std::vector<std::pair<std::string, std::string>> path = pairize(raw_path); 

    Astar* testAstar = new Astar(testGraph1);
    std::vector<std::string> Astarpath = testAstar->getCheapest(argv[1], argv[2]);

    printPaths(testGraph1, raw_path, Astarpath);
    drawPaths(testGraph1, raw_path, Astarpath, argv[3]);

    // if (raw_path[0] != "DNE" || Astarpath[0] != "DNE") {
    //     // FLIGHT INFO PRINTER
    //     double price = 0.0;

    //     std::cout << "----------------------------" << std::endl;
    //     std::cout << "Fewest Stops Route" << std::endl;
    //     std::cout << "----- FLIGHT ITINERARY -----" << std::endl;
    //     std::cout << "Departing: " << path.front().first << std::endl;
    //     std::cout << "Arriving: " << path.back().second << std::endl;
    //     std::cout << "----------------------------" << std::endl;

    //     for (unsigned i = 0; i < path.size(); i++) {
    //         std::cout << "FLIGHT " << i + 1 << ": " << path[i].first << " → " << path[i].second << std::endl;
    //         std::cout << "  PRICE: $" << testGraph1->getPrice(path[i].first, path[i].second) << std::endl;
    //         price += testGraph1->getPrice(path[i].first, path[i].second);
    //     }
    //     std::cout << "----------------------------" << std::endl;
    //     std::cout << "TOTAL PRICE: $" << price << std::endl;

    //     std::cout << std::endl;
    //     std::cout << "----------------------------" << std::endl;

    //     price = 0.0;
        
    //     std::cout << std::endl;
    //     std::cout << "----------------------------" << std::endl;
    //     std::cout << "Cheapest Route" << std::endl;
    //     std::cout << "----- FLIGHT ITINERARY -----" << std::endl;
    //     std::cout << "Departing: " << Astarpath.front() << std::endl;
    //     std::cout << "Arriving: " << Astarpath.back() << std::endl;
    //     std::cout << "----------------------------" << std::endl;

    //     for (unsigned i = 0; i < Astarpath.size() - 1; i++) {
    //         std::cout << "FLIGHT " << i + 1 << ": " << Astarpath[i] << " → " << Astarpath[i+1] << std::endl;
    //         std::cout << "  PRICE: $" << testGraph1->getPrice(Astarpath[i], Astarpath[i+1]) << std::endl;
    //         price += testGraph1->getPrice(Astarpath[i], Astarpath[i+1]);
    //     }
    //     std::cout << "----------------------------" << std::endl;
    //     std::cout << "TOTAL PRICE: $" << price << std::endl;

    //     // Map Drawing
    //     MapProjection* testMapProjection = new MapProjection();

    //     // Fill in states
    //     std::vector<std::string> commonAirports;
    //     if (raw_path[0] != "DNE" || Astarpath[0] != "DNE") {
    //         for (auto airport1 : raw_path) {
    //             for (auto airport2 : Astarpath) {
    //                 if (airport1 == airport2) {
    //                     commonAirports.push_back(airport1);
    //                 }
    //             }
    //         }
    //         for (auto state : commonAirports) {
    //             testMapProjection->floodFill(testGraph1->getState(state), 271.0, 0.84, 0.67);
    //         }
    //     }

    //     if (raw_path[0] != "DNE") {
    //         for (auto origin : path) {
    //             testMapProjection->floodFill(testGraph1->getState(origin.first), 0.0, 0.84, 0.6);
    //         }
    //         testMapProjection->floodFill(testGraph1->getState(path[path.size() - 1].second), 0.0, 0.84, 0.6);
    //     }

    //     if (Astarpath[0] != "DNE") {
    //         for (auto state : Astarpath) {
    //             testMapProjection->floodFill(testGraph1->getState(state), 217.0, 0.91, 0.6);
    //         }
    //     }

    //     // Draw lines
    //     if (raw_path[0] != "DNE") {
    //         for (auto pair : path) {
    //             testMapProjection->drawLine(testGraph1->getState(pair.first), testGraph1->getState(pair.second), 0.0, 0.7, 0.35);
    //         }
    //     }

    //     if (Astarpath[0] != "DNE") {
    //         for (auto pair : pairize(Astarpath)) {
    //             testMapProjection->drawLine(testGraph1->getState(pair.first), testGraph1->getState(pair.second), 226.0, 0.71, 0.4);
    //         }
    //     }

    //     // Draw origin and destination
    //     if (raw_path[0] != "DNE" || Astarpath[0] != "DNE") {
    //         testMapProjection->drawOrigin(testGraph1->getState(argv[1]));
    //         testMapProjection->drawDestination(testGraph1->getState(argv[2]));
    //     }

    //     testMapProjection->exportImage();
    // } else {
    //     std::cout << "[!] INVALID AIRPORT CODE, CANNOT PROCESS!" << std::endl;
    // }
}