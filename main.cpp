#include "graph.h"
#include <iostream>

int main() {
    Graph g;
    
    std::vector<std::pair<NodeId, std::string>> incomingNodes = {
        {1, "author"},
        {2, "paper"},
        {3, "paper"},
        {4, "author"}
    };
    
    for (auto& node : incomingNodes) {
        g.addNode(node.first, node.second);
    }
    
    std::vector<std::tuple<NodeId, NodeId, std::string>> incomingEdges = {
        {1, 2, "authored"},
        {1, 3, "authored"},
        {2, 3, "cites"},
        {1, 4, "coauthor"}
    };
    
    for (auto& edge : incomingEdges) {
        g.addEdge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge));
    }
    
    // Test: Get all incoming edges to node 2
    std::cout << "\n=== Node 2 Incoming Edges ===" << std::endl;
    Node& node2 = g.getNode(2);
    for (auto& edgeTypePair : node2.incoming) {
        EdgeTypeId typeId = edgeTypePair.first;
        std::vector<EdgeRef>& refs = edgeTypePair.second;
        
        std::cout << "Type " << typeId << ": " << refs.size() << " edge(s)" << std::endl;
        for (auto& ref : refs) {
            Edge e = g.resolveEdge(typeId, ref);
            std::cout << "  " << e.from << " -> " << e.to << std::endl;
        }
    }
    
    return 0;
}