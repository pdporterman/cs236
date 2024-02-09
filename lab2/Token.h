#pragma once

#include <sstream>
#include <utility>

using namespace std;

enum TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EoF,

};


class Token{
    private:
        TokenType type;
        string value;
        char c{};
        int line;

    public:
        Token(TokenType type, string value, int line) : type(type), value(std::move(value)), line(line) { }

        Token(TokenType type, char c, int line) : type(type), c(c), line(line) { }


    static string tokenString(TokenType type) {
        switch (type) {
            case COMMA:
                return "COMMA";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case COMMENT:
                return "COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
            case EoF:
                return "EOF";
            default:
                return "UNKNOWN_TOKEN";  // Handle unknown tokens
        }
    }

        string toString() const {
            stringstream out;
            out << "(" << tokenString(type) << "," << "\"" << value << "\"" << "," << line << ")";
            return out.str();
        }

        TokenType getType() const {
            return type;
        }
};


