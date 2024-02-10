#include <utility>
#include <ostream>




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
        ostringstream str;
        if (ID){
            str << item;
        }
        else{
            str << "\'" << item << "\'";
        }
        return str.str();
    }
};
