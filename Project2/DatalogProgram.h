#include <vector>
#include <set>
#include "Parameter.h"
#include <string>
#include "Predicate.h"
#include "Rule.h"
#include <ostream>

class DataLog {
private:
    vector<Predicate> Schemes{};
    vector<Predicate> Facts{};
    vector<Predicate> Queries{};
    vector<Rule> Rules{};
    set<string> domains;

public:
    DataLog(){
        Schemes = {};
        Facts = {};
        Queries = {};
        Rules = {};
    }

    void addScheme(const Predicate& scheme){
        Schemes.push_back(scheme);
    }


    void addFact(const Predicate& fact){
        Facts.push_back(fact);
    }


    void addRule(const Rule& rule){
        Rules.push_back(rule);
    }


    void addQuery(const Predicate& rule){
        Queries.push_back(rule);
    }


    void addDomain(const string& dom){
        domains.insert(dom);
    }


    string ToString(){
        ostringstream str;
        str << "Schemes(" << Schemes.size() << "):" << endl;
        for (auto p : Schemes){
            str << "  " << p.schemesToString() << endl;
        }
        str << "Facts(" << Facts.size() << "):" << endl;
        for (auto p : Facts){
            str << "  " << p.factsToString() << endl;
        }
        str << "Rules(" << Rules.size() << "):" << endl;
        for (auto p : Rules){
            str << "  " << p.toString() << endl;
        }
        str << "Queries(" << Queries.size() << "):" << endl;
        for (auto p : Queries){
            str << "  " << p.queriesToString() << endl;
        }
        return str.str();
    }

};
