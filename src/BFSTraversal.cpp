#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include "BFSTraversal.h"

using namespace DEA;

BFSTraversal::BFSTraversal(Graph *graph)  {
    graph_ = graph;
}

std::vector<std::string> BFSTraversal::getShortestPath(std::string origin, std::string destination) {
    if (origin == destination) {
        return {origin};
    }

    if (graph_->adjMap.find(origin) == graph_->adjMap.end() || graph_->adjMap.find(destination) == graph_->adjMap.end()) {
        return {"DNE"};
    }

    std::vector<std::string> path;
    std::vector<std::string> visited;
    std::vector<PathNode*> queue;

    PathNode originNode = {origin, NULL};
    PathNode targetNode;
    
    queue.push_back(&originNode);
    while (!queue.empty()) {
        PathNode* currentParent = queue.front();
        queue.erase(queue.begin());
        visited.push_back(currentParent->name);

        for (auto edge : graph_->adjMap[currentParent->name]) {
            PathNode* node = new PathNode();
            node->name = edge.first;
            node->parent = currentParent;

            if (node->name == destination) {
                targetNode = *node;
                break;
            }

            if (std::find(visited.begin(), visited.end(), node->name) == visited.end() ||
                std::find(queue.begin(), queue.end(), node) == queue.end()) {
                queue.push_back(node);
            }
        }
        if (targetNode.name == destination) {
            break;
        }
    }
    
    if (targetNode.name == destination) {
        // std::cout << "Reconstructing..." << std::endl;
        BFSTraversal::forwardReconstruct(&path, &targetNode);
        // std::cout << "Reversing..." << std::endl;
        std::reverse(path.begin(), path.end());
        path.insert(path.begin(), origin);
        return path;
    }
    else {
        return {origin};
    }
}

void BFSTraversal::forwardReconstruct(std::vector<std::string>* path, PathNode* targetNode) {
    while (targetNode->parent != NULL) {
        path->push_back(targetNode->name);
        targetNode = targetNode->parent;
    }
}