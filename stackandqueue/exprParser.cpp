#include "exprParser.h"
#include <iostream>

using namespace std;

const string ExprParser::delimiter = ",";
unordered_map<string, std::pair<int, int> > ExprParser::operatorLst = unordered_map<string, std::pair<int, int> >({
	{ "+", std::make_pair(1, 2) },
	{ "-", std::make_pair(1, 2) },
	{ "*", std::make_pair(2, 2) },
	{ "/", std::make_pair(2, 2) },
	{ "(", std::make_pair(0, 0) },
	{ ")", std::make_pair(0, 0) },
	{ delimiter, std::make_pair(0, 0) },
	{ "pow", std::make_pair(3, 2) },
	{ "max", std::make_pair(3, 2) },
	{ "abs", std::make_pair(3, 1) }
});

bool ExprParser::sanityCheck(const string &S)
{
	if (S.size() == 0)return false;
	int count = 0;
	for (char c : S)
	{
		if ('(' == c)++count;
		else if (')' == c)--count;
		if (count < 0)
			return false;
	}
	return 0 == count;
}
void ExprParser::parse(const string &S)
{
	if (false == sanityCheck(S))return;
	const char *ps = S.c_str();
	const char *lps = ps;
	unordered_map<string, std::pair<int, int> >::const_iterator iter;
	unordered_map<string, std::pair<int, int> >::const_iterator iter1;
	while (0 != *ps)
	{
		string s(1, *ps);
		iter = operatorLst.find(s);
		if (operatorLst.end() != iter)
		{
			string s1(lps, ps - lps);
			if ('(' == *ps && (iter1 = operatorLst.find(s1)) != operatorLst.end())
				tokenQ.push(ExprToken(iter1->first, iter1->second.first, iter1->second.second, true));
			else
			{
				if (s1.length() > 0)
					tokenQ.push(ExprToken(s1));
				tokenQ.push(ExprToken(iter->first, iter->second.first, iter->second.second));
			}
			lps = ps + 1;
		}
		++ps;
	}
	if (lps != ps)
		tokenQ.push(ExprToken(string(lps)));
}
string ExprParser::RPN()
{
	string empty = "";
	string result = "";
	if (0 == tokenQ.size())return empty;
	stack<ExprToken> operatorStk;
	std::pair<string, std::pair<int, int> > token;
	while (false == tokenQ.empty())
	{
		token = tokenQ.front().GetToken();
		if (true == tokenQ.front().IsOperand())//if this is an operand
			result.append(token.first);
		else//operator otherwise
		{
			if (")" == token.first)
			{
				while (false == operatorStk.empty())
				{
					if (operatorStk.top().GetLiteral() == "(")
					{
						operatorStk.pop();
						break;
					}
					else if (true == operatorStk.top().IsFunction())
					{
						result.append(operatorStk.top().GetLiteral());
						operatorStk.pop();
						break;
					}
					result.append(operatorStk.top().GetLiteral());
					operatorStk.pop();
				}
			}
			else if (delimiter == token.first)
			{
				while (false == operatorStk.empty() && false == operatorStk.top().IsFunction())
				{
					result.append(operatorStk.top().GetLiteral());
					operatorStk.pop();
				}
			}
			else if ("(" == token.first || true == tokenQ.front().IsFunction())
				operatorStk.push(tokenQ.front());
			else
			{
				while (false == operatorStk.empty() && (token.second.first <= operatorStk.top().GetPriority() && false == operatorStk.top().IsFunction()))
				{
					result.append(operatorStk.top().GetLiteral());
					operatorStk.pop();
				}
				operatorStk.push(tokenQ.front());
			}
		}
		tokenQ.pop();
	}
	while (false == operatorStk.empty())
	{
		result.append(operatorStk.top().GetLiteral());
		operatorStk.pop();
	}
	return result;
}
void testExprParserRPN()
{
	ExprParser p0("A");
	cout << "Expect A :" << p0.RPN() << endl;

	ExprParser p01("A+B,C");
	cout << "Expect AB+C :" << p01.RPN() << endl;

	ExprParser p1("1+2");
	cout << "Expect 12+ :" << p1.RPN() << endl;

	ExprParser p11("1+2-3");
	cout << "Expect 12+3- :" << p11.RPN() << endl;

	ExprParser p111("A+B*C-D");
	cout << "Expect ABC*+D- :" << p111.RPN() << endl;

	ExprParser p2("1+2*3");
	cout << "Expect 123*+ :" << p2.RPN() << endl;

	ExprParser p3("(1+2)*3");
	cout << "Expect 12+3* :" << p3.RPN() << endl;

	ExprParser p4("(A+B*C)/C");
	cout << "Expect ABC*+C/ :" << p4.RPN() << endl;

	ExprParser p5("pow(A,B)*C");
	cout << "Expect ABpowC* :" << p5.RPN() << endl;

	ExprParser p55("C*pow(A,B)");
	cout << "Expect CABpow* :" << p55.RPN() << endl;

	ExprParser p6("(((1+2))*3)");
	cout << "Expect 12+3* :" << p6.RPN() << endl;

	ExprParser p7("((((1+2))*3)");
	cout << "Expect :" << p7.RPN() << endl;

	ExprParser p8("(2)*((3))");
	cout << "Expect 23* :" << p8.RPN() << endl;

	ExprParser p9("pow(A+B,C)");
	cout << "Expect AB+Cpow :" << p9.RPN() << endl;

	ExprParser p10("pow(A+B*C,D)");
	cout << "Expect ABC*+Dpow :" << p10.RPN() << endl;

	ExprParser p12("pow(A+B*C,abs(D))");
	cout << "Expect ABC*+Dabspow :" << p12.RPN() << endl;

	ExprParser p13("pow(A+B*C,abs(D/E))+2*F");
	cout << "Expect ABC*+DE/abspow2F*+ :" << p13.RPN() << endl;
}