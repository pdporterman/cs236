#pragma once

#include <utility>
#include <vector>
#include <set>
#include "Token.h"
#include "Parser.h"
#include <ostream>

using namespace std;

// Schemes, Facts, Query

class Predicate{
private:
    string name;
    vector<Parameter> predicate;
public:
    explicit Predicate(){
        predicate = {};
    }

    void addPredicate(const Parameter& par){
        predicate.push_back(par);
    }

    vector<Parameter> getpars(){
        return predicate;
    }


    string schemesToString(){
        ostringstream str;
        str << predicate.begin()->toString() << "(";
        predicate.erase(predicate.begin());
        while (!predicate.empty()){
            str << predicate.begin()->toString();
            predicate.erase(predicate.begin());
            if (predicate.empty()){
                str << ")";
            } else{
                str <<",";
            }
        }
        return str.str();
    }

    string factsToString(){
        ostringstream str;
        str << predicate.begin()->toString() << "(";
        predicate.erase(predicate.begin());
        while (!predicate.empty()){
            str << predicate.begin()->toString();
            predicate.erase(predicate.begin());
            if (predicate.empty()){
                str << ").";
            } else{
                str <<",";
            }
        }
        return str.str();
    }

    string rulesToString(){
        ostringstream str;
        str << predicate.begin()->toString() << "(";
        predicate.erase(predicate.begin());
        while (!predicate.empty()){
            str << predicate.begin()->toString();
            predicate.erase(predicate.begin());
            if (predicate.empty()){
                str << ")";
            } else{
                str <<",";
            }
        }
        return str.str();
    }

    string queriesToString(){
        ostringstream str;
        str << predicate.begin()->toString() << "(";
        predicate.erase(predicate.begin());
        while (!predicate.empty()){
            str << predicate.begin()->toString();
            predicate.erase(predicate.begin());
            if (predicate.empty()){
                str << ")?";
            } else{
                str <<",";
            }
        }
        return str.str();
    }

    string getname(){
        return predicate[0].toString();
    }


};



