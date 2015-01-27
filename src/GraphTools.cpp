#include "GraphTools.h"

#include <set>
#include <vector>
#include <list>
#include <map>
#include <iostream>

using namespace std;

void GraphTools::ComputeInducedSubgraph(vector<vector<int>> &graph, set<int> const &vertices, vector<vector<int>> &subgraph, map<int,int> &remapping)
{
    subgraph.clear();
    remapping.clear();

    cout << "Forming induced subgraph on " << vertices.size() << " vertices." << endl;

    map<int,int> forwardMapping;

    int vertexIndex(0);
    auto mappedVertex = [&vertexIndex, &remapping, &forwardMapping](int const vertex)
    {
        if (forwardMapping.find(vertex) == forwardMapping.end()) {
            forwardMapping[vertex] = vertexIndex;
            remapping[vertexIndex] = vertex;
            vertexIndex++;
        }
        return forwardMapping[vertex];
    };

    for (int const vertex : vertices) {
        mappedVertex(vertex);
    }

    subgraph.resize(vertices.size());

    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (vertices.find(vertex) == vertices.end()) continue;

        vector<int> const &neighbors(graph[vertex]);
        int const newVertex = mappedVertex(vertex);
        cout << newVertex << " : ";
        for (int const neighbor : neighbors) {
            if (vertices.find(neighbor) == vertices.end()) continue;
            int const newNeighbor = mappedVertex(neighbor);
            subgraph[newVertex].push_back(newNeighbor);
////            subgraph[newNeighbor].push_back(newVertex);
            cout << newNeighbor << " ";
        }
        cout << endl;
    }
}

vector<int> GraphTools::OrderVerticesByDegree(vector<vector<int>> const &adjacencyList, bool const ascending)
{
    vector<int> vOrderedVertices(adjacencyList.size(), -1);

    size_t maxDegree(0);
    for (vector<int> const &neighbors : adjacencyList) {
        maxDegree = max(maxDegree, neighbors.size());
    }

    vector<list<int>> vlVerticesByDegree(maxDegree + 1, list<int>());

    for (size_t vertex = 0; vertex < adjacencyList.size(); ++vertex) {
////        std::cout << "maxDegree=" << maxDegree << ", degree=" << adjacencyList[vertex].size() << endl << flush;
        vlVerticesByDegree[adjacencyList[vertex].size()].push_back(vertex);
    }

    if (ascending) {
        size_t index(0);
        for (size_t degree = 0; degree <= maxDegree; ++degree) {
            for (int const vertex : vlVerticesByDegree[degree]) {
                vOrderedVertices[index++] = vertex;
            }
        }
    } else {
        size_t index(0);
        for (size_t degree = 0; degree <= maxDegree; ++degree) {
            for (int const vertex : vlVerticesByDegree[maxDegree - degree]) {
                vOrderedVertices[index++] = vertex;
            }
        }
    }

    return vOrderedVertices;
}

// NOT CURRENTLY USED.

////void GraphTools::RemoveVertices(vector<vector<int>> &adjacencyList, vector<int> const &vVertices)
////{
////    for (int const vertex : vVertices) {
////        if (vertex >= adjacencyList.size() || vertex < 0) {
////            continue;
////        }
////
////        vector<int> &neighbors(adjacencyList[vertex]);
////        for (int const neighbor : neighbors) {
////
////        }
////    }
////}
