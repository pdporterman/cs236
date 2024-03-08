#pragma once

#include <utility>
#include <ostream>
#include <string>
#include <sstream>

using namespace std;


class Parameter {
private:
    bool ID;
    string item;
public:
    Parameter(string val, bool id){
        item = std::move(val);
        ID = id;
    }

    bool isID() const{
        return ID;
    }


    string getVal(){
        return item;
    }

    string toString(){
        ostringstream s;
        s << item;
        return s.str();
    }
};
