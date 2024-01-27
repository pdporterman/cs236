#pragma once

#include <string>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner {
    private:
        string input;
        int line = 0;

    public:
        Scanner(const string& input) : input(input) { }


        Token scanToken() {
            while (!input.empty() && isspace(input.at(0))){
                input = input.substr(1);
            }
            for(auto c : input){
                if (c == '\n'){
                    line++;
                }
                if (c == ','){
                TokenType type = COMMA;
                string value = ",";
                return Token(type, value, line);
                }
            }
        }
};