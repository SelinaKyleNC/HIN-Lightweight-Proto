#include "graph.h"
#include <iostream>

// Initialize the graph with empty type counters
Graph::Graph() {
    nextEdgeTypeId = 0;
    nextNodeTypeId = 0;
}

// Add a node with a type name
// The type is registered dynamically if it hasn't been seen before
// After registration, everything uses integer IDs
void Graph::addNode(NodeId id, std::string nodeTypeName) {
    // Get or register the node type (string -> NodeTypeId conversion happens here)
    NodeTypeId typeId = getOrRegisterNodeType(nodeTypeName);

    // Create the node with the integer type ID
    Node n;
    n.id = id;
    n.nodeType = typeId;

    // Store in central nodes map
    nodes[id] = n;
    std::cout << "Added node " << id << " (type: " << nodeTypeName << ")" << std::endl;
}


// Register a node type if new, or return existing ID if already seen
// This is a registration boundary, last time we see the string name
NodeTypeId Graph::getOrRegisterNodeType(std::string typeName) {
       if (nodeTypeRegistry.find(typeName) != nodeTypeRegistry.end()) {
           return nodeTypeRegistry[typeName];
       }

       // New type: assign next available ID
       NodeTypeId typeId = nextNodeTypeId++;
       nodeTypeRegistry[typeName] = typeId;
       std::cout << "Registered node type '" << typeName << "' as type " << typeId << std::endl;
       return typeId;
   }

   // Register an edge type if new, or return existing ID if already seen
    // Also creates central storage vector for this edge type
    // This is a registration boundary, last time we see the string name
EdgeTypeId Graph::getOrRegisterEdgeType(std::string typeName) {
    if (edgeTypeRegistry.find(typeName) != edgeTypeRegistry.end()) {
        return edgeTypeRegistry[typeName];
    }
    EdgeTypeId typeId = nextEdgeTypeId++;
    edgeTypeRegistry[typeName] = typeId;
    edgesByType[typeId] = std::vector<Edge>();
    std::cout << "Registered edge type '" << typeName << "' as type " << typeId << std::endl;
    return typeId;
}


// Add an edge between two nodes
// Edge type registers dynamically if it's the first time we see it
// Updates both nodes' reference maps
void Graph::addEdge(NodeId from, NodeId to, std::string edgeTypeName) {
    EdgeTypeId typeId = getOrRegisterEdgeType(edgeTypeName);

    // Create the edge object with just the endpoints
    Edge e;
    e.from = from;
    e.to = to;

    // Store the edge in central storage for this type
    edgesByType[typeId].push_back(e);

    // Get the index where this edge was stored (becomes the EdgeId)
    EdgeId edgeId = edgesByType[typeId].size() - 1;
    
    // Create a reference that points to this edge in central storage
    EdgeRef ref;
    ref.id = edgeId;

    // Update source node: add this edge reference to its outgoing map
    nodes[from].outgoing[typeId].push_back(ref);

    // Update destination node: add this edge reference to its incoming map
    nodes[to].incoming[typeId].push_back(ref);
    std::cout << "Added edge " << from << " -> " << to << " (type " << typeId << ")" << std::endl;
}

// Get all outgoing edge references of a specific type from a node
// Used as the first step of traversal: get references, then resolve them
std::vector<EdgeRef> Graph::getOutgoingEdges(NodeId nodeId, EdgeTypeId typeId) {

    // Safety check: node exists?
    if (nodes.find(nodeId) == nodes.end()) {
        return std::vector<EdgeRef>();
    }

    // Safety check: this node has edges of this type?
    if (nodes[nodeId].outgoing.find(typeId) == nodes[nodeId].outgoing.end()) {
        return std::vector<EdgeRef>();
    }

    // Return the list of references for this type
    return nodes[nodeId].outgoing[typeId];
}


// Resolve an edge reference to the actual edge data
// Uses integer indices into central storage, pure integer traversal
// This is the second step of traversal: take a reference and get the endpoints
Edge Graph::resolveEdge(EdgeTypeId typeId, EdgeRef ref) {
    // Look up the edge in central storage: edgesByType[type][id]
    // All operations here are integer based (no string comparison)
    return edgesByType[typeId][ref.id];
}

void Graph::printRegistry() {
       std::cout << "\n=== Node Type Registry ===" << std::endl;
       for (auto& pair : nodeTypeRegistry) {
           std::cout << pair.first << " -> " << pair.second << std::endl;
       }
       std::cout << "\n=== Edge Type Registry ===" << std::endl;
       for (auto& pair : edgeTypeRegistry) {
           std::cout << pair.first << " -> " << pair.second << std::endl;
       }
   }

void Graph::printNodes() {
    std::cout << "\n=== Nodes ===" << std::endl;
    for (auto& pair : nodes) {
        std::cout << "Node " << pair.second.id << " (type: " << pair.second.nodeType << ")" << std::endl;
    }
}

Node& Graph::getNode(NodeId id) {
    return nodes[id];
}