#pragma once

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <sstream>
#include "Tuple.h"
#include "Scheme.h"
#include "Relation.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Predicate.h"

using namespace std;

class Interperter{
    DataLog log;
    Database data;

private:

public:
    Interperter(DataLog log):log(log){
    getRelations();
    getTups();
    getQueries();
    }

    void getRelations(){
    vector<Predicate> schemes = log.getScheme();
    for (auto pred : schemes){
        vector<Parameter> lst = pred.getpars();
        string name = lst.begin()->toString();
        lst.erase(lst.begin());
        vector<string> cols;
        for (auto c : lst){
            cols.push_back(c.toString());
        }
        Scheme scheme(cols);
        Relation relation(name, scheme);
        data.addRelation(relation);
    }
    }


    void getTups(){
        vector<Predicate> facts = log.getFacts();
        for (auto pred : facts){
            vector<Parameter> lst = pred.getpars();
            string name = lst.begin()->toString();
            lst.erase(lst.begin());
            vector<string> cols;
            for (auto c : lst){
                cols.push_back(c.toString());
            }
            Tuple tuple(cols);
            data.addTup(name, tuple);
        }
    }

    void evalQueries(Relation query, Relation relation){

    }

    void getQueries(){
        vector<Predicate> queries = log.getQueries();
        for (auto pred : queries){
            vector<Parameter> lst = pred.getpars();
            string name = lst.begin()->toString();
            lst.erase(lst.begin());
            vector<string> cols;
            for (auto c : lst){
                cols.push_back(c.toString());
            }
            Scheme scheme(cols);
            Relation relation(name, scheme);
            Relation savedRelation = data.getRelation(name);

        }
    }


};
