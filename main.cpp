//	Team ID:			DDM
//	Daniel Bravo		bravod@csu.fullerton.edu
//	David Feinzimer		dfeinzimer@csu.fullerton.edu
//	Mircea Dumitrache	dmircea@csu.fullerton.edu
//	Description:		Contains tests and their parameters.

#include <iostream>
#include "resources.h"
#include <string>
#include <vector>

using namespace std;

//	========  Global Variables  ========
string _Language = "A3";
string Test_File = "test_1.txt";
vector<Token> _Tokens;
vector<string> _Strings;

//	========  Function Prototypes  ========
void testToken(string cntrl, string test);
void readLineForTokens(string s);
vector<Token> tokenize(vector<string> lines);
bool isLetter(char c, bool firstChar);
bool isNumber(char c, bool firstChar);
string whichKwd(string s);
string whichNumType(string s);
Token tonkenate(int ln, string id, int ix, string str);
Token tonkenate(int ln, string id, string str);
Token tonkenate(int ln, string id);
static const string NOTKWD("NOTKWD");
static const string NOTFLOAT("NOTFLOAT");

int main() {



	// ========  Start Test 1  ========
	cout << "========  Start Test 1 - " << Test_File << " ========" << endl;


	_Strings = txt_to_strings(Test_File);

	_Tokens = tokenize(_Strings);

	printer(_Language, _Tokens);

	_Strings.clear();


	cout << "========  End Test 1  ========" << endl;
	// ========  End Test 1  ========



	return 0;
}

void testToken(string cntrl, string test) {
	if (cntrl.compare(test) == 0)
		cout << "Success! Token are equal";
	else
		cout << "You failed";
}

void reedLineForTokens(string s) {
	// TODO: function that reads input
	//       from text file or standard input
}

vector<Token> tokenize(vector<string> lines) {
	vector<Token> TokenList = *new vector<Token>();

	// Vriables for token cration
	int currLine = 0;
	int currTokenIndex = 0;
	string currID;
	string currString;

	if (!lines.empty()) {				// Make sure lines is not empty
		for (size_t i = 0; i < lines.size(); i++) {            // Going through each line
			
			currLine++;		// Increment line number
			currTokenIndex = 0;	// Reset token index
			
			for (size_t _char = 0; _char < lines[i].length(); _char++) {     // Going through each character in a line
				
				if (lines[i][_char] == '/') {

					// Check for comments
					if (lines[i][_char + 1] == '/') {
						break;	// A comment has been found, stop processing this line and move on to the next
					}
					// 48 slash = '/'
					else {
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "slash"));
					}
				}
				else if (lines[i][_char] == '"') {	// The beginning of a string has been found
					string s;
					++_char;
					while (lines[i][_char] != '"') {	//	Until the quote is closed keep apending chars to the string
						s.append(string(1, lines[i][_char]));
						++_char;
					}
					currTokenIndex++;
					// create token for string
					TokenList.push_back(tonkenate(currLine, "string", s));
				}
				// If the first character is a letter extract
				// the whole word (from current character until
				// you reach a non-word character)
				else if (isLetter(lines[i][_char], true)) {
					string s = string(1, lines[i][_char]);
					_char++;
					while (isLetter(lines[i][_char], false)) {
						s.append(string(1, lines[i][_char]));
						_char++;
					}
					_char--;
					if (whichKwd(s) == NOTKWD) {         // If not a kwd then it's ident
						currTokenIndex++;
						// create token for ident
						TokenList.push_back(tonkenate(currLine, "ident", currTokenIndex, s));
					}
					else {
						currTokenIndex++;
						// create token for kwd
						TokenList.push_back(tonkenate(currLine, whichKwd(s)));
					}
				}
				else if (isNumber(lines[i][_char], true)) {
					string intStr = string(1, lines[i][_char]);
					_char++;

					// ERROR Check: can't have -.1 need -0,1
					while (isNumber(lines[i][_char], false)) {
						intStr.append(string(1, lines[i][_char]));
						_char++;
					}
					_char--;
					if (whichNumType(intStr) == "int") {         // If not a float it's int
						currTokenIndex++;
						// create token for int
						TokenList.push_back(tonkenate(currLine, "int", intStr));
					}
					else if (whichNumType(intStr) == "float") {
						currTokenIndex++;
						// create token for float
						TokenList.push_back(tonkenate(currLine, "float", intStr));
					}
				}
				else {
					switch (lines[i][_char]) {
						// Paired delimeters
						// 6 comma = ','
					case ',':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "comma"));
						break;
						// 7 semi = ';'
					case ';':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "semi"));
						break;
						// 31 angle1 = '<'
					case '<':
						if (lines[i][_char + 1] == '=') {
							// 54 ople = "<="
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "ople"));
						}
						// 56 opshl = "<<"
						else if (lines[i][_char + 1] == '<') {
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "opshl"));
						}
						else {
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "angle1"));
						}
						break;
						// 32 angle2 = '>'
					case '>':
						if (lines[i][_char + 1] == '=') {
							// 55 opge = ">="
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "opge"));
						}
						else if (lines[i][_char + 1] == '>') {
							// 57 opshr = ">>"
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "opshr"));
						}
						else {
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "angle2"));
						}
						break;
						// 33 brace1 = '{'
					case '{':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "brace1"));
						break;
						// 34 brace2 = '}'
					case '}':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "brace2"));
						break;
						// 35 bracket1 = '['
					case '[':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "bracket1"));
						break;
						// 36 bracket2 = ']'
					case ']':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "bracket2"));
						break;
						// 37 parens1 = '('
					case '(':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "parens1"));
						break;
						// 38 parens2 = ')'
					case ')':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "parens2"));
						break;
						// Other punctuation
						// 41 aster = '*'
					case '*':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "aster"));
						break;
						// 42 caret = '^'
					case '^':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "caret"));
						break;
						// 43 colon = ':'
					case ':':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "colon"));
						break;
						// 44 dot = '.'
					case '.':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "angle1"));
						break;
						// 45 equal = '='
					case '=':
						if (lines[i][_char + 1] == '=') {
							// 52 opeq = "=="
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "opeq"));
						}
						else {
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "equal"));
						}
						break;
					// 46 minus = '-'
					//May need to include with number check
					case '-':
						if (lines[i][_char + 1] == '>') {
							// 51 oparrow = "->"
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "oparrow"));
						}
						else {
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "minus"));
						}
						break;
						// 47 plus = '+'
					case '+':
						currTokenIndex++;
						TokenList.push_back(tonkenate(currLine, "plus"));
						break;
						// 53 opne = "!="
					case '!':
						if (lines[i][_char + 1] == '=') {
							currTokenIndex++;
							TokenList.push_back(tonkenate(currLine, "opne"));
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}

	return TokenList;
}

bool isLetter(char c, bool firstChar) {
	string s = string(1, c);
	if (firstChar)
		return regex_match(s, regex("[a-zA-Z_]"));
	else
		return regex_match(s, regex("[a-zA-Z_0-9]"));
}

bool isNumber(char c, bool firstChar) {
	string s = string(1, c);
	if (firstChar)
		return regex_match(s, regex("[-0-9]"));
	else
		return regex_match(s, regex("[\\.0-9]"));
}

string whichKwd(string s) {
	// TODO: Check whether string is a keyword
	//       otherwise return NOTKWD
	string key = "kwd";
	for (int i = 0; i < KEY_WORD_SIZE; ++i)
	{
		if (s == keyWord[i])
		{
			key += keyWord[i];
			return key;
		}
	}
	/*if (s == "prog") {
	return "kwdprog";
	}*/
	return NOTKWD;
}

string whichNumType(string s) {
	// TODO: Check whether string is a float
	//       or an int
	if (regex_match(s, regex("-?[0-9]*\\.[0-9]+"))) {
		return "float";
	}
	else if (regex_match(s, regex("-?[0-9]+"))) {
		return "int";
	}
	return "wrong";
}

Token tonkenate(int ln, string id, int ix, string str) {

	Token tkn = *new Token();
	tkn.ln = ln;
	tkn.id = id;
	tkn.ix = ix;
	tkn.str = str;

	return tkn;
}

Token tonkenate(int ln, string id, string str) {

	Token tkn = *new Token();
	tkn.ln = ln;
	tkn.id = id;
	tkn.str = str;

	return tkn;
}

Token tonkenate(int ln, string id) {

	Token tkn = *new Token();
	tkn.ln = ln;
	tkn.id = id;

	return tkn;
}