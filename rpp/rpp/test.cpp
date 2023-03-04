#include "pch.h"
#include<iostream>
#include<stack>
using namespace std;

int set_priority(char s)
{
	if (s == '+' || s == '-')
		return 1;
	else if (s == '*' || s == '/')
		return 2;
	else if (s == '^')
		return 3;
	else return 0;
}

string to_postfix(const string s)
{
	stack<char> stack;
	string result = "";

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(')
			stack.push(s[i]);
		else if (s[i] == ')')
		{
			while (!stack.empty() && stack.top() != '(')
			{
				result += stack.top();
				stack.pop();
			}
			if (!stack.empty() && stack.top() == '(')
				stack.pop();
		}
		else
		{
			if (set_priority(s[i]) == 0)
				result += s[i];
			else
			{
				if (stack.empty())
					stack.push(s[i]);
				else
				{
					while (stack.top() != '(' && set_priority(s[i]) <= set_priority(stack.top()) && !stack.empty())
					{
						result += stack.top();
						stack.pop();
					}
					stack.push(s[i]);
				}
			}
		}
	}
	while (!stack.empty())
	{
		result += stack.top();
		stack.pop();
	}
	return result;
}

double calculate(double a, double b, char s) 
{
	if (s == '+')
		return a+b;
	else if (s == '-')
		return a-b;
	else if (s == '*')
		return a*b;
	else if (s == '/')
		return a/b;
	else if (s == '^')
		return pow(a,b);
}

double postfix_calculate(string s) 
{
	stack<double> stack;
	s = to_postfix(s);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9')
			stack.push(s[i]);
		else
		{
			int a, b;
			b = stack.top();
			stack.pop();
			a = stack.top();
			stack.pop();
			stack.push(calculate(a, b, s[i]));
		}
	}
	return stack.top();
}

TEST(Reverse_Polish_Note_Test, Prioriry_Test) {
	char ch = '*';
  EXPECT_EQ(2, set_priority(ch));
}

TEST(Reverse_Polish_Note_Test, Calculate_Test1) {
	char ch = '+';
	int a = 3, b = 4;
  EXPECT_EQ(7, calculate(a,b,ch));
}

TEST(Reverse_Polish_Note_Test, Calculate_Test2) {
	char ch = '/';
	int a = 3, b = 4;
  EXPECT_EQ(0.75, calculate(a,b,ch));
}

TEST(Reverse_Polish_Note_Test, Postfix_Tranform_Test) {
	string s, r;
	s = "(1 + 2) / (5 - 3)";
	r = "1  2+  5  3-/";
	EXPECT_EQ(r, to_postfix(s));
}

TEST(Reverse_Polish_Note_Test, Postfix_Calculate_Test1) {
	string s;
	s = "4+5-6";
	EXPECT_EQ(3, postfix_calculate(s));
}

TEST(Reverse_Polish_Note_Test, Postfix_Calculate_Test2) {
	string s;
	s = "(1+8)/4";
	EXPECT_EQ(2, postfix_calculate(s));
}

TEST(Reverse_Polish_Note_Test, Postfix_Calculate_Test3) {
	string s;
	s = "(5-3)^4";
	EXPECT_EQ(16, postfix_calculate(s));
}