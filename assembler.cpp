
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include "code.h"

#include "pass1.h"

using namespace std;


map<string,string > s_table;
int var_counter = 16;


string Ainstruction(string line) {


	int number = 0;
	string num = "";
	string ans = "";
	for(int i = 0; i < line.length(); i++ ) {
		if(i == 0) {
			continue;
		}
		else{
			num += line[i];
		}
	}

	if(s_table.find(num) != s_table.end()) {
		int tmp = string2int(s_table[num]);
		ans = decimalToBinary(tmp);
	}

	else{
		if((int)line[1]>=48 and (int)line[1]<=57){
			number = string2int(num);
			ans = decimalToBinary(number);

		}
		else{
			
			s_table[num] = to_string(var_counter); 
			var_counter++;
			int tmp = string2int(s_table[num]);
			ans = decimalToBinary(tmp);


		}
		

	}



	// num = num*10 + (line[i] - '0');
	
	ans = make16bit(ans);
	return ans;
}


string jump_ins(string line) {

	std::string s = line;
	size_t p = s.find(";");
	if (p != std::string::npos) {
		s.erase(0, p+1);
		std::transform(s.begin(), s.end(), s.begin(), ::toupper);
		return s;
	}
	// No jmp mnemonic.
	return "";

}

string dest_ins(string line) {

	std::string s = line;
	size_t e = s.find("=");
	if (e == std::string::npos)
		s = ""; // Dest = null.
	else { 
		s.erase(s.find("="), std::string::npos);
	}
	return s;

}

string comp_ins(string line) {
	std::string s = line;
	size_t p = s.find(";");
	if (p != std::string::npos)
		s.erase(p+1, std::string::npos);

	p = s.find("=");
	if (p != std::string::npos)
		s.erase(0, p+1);

	size_t end = s.find_last_not_of(";"); 
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s.substr(0, end+1);

}

string Cinstruction(string line) {

	//cout<<"C Instruction\n"<<endl;

	string des = "";
	string comp = "";
	string jump = "";

	des = dest_ins(line);
	comp = comp_ins(line);
	jump = jump_ins(line);

	if(jump.length() == 4){
		jump.pop_back();
	}


	string ans =  "111"+opcode[comp]+dests[des]+jumps[jump];
	
	ans = make16bit(ans);
	return ans;

		
}

void LableInstruction(string line,int line_pointer){

	string label = 0;


	for(int i = 0; i < (int)line.length(); i++) {
		if(line[i] == '(' or line[i] ==')'){
			continue;
		}
		else{
			label += line[i];
		}
	}


	string ans = decimalToBinary(line_pointer+1);	
	ans = make16bit(ans);

	s_table[label] = ans;
	

}

int main() {

	ifstream fin,fin1;
	ofstream fout;

	string line;
	vector<string> prog;

	fin.open("Max.asm");
	fin1.open("Max.asm");
	fout.open("Max.hack");

	int m = 0;
	int line_pointer = 0;
  

  
	// update symbol_table with new labels
	s_table = label_parser(fin1); // pass1
	fin1.close();

	while(fin) {

		getline(fin,line);
		if(line[0] == '/' or line.length()==0 or line[0] == '\n' or (int)line[0] == 13){
			
			continue;
		}
	
		
		line = replaceSpace(line); // remove space
		line = removeComment(line);
		line = final_ext(line);   // string cleaning
		

		if(line.find("@") != -1) {  // A-instruction
			string ains = Ainstruction(line);
			fout<<ains<<endl;
			//line_pointer++;
		}
		else if(line.find("(") != -1) { // skip label
		}
		else  { // C-Instruction
			string cins = Cinstruction(line);
			fout<<cins<<endl;
		}
		prog.push_back(line);
		m++;
		
	}

	fin.close();
	fout.close();

	

	cout<<"SYMBOL TABLE\n";
	for(auto it=s_table.begin(); it!=s_table.end();++it){
		cout<<it->first<<" "<<it->second<<endl;
	}
}