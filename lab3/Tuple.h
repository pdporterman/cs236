#pragma once

#include <string>
#include <vector>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {

public:

    explicit Tuple(vector<string> values) : vector<string>(values) { }


    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
        // fix the code to print "name=value" pairs
        out << scheme.at(0) << "=";
        out << tuple.at(0) << ", ";
        out << scheme.at(1) << "=";;
        out << tuple.at(1) << ", ";
        out << scheme.at(2) << "=";;
        out << tuple.at(2) << ", ";
        return out.str();
    }

};
