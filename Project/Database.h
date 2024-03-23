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

    bool addTup(string name, Tuple tuple){
        int start = relations[name].getTups().size();
        relations[name].addTuple(tuple);
        int final = relations[name].getTups().size();
        if (final > start){
            return true;
        }
        else{
            return false;
        }
    }

    void addRelation(Relation r){
        relations[r.getName()] = r;
    }

    Relation getRelation(string name) {
        return relations[name];
    }
};

