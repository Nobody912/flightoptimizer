#include <string>
#include <vector>

#include "Graph.h"

namespace DEA {
  class BFSTraversal {
    public:
      typedef struct PathNode {
        std::string name = "";
        PathNode* parent;

        bool operator==(const PathNode* rhs) {
          return this->name == rhs->name;
        }
      } PathNode;


      BFSTraversal(DEA::Graph *graph);
      ~BFSTraversal();
      std::vector<std::string> getShortestPath(std::string origin, std::string destination);

    private:
      Graph* graph_;
      std::vector<std::pair<std::string, std::string>> path_;

      void forwardReconstruct(std::vector<std::string> *Path, PathNode* targetNode);
  };
}