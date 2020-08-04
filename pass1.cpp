
// parser1

#include<bits/stdc++.h>
#include "pass1.h"
using namespace std;



string decimalToBinary(int n) 
{ 
    //finding the binary form of the number and  
    //coneverting it to string.  
    string s = bitset<64> (n).to_string(); 
      
    //Finding the first occurance of "1" 
    //to strip off the leading zeroes. 
    const auto loc1 = s.find('1'); 
      
    if(loc1 != string::npos) 
        return s.substr(loc1); 
      
    return "0"; 
} 

int string2int(string s){

	int num = 0;

	for(int i = 0; i < (int)s.length(); i++){
		num = num*10 + (s[i] - '0');
	}
	return num;
}

string make16bit(string ins) {

	if(ins.length() < 16) {
		string rem = "";
		for(int j = 0; j < 16-ins.length(); j++){
			rem += "0";
		}
		ins = rem + ins;
	}

	return ins;

}

string replaceSpace(string line) {
	string s = "";
	for(int i = 0; i < line.length(); i++) {
		
		if(int(line[i]) == 32){
			continue;
		}
		else{
			s += line[i];
		}
	}
	return s;
}

string removeComment(string line) {


	int n = line.length();
	string s = "";


	int i = 0;
	while(1) {
		s += line[i];
		i++;
		if(i > n or line[i] == '/'){
			break;
		}
	}
	return s;
}

string final_ext(string line ) {
	string s = "";
	for(int i = 0; i < line.length(); i++){
		if((int)line[i] == 0 or (int)line[i] == 13) {
			continue;
		}
		else{
			s += line[i];
		}
	}
	return s;
}



// pass1 phase
// assign all label to symbol_table
map<string,string> label_parser(ifstream & fin){

	 map<string,string> sym_table = {
	{"SP", 		"0"},
	{"LCL", 	"1"},
	{"ARG",  	"2"},
	{"THIS", 	"3"},
	{"THAT", 	"4"},
	{"R0", 		"0"},
	{"R1", 		"1"},
	{"R2", 		"2"},
	{"R3", 		"3"},
	{"R4", 		"4"},
	{"R5", 		"5"},
	{"R6", 		"6"},
	{"R7", 		"7"},
	{"R8", 		"8"},
	{"R9", 		"9"},
	{"R10", 	"10"},
	{"R11", 	"11"},
	{"R12", 	"12"},
	{"R13", 	"13"},
	{"R14", 	"14"},
	{"R15", 	"15"},
	{"SCREEN",  "16384"},
	{"KBD",		"24576"}
	
	};

	string line = "";
	int line_ptr = 0;
	while(fin) {
		
		getline(fin,line);

		
		if(line[0] != '/' and line.length()!=0 and line[0] != '\n' and(int)line[0] != 13 and line[0]!='('){
			
			line_ptr++;
		}

	
		if(line[0]=='(') { // label statment
			int l = line.find('(');
			int r = line.find(')');

			string label = line.substr(l+1,r-1);
			string ans = decimalToBinary(line_ptr);
			sym_table[label] = to_string(line_ptr); 
			
			//sym_table[label] = make16bit(ans);


		}
	}
	return sym_table;
	
}
