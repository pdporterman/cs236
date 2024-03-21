#pragma once

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


    void addRule(Rule rule){
        Rules.push_back(rule);
    }


    void addQuery(const Predicate& query){
        Queries.push_back(query);
    }


    void addDomain(const string& dom){
        domains.insert(dom);
    }


    vector<Predicate> getScheme(){
        return Schemes;
    }

    vector<Predicate> getFacts(){
        return Facts;
    }

    vector<Predicate> getQueries(){
        return Queries;
    }

    vector<Rule> getRules(){
        return Rules;
    }


    string ToString(){
        ostringstream str;
        str << "Success!" << endl;
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
        str << "Domain(" << domains.size() << "):" << endl;
        for (const auto& p : domains){
            str << "  " << p << endl;
        }
        return str.str();
    }

};
