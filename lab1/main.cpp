#include <iostream>
#include "Scanner.h"

using namespace std;

int main() {
    Scanner s = Scanner("   if the first character of the input is a comma make a COMMA token (with type, value, and line number) remove the comma character from the input");
    Token t = s.scanToken();
    cout << t.toString() << endl;
}