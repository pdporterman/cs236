#pragma once

#include <string>
#include <utility>
#include <vector>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {

public:

    explicit Tuple(vector<string> values) : vector<string>(std::move(values)) { }


    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
        // fix the code to print "name=value" pairs
        for (int i = 0; i < tuple.size(); i++) {
            out << scheme.at(i) << "=";
            out << tuple.at(i) << ", ";
        }
        return out.str();
    }

};
