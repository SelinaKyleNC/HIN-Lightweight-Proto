#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>


// Type aliases for clarity and consistency. 
// These are used throughout the system for traversal and storage
using NodeId = uint32_t;                //unique identifier for each node
using NodeTypeId = uint16_t;            //unique identifier for each node type
using EdgeTypeId = uint16_t;            //unique identifier for each edge type
using EdgeId = uint32_t;                //index position of an edge within its type central vector



// Edge: The actual connection between two nodes
// Stored centrally in Graph::edgesByType, grouped by type
// Only stores endpoints, type is implicit from which vector it lives in
struct Edge {
    NodeId from;
    NodeId to;
};


// EdgeRef: A lightweight reference to an edge
// Nodes store these, NOT full Edge objects
// Points into the central edge storage via an index (EdgeId)
struct EdgeRef {
    EdgeId id;
};

// Node: Generic node that works for any type
// Does NOT hardcode edge types, dynamically stores edges by type
// The node type  is stored as an integer ID, not a string
struct Node {
    NodeId id;
    NodeTypeId nodeType;

    // Outgoing edges grouped by type
    // Key: global EdgeTypeId (same meaning everywhere in graph)
    // Value: list of EdgeRefs pointing to edges in central storage
    std::unordered_map<EdgeTypeId, std::vector<EdgeRef>> outgoing;

    // Incoming edges grouped by type (same structure as outgoing)
    std::unordered_map<EdgeTypeId, std::vector<EdgeRef>> incoming;
};


#endif