#include <utility>
#include <vector>
#include <set>
#include "Token.h"
#include "Parser.h"
#include <ostream>

using namespace std;

class Rule{
private:

    vector<Predicate> rule{};

public:

    Rule(){
        rule = {};
    }

    void addPred(const Predicate& pred){
        rule.push_back(pred);
    }

    vector<Predicate> getVec(){
        return rule;
    }

    string toString(){
        ostringstream str;
        str << rule.begin()->rulesToString() << " :- ";
        rule.erase(rule.begin());
        while (!rule.empty()){
            str << rule.begin()->rulesToString(); // this is the problem
            rule.erase(rule.begin());
            if (rule.empty()){
                str << " .";
            } else{
                str <<" ,";
            }
        }
        return str.str();
    }

};
