#pragma once
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>

/*
https://en.wikipedia.org/wiki/Reverse_Polish_notation
https://en.wikipedia.org/wiki/Shunting-yard_algorithm

shunting yard algorithm to convert infix expression to Reverse Polish Notation, which is "parenthesis-free".

"Reverse Polish notation (RPN) is a mathematical notation in which every operator follows all of its operands"
*/
class ExprToken
{
private:
	string token;
	int priority;
	int numberOfOperands;
	bool isFunction;
public:
	ExprToken() :token(""), priority(-1), numberOfOperands(0){}
	ExprToken(const string &t, int pri = -1, int num = 0, bool isF = false) : token(t), priority(pri), numberOfOperands(num), isFunction(isF){}
	std::pair<string, std::pair<int, int> > GetToken()
	{
		return std::make_pair(this->token, std::make_pair(priority, numberOfOperands));
	}
	string GetLiteral(){ return token; }
	int GetPriority(){ return priority; }
	bool IsOperator(){ return numberOfOperands > 0 || priority >= 0; }
	bool IsOperand(){ return priority == -1; }
	bool IsFunction(){ return isFunction; }
};
class ExprParser
{
private:
	static const string delimiter;
	static unordered_map<string, std::pair<int, int> > operatorLst;
	queue<ExprToken> tokenQ;
	bool sanityCheck(const string &S);
	void parse(const string &S);
public:
	ExprParser(const string &S) : tokenQ()
	{
		parse(S);
	}
	string RPN();
};


void testExprParserRPN();
