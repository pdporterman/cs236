#pragma once

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include "Tuple.h"
#include "Scheme.h"
#include "Relation.h"
#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

class Database{
    map<string, Relation> relations;

private:

public:
    Database()= default;

    void addTup(string name, Tuple tuple){
        relations[name].addTuple(tuple);
    }

    void addRelation(Relation r){
        //relations.insert(pair<string, Relation>(r.getName(), r));
        relations[r.getName()] = r;
    }

    Relation getRelation(string name) {
        auto it = relations.find(name);
        if (it != relations.end()){
            return relations[name];
        }

    }
};

