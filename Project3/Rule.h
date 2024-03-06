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
        int r = static_cast<int>(rule.size());
        str << rule[0].rulesToString() << " :- ";
        for (int i = 1; i < r - 1; i++) {
            if (i > 1) {
                str << ",";
            }
            str << rule[i].rulesToString(); // this is the problem
        }
        str << ".";
        return str.str();
    }

};
