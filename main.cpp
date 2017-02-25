//	Team ID:			DDM
//	Daniel Bravo		bravod@csu.fullerton.edu
//	David Feinzimer		dfeinzimer@csu.fullerton.edu
//	Mircea Dumitrache	dmircea@csu.fullerton.edu
//	Description:		Contains tests and their parameters.

#include <iostream>
#include <fstream>
#include <vector>
#include "Tokenizer.h"

using namespace std;

vector<string> txt_to_strings(string txt_file);
void printer(string Global_Language, vector<Token> &tokens);


//	========  Global Variables  ========
string _Language = "A3";
string Test_File = "test_X.txt";
vector<string> _Strings;

int main() {

	//declare int and make user input the test number
	//NOTE: files must be named after the following prototype: 'test_X.txt' where X is a number
	int x = 0;
	while (true) {
		
		cout << "Please input a test number or a negative number to exit: ";
		cin >> x;
		//if negative x then exit loop
		if (x < 0)
			break;
		//concatinates string to match reuired name
		Test_File = "test_" + to_string(x) + ".txt";

		//checks if a file is available
		ifstream f(Test_File.c_str());//if true run lexer
		if (f.good())
		{
			// ========  Start Test  ========
			cout << "========  Start Test - " << Test_File << " ========" << endl;


			_Strings = txt_to_strings(Test_File);

			_Tokens = tokenize(_Strings);

			printer(_Language, _Tokens);

			_Strings.clear();


			cout << "========  End Test  ========" << endl;
			// ========  End Test  ========
		}//else output error
		else cout << "No such file found in current directory!" << endl;
	}

	return 0;
}

vector<string> txt_to_strings(string txt_file) {	//	Convert an input txt file to a string with newline characters
	vector<string> strings;		// This is what our function will return
	ifstream reader;
	reader.open(txt_file);
	while (!reader.eof()) {
		string new_string;
		getline(reader, new_string);
		strings.push_back(new_string);
	}
	return strings;
}

void printer(string Global_Language, vector<Token> &tokens) { // Prints out all tokens

	cout << "(:lang " << Global_Language << endl;	//	Print the language

	// for (size_t i = 0; i < tokens.size(); i++) {	// For each token in our tokens vector

	// 	for (int i = 0; i < 3; i++) { // Indent the new line
	// 		cout << " ";
	// 	}

	// 	cout << "(:token " << tokens[i].ln << " " << tokens[i].id;	//	Print line number

	// 	if (tokens[i].id == "ident") {	//	If the token has an index, print it
	// 		cout << " :ix " << tokens[i].ix;
	// 	}

	// 	if (tokens[i].id == "ident" |
	// 		tokens[i].id == "string" |
	// 		tokens[i].id == "int" |
	// 		tokens[i].id == "float") {
	// 		cout << " :str \"" << tokens[i].str << "\"";	//	If the token has a str, print it
	// 	}

	// 	cout << ")" << endl;	//	Finish printing that token


	// 	//trail section
	// 	cout << "now from token cout" << endl;
	// 	cout << tokens[i] << endl;
	// }

	for (int i = 0; i < tokens.size(); ++i)
	{
		cout << "  " << tokens[i] << endl;
	}

	cout << ")" << endl;	//	Finish the print function
	tokens.clear();
}