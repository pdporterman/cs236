#pragma once

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <sstream>
#include "Tuple.h"
#include "Scheme.h"

using namespace std;




class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(){}

    Relation(string  name, Scheme  scheme): name(name), scheme(scheme){ }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    string toString() const {
        stringstream out;
        for (const auto& tuple : tuples)
        out << tuple.toString(scheme) << endl;
        return out.str();
    }

    int findIndex(string col){
        for (size_t i = 0; i < scheme.size(); ++i){
            if (scheme[i] == col) {
                return i; // Return the index if the string is found
            }
        }
        return -1;
    }

    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (const auto& tuple : tuples){
            if (tuple.at(index) == value){
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation project(vector<string> cols){
        Scheme newCols(cols);
        Relation result(name,newCols);
        for (string col : cols){
            int index = findIndex(col);
            if (index != -1){
                for (auto tuple : tuples){
                    Tuple single({tuple.at(index)});
                    result.addTuple(single);
                }
            }
        }
        return result;
    }

    void rename(string newName){
        this->name = newName;
    }

    string getName(){
        return name;
    };

};
