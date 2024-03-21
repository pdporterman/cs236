#pragma once

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
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
        for (const auto &tuple: tuples) {
            string s = tuple.toString(scheme);
            if (s != ""){
                out << "  " << s << endl;
            }
        }
        return out.str();
    }

    set<Tuple> getTups(){
        return tuples;
    }

//    int findIndex(string col){
//        for (int i = 0; i < static_cast<int>(scheme.size()); ++i){
//            if (scheme[i] == col) {
//                return i; // Return the index if the string is found
//            }
//        }
//        return -1;
//    }

    Relation selectMatch(int index1, int index2) const {
        Relation result(name, scheme);
        for (const auto& tuple : tuples){
            if (tuple.at(index1) == tuple.at(index2)){
                result.addTuple(tuple);
            }
        }
        return result;
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

    Relation project(vector<int> cols, Scheme newScheme){
        //Scheme newCols(cols);
        Relation result(name, newScheme);
        for (auto tuple : tuples){ // tupels first
            Tuple tup({});
                for (auto col : cols){ // cols
                    //int index = findIndex(col);
                    //if (index != -1){
                    tup.push_back(tuple.at(col));  // tup.append(val)
                //}
            }
            result.addTuple(tup);
        }
        return result;
    }


    void rename(Scheme newScheme){ //pass in scheme
        this->scheme = newScheme;
    }

    string getName(){
        return name;
    };

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string &leftName = leftScheme.at(leftIndex);
            const string &leftValue = leftTuple.at(leftIndex);
            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string &rightName = rightScheme.at(rightIndex);
                const string &rightValue = rightTuple.at(rightIndex);
                if (rightName == leftName && rightValue != leftValue){
                    return false;
                }
        }
    }
        return true;
    }

    // check with TAs

    Relation join(Relation& right) {
        const Relation& left = *this;
        Relation result;
        for (const Tuple& leftTuple: left.tuples) {
            for (const Tuple& rightTuple: right.tuples) {
                if (joinable(left.scheme, right.scheme, leftTuple, rightTuple)){
                    result.addTuple(joinTuples(leftTuple, rightTuple));
                }
            }
        }
        result.rename(joinSchemes(left.scheme, right.scheme));
        return result;
    }

    // check with TAs

    static Tuple joinTuples(Tuple left, const Tuple& right){ // add if to check schemes
        Tuple result = left;
        for (const auto& value : right){
            auto it = find(left.begin(), left.end(), value);
            if (it == left.end()) {
                result.push_back(value);
            }
        }
        return result;
    }

    // check with TAs

    static Scheme joinSchemes(Scheme left, const Scheme& right){ 
        Scheme result = left;
        for (const auto& col : right){
            auto it = find(left.begin(), left.end(), col);
            if (it == left.end()) {
                result.push_back(col);
            }
        }
        return result;
    }


};
