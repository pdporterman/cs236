#pragma once

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <sstream>
#include "Graph.h"
#include "Node.h"
#include "Tuple.h"
#include "Scheme.h"
#include "Relation.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Predicate.h"

using namespace std;

class Interperter{
    DataLog log;
    Database data;
    int rulePasses = 0;

private:

public:
    explicit Interperter(DataLog log):log(std::move(log)){
    getRelations();
    getTups();
    cout << "Rule Evaluation" << endl;
    getRules();
    cout << "\nSchemes populated after " << rulePasses <<" passes through the Rules." << endl;
    cout << "\nQuery Evaluation" << endl;
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

    void processRule(string name, vector<Parameter> query, Relation ruleTable){
        Relation temp = std::move(ruleTable);
        map<string, int> seen;
        vector<string> colsNames;
        for (int i = 0; i < static_cast<int>(query.size()); i++){
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
                }
            }
        }
        vector<int> colsIndex;
        for (auto col : colsNames){
            for (int i = 0; i < temp.getScheme().size(); i++){
                if (temp.getScheme()[i] == col){
                    colsIndex.push_back(i);
                }
            }
        }
        Scheme scheme(colsNames);
        temp.rename(scheme);
        temp = temp.project(colsIndex, scheme);          // project seen Ids
        int startSize = data.getRelation(name).getTups().size();
        Relation printer;
        for (const auto& tup : temp.getTups()){
            if (data.addTup(name, tup)){
                printer.addTuple(tup);
            }
        }
        vector<string> othernames; // start code to get matching cal names
        for (int i = 0; i < colsNames.size(); i++){
            othernames.push_back(data.getRelation(name).getScheme()[i]);
        }
        if (othernames.size() > 0){
            Scheme oldcols(othernames);
            printer.rename(oldcols);
        }
        if (data.getRelation(name).getTups().size() > startSize){
            cout << printer.toString();
        }
    }

    Relation makeRelation(vector<Parameter> query, string name) {
        Relation temp = data.getRelation(name);
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
        return temp;
    }

    Relation makeTable(Rule rule) {
        vector<Relation> parts;
        for (int i = 1; i < rule.getVec().size()-1; i++){
            vector<Parameter> lst = rule.getPars(i);
            string name = lst.begin()->toString();
            lst.erase(lst.begin());
            Relation result = makeRelation(lst, name);
            parts.push_back(result);
        }
        Relation result = parts[0];
        for (int i = 1; i < parts.size(); i++){
            result = result.joinMethod(parts[i]);
        }
        return result;
    }

    void getRules(){
        vector<Rule> rules = log.getRules();
        vector<int> startSizes;
        vector<int> finalSizes;
        for (Rule rule : rules){
            Rule copy = rule;
            cout << copy.toString() << endl;
            vector<Parameter> namePars = rule.getNamePars(); // name at end to eval
            Relation bigTable = makeTable(rule); //take care of combining the right side


            string name = namePars.begin()->toString();  // get relation
            namePars.erase(namePars.begin());
            Relation startRelation = data.getRelation(name);
            startSizes.push_back(startRelation.getTups().size());
            processRule(name, namePars, bigTable);
            Relation finishRelation = data.getRelation(name);
            finalSizes.push_back(finishRelation.getTups().size());
        }
        rulePasses += 1;
        bool runAgain = false;
        for (int i = 0; i < startSizes.size(); i++){
            if (startSizes[i] != finalSizes[i]){
                runAgain = true;
            }
        }
        if (runAgain){
            getRules();
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

    static Graph makeGraph(const vector<Rule>& rules) {
        stringstream out;
        Graph graph(rules.size());
        int c = 0;
        for (auto rule : rules){
            vector<pair<int,int>> depend;
            vector<string> names;
            vector<Parameter> pred = rule.getVec()[0].getpars();
            out << "from rule R" << c << ": " << pred[0].toString() << "() :- ";
            for (int i = 1; i < pred.size(); i++){
                out << pred[i].toString() << "()";
                if (i  == pred.size() - 1){
                    out << endl;
                }
                else{
                    out << ",";
                }
            }
            for (int i = 1; i < pred.size(); i++){
                string name = pred[i].toString();
                names.push_back(name);
                out << "from body predicate: "<< name << "()" << endl;
                int n = 0;
                for (auto rule : rules) {
                    vector<Parameter> pred = rule.getVec()[0].getpars();
                    string other = pred[0].toString();
                    out << "to rule R" << n << ": " << other << "() :- ";
                    auto it = find(names.begin(), names.end(), other);

                    for (int i = 1; i < pred.size(); i++) {
                        out << pred[i].toString() << "()";
                        if (i == pred.size() - 1) {
                            out << endl;
                        } else {
                            out << ",";
                        }
                    }
                    if (it != names.end()) {
                        out << "dependency found: (R" << c << ",R" << n << ")" << endl;
                        graph.addEdge(c,n);
                    }
                    n += 1;
                }
            }
            c += 1;
        };
        cout << out.str();
        return graph;

    }


};

// grab relation start of rule as name
// then for pred do eval on each relation and then join them
// then use select project on resulting table then use that relaiton for name
