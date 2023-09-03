// CS255
// P03 Infix to Postfix
//		It accepts an infix expression, converts it to postfix, 
//		and evaluates the postfix
// Samantha Roldan
//

#include <iostream>
#include <string>
#include "InfixToPostfix.h"
#include "PostfixEval.h"
#include "CS255Exceptions.h"

using namespace std;

int main() {
	// use iexp for infix to postfix conversion
	InfixToPostfix iexp;

	string infixExp; //infix expression input
	string postfixExp; //postfix expression output

	PostfixEval pexp; //use pexp to evaluate postfix expressions

	// input and evaluate infix expressions until the
	// user enters an empty string

	// get the first expression
	cout << "Enter an infix expression: ";
	getline(cin, infixExp);

	while (infixExp != "") {
		// an exception may occur. enclose the conversion
		// to postfix and the output of the expression
		// value in a try block
		try {
			// set entered infix expression in iexp
			iexp.setInfixExp(infixExp);
			// convert to postfix
			postfixExp = iexp.postfix();

			// output the postfix expression
			cout << "The postfix form is " << postfixExp << endl;

			// use PostfixEval object pexp
			// store postfileExp string
			pexp.setPostfixExp(postfixExp);

			// Evaluate the postfix expression
			cout << "Value of the expression = " << pexp.evaluate() << endl << endl;
		}
		// catch an exception and output the error
		catch (const ExpressionError& ee) {
			cout << ee.what() << endl << endl;
		}

		// input another expression
		cout << "Enter an infix expression: ";
		getline(cin, infixExp);
	} //end while

	return 0;
} //end main

