#ifndef INFIX_TO_POSTFIX
#define INFIX_TO_POSTFIX

#include <iostream>
#include <string>
#include "MyStack.h"
#include <ctype.h>

#include "ExpressionSymbol.h"	
#include "CS255Exceptions.h"	

using namespace std;

const char lParen = '(';
const char rParen = ')';

class InfixToPostfix
{
public:
	// default constructor. infix expression is NULL string
	InfixToPostfix();

	// initialize the infix expression
	InfixToPostfix(const string& infixExp);

	// change the infix expression
	void setInfixExp(const string& infixExp);

	// return a string that contains the equivalent postfix expression.
	//   The function throws ExpressionError if an error occurs during conversion
	string postfix();

private:
	// the infix expression to convert
	string infixExpression;

	// built to contain the postfix equivalent of infixExpression
	string postfixExpression;

	// stack of expressionSymbol objects
	myStack<ExpressionSymbol> operatorStack;

	void outputHigherOrEqual(const ExpressionSymbol& op);

	bool isOperator(char ch) const;
};

// Determine which operators need to be popped from stack
//	before adding the new operator, "op"
//  Determines whether operator left on the stack should be output before
//  pushing operator right on the stack
void InfixToPostfix::outputHigherOrEqual(const ExpressionSymbol& op) {
	ExpressionSymbol op2;

	while (!operatorStack.isEmpty() && (op2 = operatorStack.top()) >= op) {
		operatorStack.pop();
		postfixExpression += op2.getOp();
		postfixExpression += ' ';
	}
}

bool InfixToPostfix::isOperator(char ch) const {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

InfixToPostfix::InfixToPostfix() {}

InfixToPostfix::InfixToPostfix(const string& infixExp) : infixExpression{ infixExp } {}

void InfixToPostfix::setInfixExp(const string& infixExp) {
	// assign a new infix expression
	infixExpression = infixExp;
	// make postfixExpression the NULL string
	postfixExpression = "";
}

string InfixToPostfix::postfix() {

	ExpressionSymbol op;
	char ch;

	//put things into the stack and into the postfix expression
	for (int i = 0; i < infixExpression.length(); i++) {
		ch = infixExpression[i];

		if (isdigit(ch) && ch != ' ') { 
			postfixExpression.push_back(ch);
			postfixExpression.push_back(' ');
		}
		else if (isOperator(ch) || ch == lParen) { 
			op = ExpressionSymbol(ch);

			//check if what's on the stack is of higher or equal precedence
			outputHigherOrEqual(op);
			
			//push op on the stack
			operatorStack.push(op);
		}
		else if (ch == rParen) { 
			op = ExpressionSymbol(ch);

			//get up to the left paren off the stack -- hopefully finding a lparen
			outputHigherOrEqual(op);

			if (operatorStack.isEmpty()) {
				throw ExpressionError("infix2Postfix: Missing \'(\'");
			}
			else {
				operatorStack.pop();
			}
		}
		else if (!isspace) { 
			throw ExpressionError("InfixToPostfix: Invalid input");
		}

	}

	//check for the remaining things in the stack
	while (!operatorStack.isEmpty()) {
		op = operatorStack.topAndPop();
		if (op.getOp() == '(') {
			throw ExpressionError("infix2Postfix: Missing \')\'");
		}
		else {
			postfixExpression.push_back(op.getOp());
		}
	}

	return postfixExpression;


} //end postfix()
#endif	// INFIX_TO_POSTFIX
