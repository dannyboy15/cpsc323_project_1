#ifndef Lexer_h
#define Lexer_h
#endif

//	========  Function Prototypes  ========
struct Token;
std::vector<Token> tokenize(std::vector<std::string> lines);
bool isNumber(char c, bool firstChar);
std::string whichKwd(std::string s);
std::string whichNumType(std::string s);
Token tokenate(int ln, std::string id, int ix, std::string str);
bool isLetter(char c, bool firstChar);
Token tokenate(int ln, std::string id, std::string str);
Token tokenate(int ln, std::string id);
std::ostream& operator<<(std::ostream& os, const Token& obj);
bool operator==(const Token& lhs);