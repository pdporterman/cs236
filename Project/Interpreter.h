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
    explicit Interperter(DataLog log):log(std::move(log)){
    getRelations();
    getTups();
    cout << "Query Evaluation" << endl;
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

    void getRules(){
        cout << "Rule Evaluation" << endl;
        vector<Rule> rules = log.getRules();
        for (auto pred : rules){

        }
    }

    static void evalQueries(vector<Parameter> query, Relation relation, Predicate question){
        // select
        Relation temp = std::move(relation);
        map<string, int> seen;
        vector<string> colsNames;
        vector<int> colsIndex;
        for (int i=0; i < static_cast<int>(query.size()); i++){
            if (!query[i].isID()){                                                         //select based on value
                temp = temp.select(i, query[i].getVal());
            }
            else{
                auto it = seen.find(query[i].getVal());
                if (it != seen.end()){                                                      // check seen for match
                    temp = temp.selectMatch(seen[query[i].getVal()], i);
                }
                else{                                                                      // save ID in seen
                    seen[query[i].getVal()] = i;
                    colsNames.push_back(query[i].getVal());
                    colsIndex.push_back(i);

                }
            }
        }
        Scheme scheme(colsNames);
        temp.rename(scheme);      // rename
        temp = temp.project(colsIndex, scheme);          // project seen Ids
        stringstream out;              //print
        if (!temp.getTups().empty()){
            out << question.schemesToString() <<"? Yes(" << temp.getTups().size() << ")" << endl;
            out << temp.toString();
        }
        else{
            out << question.schemesToString() <<"? No" << endl;
        }
        cout <<  out.str();
    }

    void getQueries(){
        vector<Predicate> queries = log.getQueries();
        for (auto pred : queries){
            vector<Parameter> lst = pred.getpars();
            string name = lst.begin()->toString();
            lst.erase(lst.begin());
            Relation relation = data.getRelation(name);
            evalQueries(lst, relation, pred);
        }
    }


};
