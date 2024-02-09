#pragma once

#include <vector>
#include "Token.h"
#include <utility>
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>


using namespace std;

class Parser {
private:
    vector<Token> tokens;
public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }


    TokenType tokenType() const {
        return tokens[0].getType();
    }


    void advanceToken() {
        tokens.erase(tokens.begin());
    }


    void throwError() {
        cout << "error" << endl;
    }


    void match(TokenType t) {
        std::cout << "match: " << t << std::endl;
        if (tokenType() == t) {
            advanceToken(); // Advance to the next token
        } else {
            // Report syntax error if the token types don't match
            throwError();
        }
    }

    void idList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            //idList();
        } else {
            // lambda
        }
    }

    void scheme() {
        match(TokenType::ID);         // scheme -> ID
        match(TokenType::LEFT_PAREN); // scheme -> ID LEFT_PAREN
        match(TokenType::ID);         // scheme -> ID LEFT_PAREN ID
        idList();                 // scheme -> ID LEFT_PAREN ID idList
        match(TokenType::RIGHT_PAREN);
    }




};
