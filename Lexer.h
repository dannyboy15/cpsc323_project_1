#ifndef Lexer_h
#define Lexer_h
#endif

// #include <string>
// #include <vector>
// #include <regex>

// using namespace std;

//	========  Function Prototypes  ========
struct Token;
vector<Token> tokenize(vector<string> lines);
bool isNumber(char c, bool firstChar);
string whichKwd(string s);
string whichNumType(string s);
Token tokenate(int ln, string id, int ix, string str); // takes current variables to create a token
bool isLetter(char c, bool firstChar);
Token tokenate(int ln, string id, string str);
Token tokenate(int ln, string id);
ostream& operator<<(ostream& os, const Token& obj);