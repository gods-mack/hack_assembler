
#ifndef _PASS1_H
#define _PASS1_H

#include<bits/stdc++.h>
using namespace std;

//void hello();


string decimalToBinary(int );	
int string2int(string );

string make16bit(string);
string replaceSpace(string);
string removeComment(string);
string final_ext(string);

map<string,string> label_parser(ifstream&);

#endif