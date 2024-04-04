#pragma once

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
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

    getRules(0);
    //cout << "\nSchemes populated after " << rulePasses <<" passes through the Rules." << endl;
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

    void depthFirst(Graph graph, int i, vector<int>& visited, vector<int>& post) {
        Node node = graph.at(i);
        for (auto item : node.getAdjacentNodeIDs()) {
            auto i = find(visited.begin(), visited.end(), item);
            if (i == visited.end()) {
                visited.push_back(item);
                depthFirst(graph, item, visited, post);
                post.push_back(item);
            }
        }
    } // check with TAs

    vector<int> postOrder(Graph graph) {
        vector<int> visited;
        vector<int> post;
        for (auto key : graph.getNodes()){
            auto it = find(visited.begin(), visited.end(), key.first);

            if (it == visited.end()){
                visited.push_back(key.first);
                for (auto item : key.second.getAdjacentNodeIDs()) {
                    auto i = find(visited.begin(), visited.end(), item);
                    if (i == visited.end()) {
                        visited.push_back(item);
                        depthFirst(graph, item, visited, post);
                    }
                    post.push_back(key.first);
                }
            }
        }
        return post;
    }  // check with TAs

    vector<vector<int>> getSCCS(vector<int> order, Graph graph) {
        vector<vector<int>> components;
        vector<int> visited;
        for (auto index : order){
            vector<int> component;
            auto it = find(visited.begin(), visited.end(), index);

            if (it == visited.end()){
                visited.push_back(index);
                for (auto item : graph.at(index).getAdjacentNodeIDs()) {
                    auto i = find(visited.begin(), visited.end(), item);
                    if (i == visited.end()) {
                        visited.push_back(item);
                        depthFirst(graph, item, visited, component);
                    }
                    components.push_back(component);
                }
            }
        }
        return components;
    } // check with TAs

    void getRules(int current){
        vector<Rule> rules = log.getRules();
        pair<Graph, Graph> graphs = makeGraph(rules);
        Graph graph = graphs.second;
        Graph reverse = graphs.first;
        cout << "Rule Evaluation" << endl;
        vector<int> order = postOrder(reverse);
        vector<vector<int>> sccs = getSCCS(order, graph);
        vector<int> startSizes;
        vector<int> finalSizes;
        cout << order.size() << endl << sccs.size() << endl;
        for (auto component : sccs) { // added another loop for each component
            cout << "SCC: R" << component[0] << endl;
            int componentPasses = 0; // count loops through component
            for (auto index: component) { // loop through all indexes in component
                Rule copy = rules[index]; // get rule at component index
                cout << copy.toString() << endl;
                vector<Parameter> namePars = rules[index].getNamePars(); // name at end to eval
                Relation bigTable = makeTable(rules[index]); //take care of combining the right side
                string name = namePars.begin()->toString();  // get relation
                namePars.erase(namePars.begin());
                Relation startRelation = data.getRelation(name);
                startSizes.push_back(startRelation.getTups().size());
                processRule(name, namePars, bigTable);
                Relation finishRelation = data.getRelation(name);
                finalSizes.push_back(finishRelation.getTups().size());
            }
            componentPasses += 1;
            bool runAgain = false;
            for (int i = 0; i < startSizes.size(); i++) {
                if (startSizes[i] != finalSizes[i]) {
                    runAgain = true;
                }
            }
            if (runAgain) {
                getRules(current);
            }
            else{
                current += 1;
            }
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

    static pair<Graph,Graph> makeGraph(const vector<Rule>& rules) {
        stringstream out;
        Graph graph(rules.size());
        Graph reverse(rules.size());
        int c = 0;
        for (auto rule : rules){
            vector<pair<int,int>> depend;
            vector<string> names;
            vector<Predicate> pred = rule.getVec();
            for (int i = 1; i < pred.size()-1; i++){
                string name = pred[i].getname();
                names.push_back(name);
                int n = 0;
                for (auto rule : rules) {
                    vector<Parameter> parm = rule.getVec()[0].getpars();
                    string other = parm[0].toString();
                    auto it = find(names.begin(), names.end(), other);

                    if (it != names.end()) {
                        graph.addEdge(c,n);
                        reverse.addEdge(n, c);
                    }
                    n += 1;
                }
            }
            c += 1;
        };
        cout << "Dependency Graph" << endl;
        cout << graph.toString() << endl;
//        cout << reverse.toString() << endl;
        return make_pair(reverse, graph);

    } //prints dependency graph and returns reverse edge graph and dependency graph


};
