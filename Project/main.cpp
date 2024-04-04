#include <iostream>
#include "Scanner.h"
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
#include "Node.h"
#include "Graph.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;
    ifstream in;
    in.open(argv[1]);
    stringstream ss;
    ss << in.rdbuf();
    string input = ss.str();
    Scanner s = Scanner(input);
    vector<Token> Tokens = s.scanTokens();
    Parser p = Parser(Tokens);
    p.startParse();
    Interperter interpreter(p.getDL());

//    // predicate names for fake rules
//    // first is name for head predicate
//    // second is names for body predicates
//    pair<string,vector<string>> ruleNames[] = {
//            { "A", { "B", "C" } },
//            { "B", { "A", "D" } },
//            { "B", { "B" } },
//            { "E", { "F", "G" } },
//            { "E", { "E", "F" } },
//    };
//
//    vector<Rule> rules;
//
//    for (auto& rulePair : ruleNames) {
//        string headName = rulePair.first;
//        Parameter name = Parameter(headName,true);
//        Predicate pred = Predicate();
//        pred.addPredicate(name);
//        vector<string> bodyNames = rulePair.second;
//        for (auto s : bodyNames){
//            Parameter temp = Parameter(s,false);
//            pred.addPredicate(temp);
//        }
//        Rule rule = Rule();
//        rule.addPred(pred);
//        rules.push_back(rule);
//    }
//    Graph graph = Interperter::makeGraph(rules);
//    cout << graph.toString();
//

};