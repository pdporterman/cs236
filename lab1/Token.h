#pragma once

#include <sstream>

using namespace std;

enum TokenType {
    COMMA
};

class Token {
    private:
        TokenType type;
        string value;
        int line;

    public:
        Token(TokenType type, string value, int line) : type(type), value(value), line(line) { }

        string typeName(TokenType type) const {
            if (type == 0){
                return "COMMA";
            }
            return "error";
        }

        string toString() const {
            stringstream out;
            out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
            return out.str();
        }
};


