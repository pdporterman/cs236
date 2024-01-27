#pragma once

#include <string>
#include <cctype>
#include "Token.h"
#include <fstream>
#include <utility>
#include <vector>


using namespace std;

class Scanner {
    private:
        string input;
        int line = 1;
        int j{};
        vector<Token> Tokens;
        size_t k{};

    public:
        explicit Scanner(string  input) : input(std::move(input)) { }
        string value;


        vector<Token> scanTokens() {
            for (int i = 0; i < input.length(); i++) {
                auto c = input[i];
                switch (c) {
                    case '\t':
                        break;
                    case ' ':
                        break;
                    case '\n':
                        line++;
                        break;
                    case '\r':
                        break;
                    case ',':
                        Tokens.emplace_back(COMMA, string(1,c), line);
                        break;
                    case '.':
                        Tokens.emplace_back(PERIOD, string(1,c), line);
                        break;
                    case '?':
                        Tokens.emplace_back(Q_MARK, string(1,c), line);
                        break;
                    case '(':
                        Tokens.emplace_back(LEFT_PAREN, string(1,c), line);
                        break;
                    case ')':
                        Tokens.emplace_back(RIGHT_PAREN, string(1,c), line);
                        break;
                    case '*':
                        Tokens.emplace_back(MULTIPLY, string(1,c), line);
                        break;
                    case '+':
                        Tokens.emplace_back(ADD, string(1,c), line);
                        break;
                    case ':':
                        if (input.substr(i,2) == ":-"){
                            Tokens.emplace_back(COLON_DASH, ":-", line);
                            i++;
                        }
                        else{
                            Tokens.emplace_back(COLON, string(1,c), line);
                        }
                        break;
                    case '#':
                        value = input[i];
                        j = 0;
                        // block comment
                        if (input.substr(i,2) == "#|"){
                            i++;
                            while(i < input.length() && input[i] != '#') {
                                if (input[i] == '\n') {
                                    j++;
                                    i++;
                                }
                                else if (input[i] == '\r') {
                                    i++;
                                }
                                else{
                                    value += input[i];
                                    i++;
                                }
                            }
                            if (i < input.length() && input[i] == '#') {
                                value += input[i];
                                i++;
                                Tokens.emplace_back(COMMENT, value, line);
                            }
                            else{
                                Tokens.emplace_back(UNDEFINED, value, line);
                            }
                            line += j;
                            break;
                        }
                        // line comment
                        else{
                            i++;
                            while(i < input.length() && input[i] != '\n'){
                                value += input[i];
                                i++;
                            }
                            value.erase(value.length()-1);
                            Tokens.emplace_back(COMMENT, value, line);
                            line++;
                        }
                        break;
                    case '\'':
                        value = input[i];
                        i++;
                        while(i < input.length() && input[i] != '\''){
                            value += input[i];
                            i++;
                        }
                        if (i < input.length() && input[i] == '\''){
                            value += input[i];
                            i++;
                            Tokens.emplace_back(STRING, value, line);
                        }
                        else{
                            Tokens.emplace_back(UNDEFINED, value, line);
                        }
                        i--;
                        break;
                    default:
                        if (isalpha(c)){
                            value = "";
                            if (input.substr(i,5) == "Rules" && !isalnum(input[i+5])){
                                Tokens.emplace_back(RULES, "Rules", line);
                                i += 4;
                                break;
                            }
                            else if (input.substr(i,7) == "Queries" && !isalnum(input[i+7])){
                                Tokens.emplace_back(QUERIES, "Queries", line);
                                i += 6;
                                break;
                            }
                            else if (input.substr(i,7) == "Schemes" && !isalnum(input[i+7])){
                                Tokens.emplace_back(SCHEMES, "Schemes", line);
                                i += 6;
                                break;
                            }
                            else if (input.substr(i,5) == "Facts" && !isalnum(input[i+5])){
                                Tokens.emplace_back(FACTS, "Facts", line);
                                i += 4;
                                break;
                            }
                            else{
                                while(isalnum(input[i]) && string(1,input[i]) != " " && string(1,input[i]) != "\n" ){
                                    value += input[i];
                                    i++;
                                }
                                i--;
                                Tokens.emplace_back(ID, value, line);
                                break;
                            }
                        }
                        else{
                            Tokens.emplace_back(UNDEFINED, string(1,c), line);
                            break;
                        }
                }
            }
            Tokens.emplace_back(EoF, "", line);
            return Tokens;
        }
};