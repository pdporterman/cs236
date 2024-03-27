#pragma once

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

class Node {

private:

    set<int> adjacentNodeIDs;

public:

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    string toString(){
        std::stringstream out;
        bool first = true;
        for (auto ID : adjacentNodeIDs) {
            if (!first) {
                out << ",";
            }
            out << "R" << ID;
            first = false;
        }
        out << std::endl;
        return out.str();
    }

};
