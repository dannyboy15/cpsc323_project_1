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
#include <iostream>
#include <map>
#include <regex>
#include <stdio.h>
#include <string>
#include <vector>


using namespace std;

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
	int ln;		// line number
    string id;		// id based on grammar
	int ix = 0;	// optional; index number
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

	for (int i = 0; i < tokens.size(); i++) {	// For each token in our tokens vector
		
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
			tokens[i].id == "float" | 
			tokens[i].id == "flpoat") {	
				cout << " :str \"" << tokens[i].str << "\"";	//	If the token has a str, print it
		}
		
		cout << ")" << endl;	//	Finish printing that token
	}

	cout << ")" << endl;	//	Finish the print function
	tokens.clear();
}

map<string, regex> gmr = {
	{ "comment", regex("//.*") }, // Treat as whitespace up to newline char; like C/C++/Java.
								  //   2 ident = LU LUD *  // identifier.
								  //     LU = '_' | [a..zA..Z]  // Letter-Underscore.
								  //     LUD = LU | DIGIT  // Letter-Underscore-Digit.
								  //     DIGIT = [0..9]
								  //   3 int = ( NDIG | PDIG ) DIGIT * // integer; might start with a negative-digit.
								  //     NDIG = '-' | DIGIT  // Negative-Digit.
								  //     PDIG = DIGIT  // Positive-Digit.
								  //   4 float = int '.' DIGIT + // float, with decimal point and 1+ fractional digits.
								  //   5 string = '"' .* '"' // Cannot contain a double-quote char; no escape chars.
								  // Unpaired delimiters
	{ "comma", regex(",") },  // 6 comma = ','
	{ "6", regex(",") },
	{ "semi", regex(";") },  //  7 semi = ';'
	{ "7", regex(";") },
	// Keywords
	{ "kwd", regex(";") },  //  7 semi = ';'
	{ "7", regex(";") },
	// 10 kwdprog = "prog"
	// 11 kwdmain = "main"
	// 12 kwdfcn = "fcn"
	// 13 kwdclass = "class"
	// 15 kwdfloat = "float"
	// 16 kwdint = "int"
	// 17 kwdstring = "string"
	// 18 kwdif = "if"
	// 19 kwdelseif = "elseif"
	// 20 kwdelse = "else"
	// 21 kwdwhile = "while"
	// 22 kwdinput = "input"
	// 23 kwdprint = "print"
	// 24 kwdnew = "new"
	// 25 kwdreturn = "return"
	// // Paired delimeters
	// 31 angle1 = '<'
	// 32 angle2 = '>'
	// 33 brace1 = '{'
	// 34 brace2 = '}'
	// 35 bracket1 = '['
	// 36 bracket2 = ']'
	// 37 parens1 = '('
	// 38 parens2 = ')'
	// // Other punctuation
	// 41 aster = '*'
	// 42 caret = '^'
	// 43 colon = ':'
	// 44 dot = '.'
	// 45 equal = '='
	// 46 minus = '-'
	// 47 plus = '+'
	// 48 slash = '/'
	// // Multi-char operators
	// 51 oparrow = "->"
	// 52 opeq = "=="
	// 53 opne = "!="
	// 54 ople = "<="
	// 55 opge = ">="
	// 56 opshl = "<<"
	// 57 opshr = ">>"
	// // Miscellaeous
	// 99 error // Unknown token.
	//  0 eof // End-of-Input.\
	    
};