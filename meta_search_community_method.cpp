#include "meta_search_community_method.h"
#include <iostream>

using namespace std;

// STAGE 1: META-PATH TRAVERSAL
vector<NodeId> metaPathSearch(
    Graph& g,
    NodeId startNode,
    vector<string> metaPath
) {
    vector<NodeId> currentNodes;
    currentNodes.push_back(startNode);

    for (int step = 0; step < metaPath.size(); step++) {

        vector<NodeId> nextNodes;

        for (NodeId currentID : currentNodes) {

            Node& currentNode = g.getNode(currentID);

            for (auto& edgeTypePair : currentNode.outgoing) {

                EdgeTypeId typeId = edgeTypePair.first;
                vector<EdgeRef>& refs = edgeTypePair.second;

                for (auto& ref : refs) {

                    Edge edge = g.resolveEdge(typeId, ref);

                    Node& destinationNode = g.getNode(edge.to);

                    if (to_string(destinationNode.nodeType) == metaPath[step]) {
                        nextNodes.push_back(edge.to);
                    }
                }
            }
        }

        currentNodes = nextNodes;
    }

    return currentNodes;
}

// STAGE 2: DISPLAY MATCHING RESULTS
void displayResults(
    Graph& g,
    vector<NodeId> results
) {
    cout << "Matching nodes: { ";

    for (NodeId id : results) {
        cout << id << " ";
    }

    cout << "}" << endl;
}

// STAGE 3: SIMPLE COMMUNITY SEARCH
void communitySearch(
    Graph& g,
    NodeId startNode,
    vector<string> metaPath
) {
    vector<NodeId> community;

    community.push_back(startNode);

    vector<NodeId> results =
        metaPathSearch(g, startNode, metaPath);

    for (NodeId id : results) {

        bool alreadyExists = false;

        for (NodeId existing : community) {

            if (existing == id) {
                alreadyExists = true;
            }
        }

        if (!alreadyExists) {
            community.push_back(id);
        }
    }

    cout << "Community: { ";

    for (NodeId id : community) {
        cout << id << " ";
    }

    cout << "}" << endl;
}