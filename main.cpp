#include "graph.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "meta_search_community_method.h"

using namespace std;

int main() {

    Graph g;

    // SAMPLE DATASET
    vector<pair<NodeId, string>> incomingNodes = {

        {1, "author"},
        {2, "paper"},
        {3, "paper"},
        {4, "author"}
    };


    for (auto& node : incomingNodes) {

        g.addNode(node.first, node.second);
    }

    // EDGES
    vector<tuple<NodeId, NodeId, string>> incomingEdges = {

        {1, 2, "authored"},
        {1, 3, "authored"},

        // Paper 2 cites Paper 3
        {2, 3, "cites"},

        // Author 1 and Author 4 are coauthors
        {1, 4, "coauthor"}
    };

    for (auto& edge : incomingEdges) {

        g.addEdge(
            get<0>(edge),
            get<1>(edge),
            get<2>(edge)
        );
    }


    // META-PATH SEARCH
    cout << "\n=== Meta-Path Search ===" << endl;

    cout << "Meta-path: AUTHOR -> PAPER -> AUTHOR"
         << endl;


    /*
        Starting from Author 1:
        The prototype searches for nodes matching
        the requested sequence.
    */

    vector<string> metaPath = {
        "paper",
        "author"
    };

    vector<NodeId> results =
        metaPathSearch(g, 1, metaPath);


    displayResults(g, results);

    // COMMUNITY SEARCH
    cout << "\n=== Community Search ===" << endl;

    cout << "Starting node: Author 1" << endl;

    cout << "Using meta-path: AUTHOR -> PAPER -> AUTHOR"
         << endl;


    communitySearch(
        g,
        1,
        metaPath
    );

    return 0;
}