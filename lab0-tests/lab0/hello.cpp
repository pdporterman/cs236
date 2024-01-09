#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int main(int argc, char* argv[]) {
ifstream in;
in.open(argv[1]);
stringstream ss;
ss << in.rdbuf();
string input = ss.str();
int chars = 0;
int lines = 0;
int spaces = 0;
int digits = 0;
int letters = 0;
for (auto c : input){
if (isspace(c)){
spaces++;
if (c == '\n'){
lines++;};
}else if (isdigit(c)){
digits++;}else if (isalpha(c)){
letters++;};
chars++;};
in.close();
cout<<"chars: "<<chars<<endl;
cout<<"lines: "<<lines<<endl;
cout<<"spaces: "<<spaces<<endl;
cout<<"digits: "<<digits<<endl;
cout<<"letters: "<<letters<<endl;
}