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

    //check with TAs


    Relation project(vector<int> cols, Scheme newScheme){
        //Scheme newCols(cols);
        Relation result(name, newScheme);
        for (auto tuple : tuples){ // tupels first
            Tuple tup({});
                for (auto col : cols){ // cols
                    tup.push_back(tuple.at(col));  // tup.append(val)
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

    Scheme getScheme(){
        return scheme;
    }

    static bool common(Scheme left, const Scheme& right){
        for (const auto & val : right) {
            auto check = find(left.begin(), left.end(), val);
            if (check != left.end()){
                return true;
            }
        }
        return false;
    }

    Relation same(Relation right) {
        Relation result = *this;
        set<Tuple> tups = right.getTups();
        for (const auto& tup : tups){
            result.addTuple(tup);
        }
        return result;
    }

    Relation joinMethod(Relation right){
        Relation& left = *this;
        if (left.scheme == right.scheme){
            return left.same(right);
        }
        else if (common(left.scheme, right.scheme)){
            return left.join(right);
        }
        else {
            return left.unionize(right);
        }

    }

    Relation unionize(Relation right){
        const Relation& left = *this;
        Scheme joint = joinSchemes(left.scheme, right.scheme);
        Relation result;
        result.rename(joint);
        for (const Tuple& leftTuple: left.tuples) {
            for (const Tuple& rightTuple: right.tuples) {
                result.addTuple(joinTuples(left.scheme, right.scheme, leftTuple, rightTuple));
            }
        }
        return result;
    }

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
                    result.addTuple(joinTuples(left.scheme, right.scheme, leftTuple, rightTuple));
                }
            }
        }
        result.rename(joinSchemes(left.scheme, right.scheme));
        return result;
    }

    // check with TAs

    static Tuple joinTuples(Scheme leftScheme, Scheme rightScheme, Tuple left, const Tuple& right){ // add if to check schemes
        Tuple result = left;
        for (int i = 0; i < right.size(); i++){
            auto name = find(leftScheme.begin(), leftScheme.end(), rightScheme[i]);
            auto val = find(left.begin(), left.end(), right[i]);
            if (name == leftScheme.end()) {
                result.push_back(right[i]);
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


// make union function for if no cols are the same
// make join for same schemes
