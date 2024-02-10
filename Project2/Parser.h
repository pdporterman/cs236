#pragma once

#include <vector>
#include "Token.h"
#include <utility>
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include "DatalogProgram.h"


using namespace std;

class Parser {
private:
    vector<Token> tokens;
public:
    explicit Parser(const vector<Token>& tokens) : tokens(tokens) {}


    Predicate pred;
    Rule newRule;
    DataLog dl = DataLog();

    DataLog startparse() {
        try{
            parse();
            return dl;
        } catch (const std::exception& e) {
            cout << "Failure!\n  " << tokens[0].toString() << endl;
        }
    }


    TokenType nextToken(){
        return tokens[1].getType();
    }



    TokenType tokenType() const {
        return tokens[0].getType();
    }


    void advanceToken() {
        tokens.erase(tokens.begin());
    }


    static void throwError() {
        throw std::runtime_error("aaaaaaaaaaahhhhhhhhhh");
    }

    void parse() {
        match(TokenType::SCHEMES);
        match(TokenType::COLON);

        if (nextToken() != TokenType::ID){
            throwError();
        }

        while (tokenType() != TokenType::FACTS){
            pred = Predicate();
            scheme();
        }

        match(TokenType::FACTS);
        match(TokenType::COLON);

        if (nextToken() != TokenType::ID){
            throwError();
        }

        while (tokenType() != TokenType::RULES){
            pred = Predicate();
            fact();
        }

        match(TokenType::RULES);
        match(TokenType::COLON);

        if (nextToken() != TokenType::ID){
            throwError();
        }

        while (tokenType() != TokenType::QUERIES){
            newRule = Rule();
            pred = Predicate();
            rule();
        }

        match(TokenType::QUERIES);
        match(TokenType::COLON);

        if (nextToken() != TokenType::ID){
            throwError();
        }

        while (tokenType() != TokenType::EoF){
            pred = Predicate();
            queries();
        }

    }


    void match(TokenType t) {
        //std::cout << "match: " << t << std::endl;
        while (tokenType() == COMMENT){
            advanceToken();
        }
        if (tokenType() == t) {
            if (t == TokenType::ID || t == TokenType::STRING){
                Parameter para = *new Parameter(tokens[0].getValue(), t == TokenType::ID);
                pred.addPredicate(para);
            }
            advanceToken(); // Advance to the next token
        } else {
            throwError();
        }
    }


    void idList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        } else {
            // lambda do nothing
        }
    }

    void scheme() {
        match(TokenType::ID);         // scheme -> ID
        match(TokenType::LEFT_PAREN); // scheme -> ID LEFT_PAREN
        match(TokenType::ID);         // scheme -> ID LEFT_PAREN ID
        idList();                 // scheme -> ID LEFT_PAREN ID idList
        match(TokenType::RIGHT_PAREN);
        dl.addScheme(pred);
    }


    void fact() {
        match(TokenType::ID);         // fact -> ID
        match(TokenType::LEFT_PAREN); // fact -> ID LEFT_PAREN
        match(TokenType::ID);         // fact -> ID LEFT_PAREN ID
        idList();                 // fact -> ID LEFT_PAREN ID idList
        match(TokenType::RIGHT_PAREN);
        match(TokenType::PERIOD);
        dl.addFact(pred);
    }


    void rule() {
        match(TokenType::ID);         // fact -> ID
        match(TokenType::LEFT_PAREN); // fact -> ID LEFT_PAREN
        match(TokenType::ID);         // fact -> ID LEFT_PAREN ID
        idList();                 // fact -> ID LEFT_PAREN ID idList
        match(TokenType::RIGHT_PAREN);
        newRule.addPred(pred);
        pred = Predicate();
        match(TokenType::COLON_DASH);
        match(TokenType::PERIOD);
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        match(TokenType::ID);
        idList();
        match(TokenType::RIGHT_PAREN);
        newRule.addPred(pred);
        pred = Predicate();
        while (tokenType() != PERIOD){
            match(TokenType::COMMA);
            match(TokenType::ID);
            match(TokenType::LEFT_PAREN);
            match(TokenType::ID);
            idList();
            match(TokenType::RIGHT_PAREN);
            newRule.addPred(pred);
            pred = Predicate();
        }
        match(TokenType::PERIOD);
        newRule.addPred(pred);
        dl.addRule(newRule);
    }

    void queries() {
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        match(TokenType::ID);
        idList();
        match(TokenType::RIGHT_PAREN);
        match(TokenType::Q_MARK);
        dl.addQuery(pred);
    }
};
