//	Team ID:			DDM
//	Daniel Bravo		bravod@csu.fullerton.edu
//	David Feinzimer		dfeinzimer@csu.fullerton.edu
//	Mircea Dumitrache	dmircea@csu.fullerton.edu
//	Description:		Contains the declaration of token, conversion functions and our printing function.

#pragma once

#ifndef resources_h
#define resources_h

#endif /* Header_h */

#include <fstream>
#include <string>
#include <vector>


using namespace std;

//	========  Global Variables  ========
const int KEY_WORD_SIZE = 13;
string keyWord[KEY_WORD_SIZE] = {"prog", "main", "fcn", "class",
								"float", "int", "string", "if",
								"elseif", "else", "while", "input",
								"print"};

//	========  Function Prototypes  ========
struct Token;	//	prototype
void printer();	//	prototype
string txt_to_strings();	//	prototype
void print_tokens(vector<Token> &t);
void tokenize(string s);            // a function to derive tokens from a string
Token tokenate();                   // takes current variables to create a token
Token peek_token();
Token next_token();

struct Token {
	int ln;			// line number
	string id;		// id based on grammar
	int ix;			// optional; index number
	string str;		// optional; actual string
};

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

	for (size_t i = 0; i < tokens.size(); i++) {	// For each token in our tokens vector

		for (int i = 0; i < 3; i++) { // Indent the new line
			cout << " ";
		}

		cout << "(:token " << tokens[i].ln << " " << tokens[i].id;	//	Print line number

		if (tokens[i].id == "ident") {	//	If the token has an index, print it
			cout << " :ix " << tokens[i].ix;
		}

		if (tokens[i].id == "ident" |
			tokens[i].id == "string" |
			tokens[i].id == "int" |
			tokens[i].id == "float") {
			cout << " :str \"" << tokens[i].str << "\"";	//	If the token has a str, print it
		}

		cout << ")" << endl;	//	Finish printing that token
	}

	cout << ")" << endl;	//	Finish the print function
	tokens.clear();
}