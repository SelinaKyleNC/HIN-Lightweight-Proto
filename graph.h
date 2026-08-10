#ifndef GRAPH_H
#define GRAPH_H

#include "types.h"

// Graph: Owns all data storage and handles dynamic type registration
// The graph is the source of truth for:
// - What EdgeTypeId and NodeTypeId mean globally
// - Central edge storage (separate vectors per type)
// - All nodes and their connections
class Graph {
public:
    Graph();

    // Add a node with a type name (type registers dynamically)
    // String boundary: this is where nodeType becomes NodeTypeId
    void addNode(NodeId id, std::string nodeTypeName);

    // Register or retrieve a node type ID
    // If node type already exists, returns existing ID
    // If new, assigns next available ID and stores it
    NodeTypeId getOrRegisterNodeType(std::string typeName);

    // Register or retrieve an edge type ID
    // If edge type already exists, returns existing ID
    // If new, assigns next available ID, creates central storage vector, stores it
    EdgeTypeId getOrRegisterEdgeType(std::string typeName);

    // Add an edge between two nodes
    // Edge type registers dynamically if it's new
    // Updates both source node's outgoing and destination node's incoming references
    void addEdge(NodeId from, NodeId to, std::string edgeTypeName);

    // Get all outgoing edge references of a specific type from a node
    // Returns empty vector if node or type doesn't exist
    std::vector<EdgeRef> getOutgoingEdges(NodeId nodeId, EdgeTypeId typeId);

    // Convert an edge reference back into the actual edge data
    // Used during traversal: get reference from node, resolve to get endpoints
    Edge resolveEdge(EdgeTypeId typeId, EdgeRef ref);

    // Get a reference to a node (for direct access to its edges)
    Node& getNode(NodeId id);

    // Debugging/Validation
    void printRegistry();
    void printNodes();

private:

    // Central edge storage: one vector per edge type
    // edgesByType[0] = all "authored" edges
    // edgesByType[1] = all "cites" edges
    // etc.
    // Edges are never mixed - type 0 always means the same thing everywhere
    std::unordered_map<EdgeTypeId, std::vector<Edge>> edgesByType;

    // All nodes in the graph
    // Key: NodeId, Value: Node (which has its own edge references)
    std::unordered_map<NodeId, Node> nodes;

    // String-to-ID mapping for edge types (registration boundary)
    // Maps: "authored" -> 0, "cites" -> 1, etc.
    // This is the ONLY place strings are used for edge types
    std::unordered_map<std::string, EdgeTypeId> edgeTypeRegistry;

    // String-to-ID mapping for node types (registration boundary)
    // Maps: "author" -> 0, "paper" -> 1, etc.
    // This is the ONLY place strings are used for node types
    std::unordered_map<std::string, NodeTypeId> nodeTypeRegistry;

    // Counters for auto-assigning new IDs when types are first encountered
    uint16_t nextNodeTypeId = 0;
    uint16_t nextEdgeTypeId = 0;

};

#endif