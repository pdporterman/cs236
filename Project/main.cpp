#include <iostream>
#include "Scanner.h"
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
#include "Node.h"
#include "Graph.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
//    if (argc < 2) return -1;
//    ifstream in;
//    in.open(argv[1]);
//    stringstream ss;
//    ss << in.rdbuf();
//    string input = ss.str();
//    Scanner s = Scanner(input);
//    vector<Token> Tokens = s.scanTokens();
//    Parser p = Parser(Tokens);
//    p.startParse();
//    Interperter interpreter(p.getDL());

    Graph graph(3);
    graph.addEdge(1,2);
    graph.addEdge(1,0);
    graph.addEdge(0,1);
    graph.addEdge(1,1);
    cout << graph.toString();


};