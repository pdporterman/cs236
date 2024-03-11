#pragma once

#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {

public:

    explicit Tuple(vector<string> values) : vector<string>(std::move(values)) { }


    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
        if (scheme.empty()) {
            return out.str();
        }
        out << scheme.at(0) << "=" << tuple.at(0);
        for (int i = 1; i < static_cast<int>(scheme.size()); i++) {
            out << ", " << scheme.at(i) << "=" << tuple.at(i);
        }
        return out.str();
    }

};
