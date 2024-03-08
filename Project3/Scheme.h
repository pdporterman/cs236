#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

class Scheme : public vector<string> {

public:

    Scheme(){}

    explicit Scheme(vector<string> names) : vector<string>(std::move(names)) { }

};
