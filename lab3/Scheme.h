#pragma once

#include <string>
#include <vector>

using namespace std;

class Scheme : public vector<string> {

public:

    explicit Scheme(vector<string> names) : vector<string>(names) { }

};
