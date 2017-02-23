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
string Global_Language = "A3";
string Test_File = "test_5.txt";
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

	printer(Global_Language, _Tokens);

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

	int currLine = 0;
	int currTokenIndex = 0;
	string currID;
	string currString;

	if (!lines.empty()) {
		for (size_t i = 0; i < lines.size(); i++) {            // Going through each line
			currLine++;
			currTokenIndex = 0;
			for (size_t j = 0; j < lines[i].size(); j++) {     // Going through each character
															// Check for comment
				if (lines[i][j] == '/') {
					if (lines[i][++j] == '/') {
						break;
					}
					else
						continue;
				}
				else if (lines[i][j] == '"') {
					string s;
					++j;
					while (lines[i][j] != '"') {
						s.append(string(1, lines[i][j]));
						++j;
					}
					currTokenIndex++;
					// create token for ident
					TokenList.push_back(tonkenate(currLine, "string", s));
				}
				// If the first character is a letter extract
				// the whole word (from current character until
				// you reach a non-word character)
				else if (isLetter(lines[i][j], true)) {
					string s = string(1, lines[i][j]);
					j++;
					while (isLetter(lines[i][j], false)) {
						s.append(string(1, lines[i][j]));
						j++;
					}

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
				else if (isNumber(lines[i][j], true)) {
					string intStr = string(1, lines[i][j]);
					j++;
					while (isNumber(lines[i][j], false)) {
						intStr.append(string(1, lines[i][j]));
						j++;
					}
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
					switch (lines[i][j]) {
						// Paired delimeters
						// 6 comma = ','
					case ',':
						TokenList.push_back(tonkenate(currLine, "comma"));
						break;
						// 7 semi = ';'
					case ';':
						TokenList.push_back(tonkenate(currLine, "semi"));
						break;
						// 31 angle1 = '<'
					case '<':
						if (lines[i][j + 1] == '=')
							// 54 ople = "<="
							TokenList.push_back(tonkenate(currLine, "ople"));
						// 56 opshl = "<<"
						else if (lines[i][j + 1] == '<')
							TokenList.push_back(tonkenate(currLine, "opshl"));
						else
							TokenList.push_back(tonkenate(currLine, "angle1"));
						break;
						// 32 angle2 = '>'
					case '>':
						if (lines[i][j + 1] == '=')
							// 55 opge = ">="
							TokenList.push_back(tonkenate(currLine, "opge"));
						else if (lines[i][j + 1] == '>')
							// 57 opshr = ">>"
							TokenList.push_back(tonkenate(currLine, "opshr"));
						else
							TokenList.push_back(tonkenate(currLine, "angle2"));
						break;
						// 33 brace1 = '{'
					case '{':
						TokenList.push_back(tonkenate(currLine, "brace1"));
						break;
						// 34 brace2 = '}'
					case '}':
						TokenList.push_back(tonkenate(currLine, "brace2"));
						break;
						// 35 bracket1 = '['
					case '[':
						TokenList.push_back(tonkenate(currLine, "bracket1"));
						break;
						// 36 bracket2 = ']'
					case ']':
						TokenList.push_back(tonkenate(currLine, "bracket2"));
						break;
						// 37 parens1 = '('
					case '(':
						TokenList.push_back(tonkenate(currLine, "perns1"));
						break;
						// 38 parens2 = ')'
					case ')':
						TokenList.push_back(tonkenate(currLine, "pernes2"));
						break;
						// Other punctuation
						// 41 aster = '*'
					case '*':
						TokenList.push_back(tonkenate(currLine, "aster"));
						break;
						// 42 caret = '^'
					case '^':
						TokenList.push_back(tonkenate(currLine, "caret"));
						break;
						// 43 colon = ':'
					case ':':
						TokenList.push_back(tonkenate(currLine, "colon"));
						break;
						// 44 dot = '.'
					case '.':
						TokenList.push_back(tonkenate(currLine, "angle1"));
						break;
						// 45 equal = '='
					case '=':
						if (lines[i][j + 1] == '=')
							// 52 opeq = "=="
							TokenList.push_back(tonkenate(currLine, "opeq"));
						else
							TokenList.push_back(tonkenate(currLine, "equal"));
						// 46 minus = '-'
					case '-':
						if (lines[i][j + 1] == '>')
							// 51 oparrow = "->"
							TokenList.push_back(tonkenate(currLine, "oparrow"));
						else
							TokenList.push_back(tonkenate(currLine, "minus"));
						break;
						// 47 plus = '+'
					case '+':
						TokenList.push_back(tonkenate(currLine, "plus"));
						break;
						// 48 slash = '/'
					case '/':
						TokenList.push_back(tonkenate(currLine, "slash"));
						break;
						// 53 opne = "!="
					case '!':
						if (lines[i][j + 1] == '=')
							TokenList.push_back(tonkenate(currLine, "opne"));
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
		return regex_match(s, regex("[a-zA-z_]"));
	else
		return regex_match(s, regex("[a-zA-z_0-9]"));
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
	if (regex_match(s, regex("-?[0-9]+\\.[0-9]+"))) {
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