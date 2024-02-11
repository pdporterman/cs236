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
    Parameter para = Parameter("temp", true);
public:
    explicit Parser(const vector<Token>& tokens) : tokens(tokens) {}


    Predicate pred;
    Rule newRule;
    DataLog dl = * new DataLog();

    void startParse() {
        try{
            parse();
            cout << dl.ToString() << endl;
        } catch (const std::exception& e) {
            cout << "Failure!\n  " << tokens[0].toString() << endl;
        }
    }


    DataLog getDL() const{
        return dl;
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

        if (tokenType() != TokenType::ID){
            throwError();
        }

        while (tokenType() != TokenType::FACTS){
            pred = Predicate();
            scheme();
        }

        match(TokenType::FACTS);
        match(TokenType::COLON);

        if (tokenType() != TokenType::ID && tokenType() != TokenType::RULES){
            throwError();
        }

        while (tokenType() != TokenType::RULES){
            pred = Predicate();
            fact();
        }

        match(TokenType::RULES);
        match(TokenType::COLON);

        if (tokenType() != TokenType::ID && tokenType() != TokenType::QUERIES){
            throwError();
        }

        while (tokenType() != TokenType::QUERIES){
            newRule = Rule();
            pred = Predicate();
            rule();
        }

        match(TokenType::QUERIES);
        match(TokenType::COLON);

        if (tokenType() != TokenType::ID){
            throwError();
        }

        while (tokenType() != TokenType::EoF){
            pred = Predicate();
            queries();
        }

    }


    void match(TokenType t) {
        while (tokenType() == COMMENT){
            advanceToken();
        }
        if (tokenType() == t) {
            if (t == TokenType::ID || t == TokenType::STRING){
                para = Parameter(tokens[0].getValue(), t == TokenType::ID);
                pred.addPredicate(para);
            }
            advanceToken(); // Advance to the next token
        } else {
            throwError();
        }
    }


    void factIdList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(STRING);
            dl.addDomain(para.toString());
            factIdList();
        } else {
            // lambda do nothing
        }
    }


    void schemeIdList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        } else {
            // lambda do nothing
        }
    }

    void idList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            if (tokenType() == ID || tokenType() == STRING){
                match(tokenType());
            }
            idList();
        } else {
            // lambda do nothing
        }
    }

    void scheme() {
        match(TokenType::ID);         // scheme -> ID
        match(TokenType::LEFT_PAREN); // scheme -> ID LEFT_PAREN
        match(TokenType::ID);         // scheme -> ID LEFT_PAREN ID
        schemeIdList();                 // scheme -> ID LEFT_PAREN ID idList
        match(TokenType::RIGHT_PAREN);
        dl.addScheme(pred);
    }


    void fact() {
        match(TokenType::ID);         // fact -> ID
        match(TokenType::LEFT_PAREN); // fact -> ID LEFT_PAREN
        match(TokenType::STRING);
        dl.addDomain(para.toString());
        factIdList();                 // fact -> ID LEFT_PAREN ID idList
        match(TokenType::RIGHT_PAREN);
        match(TokenType::PERIOD);
        dl.addFact(pred);
    }


    void rule() {
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        Helper();
        idList();
        match(TokenType::RIGHT_PAREN);
        newRule.addPred(pred);
        pred = Predicate();
        match(TokenType::COLON_DASH);
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        Helper();
        idList();
        match(TokenType::RIGHT_PAREN);
        newRule.addPred(pred);
        pred = Predicate();
        while (tokenType() != PERIOD){
            match(TokenType::COMMA);
            match(TokenType::ID);
            match(TokenType::LEFT_PAREN);
            Helper();
            idList();
            match(TokenType::RIGHT_PAREN);
            newRule.addPred(pred);
            pred = Predicate();
        }
        match(TokenType::PERIOD);
        newRule.addPred(pred);
        dl.addRule(newRule);
    }

    void Helper(){
        if(tokenType() == TokenType::STRING){
            match(TokenType::STRING);
        } else{
            match(TokenType::ID);
        }
    }


    void queries() {
        match(TokenType::ID);
        match(TokenType::LEFT_PAREN);
        Helper();
        idList();
        match(TokenType::RIGHT_PAREN);
        match(TokenType::Q_MARK);
        dl.addQuery(pred);
    }
};
