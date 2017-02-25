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
void printer(string language, vector<Token> &tokens);


//	========  Global Variables  ========
string _Language = "A3";
string Test_File = "test_X.txt";
string expectedOutput = "expected_output_X.txt";
vector<string> _Strings;

int main() {
	//declare int and make user input the test number
	//NOTE: files must be named after the following prototype: 'test_X.txt' where X is a number
	int x = 0;
	while (true) {
		cout << "Please input a test number or a negative number to exit: ";
		cin >> x;
		//	If negative x then exit loop
		if (x < 0)
			break;
		//	Concatenates string to match required name
		Test_File = "test_" + to_string(x) + ".txt";

		//  Checks for correct input
		if (!cin.fail())
		{
			//  Checks if a file is available
			ifstream f(Test_File.c_str());                       //If true run lexer
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
			}                                                    //  Else output error
			else cout << "No such file found in current directory!" << endl;
		}
		else //  If output is not correct, display message and clear input stream
		{ 
			cout << "Wrong input detected." << endl; 
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
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

void printer(string language, vector<Token> &tokens) { // Prints out all tokens

	cout << "(:lang " << language << endl;	//	Print the language

	for (int i = 0; i < tokens.size(); ++i)
	{
		cout << "  " << tokens[i] << endl;
	}

	cout << ")" << endl;	//	Finish the print function
	tokens.clear();
}