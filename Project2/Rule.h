#include <utility>
#include <vector>
#include <set>
#include "Token.h"
#include "Parser.h"
#include <ostream>

using namespace std;

class Rule{
private:

    vector<Predicate> rule;

public:

    Rule(){
        rule = {};
    }

    void addPred(const Predicate& pred){
        rule.push_back(pred);
    }

    string toString(){
        ostringstream str;
        auto start = rule[0];
        str << start.rulesToString() << " :- ";
        rule.erase(rule.begin());
        while (!rule.empty()){
            str << rule[0].rulesToString();
            rule.erase(rule.begin());
            if (rule.empty()){
                str << " ." << endl;
            } else{
                str <<" ,";
            }
        }
        return str.str();
    }

};
