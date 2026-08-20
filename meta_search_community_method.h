#ifndef META_SEARCH_COMMUNITY_METHOD_H
#define META_SEARCH_COMMUNITY_METHOD_H

#include "graph.h"
#include <vector>
#include <string>

std::vector<NodeId> metaPathSearch(
    Graph& g,
    NodeId startNode,
    std::vector<std::string> metaPath
);

void displayResults(
    Graph& g,
    std::vector<NodeId> results
);

void communitySearch(
    Graph& g,
    NodeId startNode,
    std::vector<std::string> metaPath
);

#endif

