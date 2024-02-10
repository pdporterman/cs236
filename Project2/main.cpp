#include <iostream>
#include "Scanner.h"
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;
    ifstream in;
    in.open(argv[1]);
    stringstream ss;
    ss << in.rdbuf();
    string input = ss.str();
    Scanner s = Scanner(input);
    vector<Token> Tokens = s.scanTokens();
    Parser p = Parser(Tokens);
    p.startParse();
}