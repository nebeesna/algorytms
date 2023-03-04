#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

string markow(string word, string s1, string s2) { // s1 -> s2
	int w = word.length(), n1 = s1.length(), n2 = s2.length();
	string temp, res = word;
	for (int i = 0; i < w; i++)
	{
		temp = "";
		if (res[i] == s1[0]) {
			if (n1 + i <= w) {
				for (int j = i; j < n1 + i; j++)
					temp += res[j];
			}
			if (temp == s1) {
				temp = "";
				for (int j = 0; j < i; j++)
				{
					temp += res[j];
				}
				temp += s2;
				
				for (int j = i + n1; j < w; j++)
				{
					temp += res[j];
				}
				res = temp;
				w += (n2 - n1);
			}
		}
	}
	return	res;
}


TEST(AlgoritmMarkowaTest, Test1) {
	string s = "His name is Yagami Light";
	string s1 = "Yagami Light";
	string s2 = "Kira";
	EXPECT_EQ("His name is Kira", markow(s,s1,s2));
}
TEST(AlgoritmMarkowaTest, Test2) {
	string s = "ababagalamaga";
	string s1 = "a";
	string s2 = "w";
	EXPECT_EQ("wbwbwgwlwmwgw", markow(s,s1,s2));
}
TEST(AlgoritmMarkowaTest, Test3) {
	string s = "ababagalamaga";
	string s1 = "a";
	string s2 = "ee";
	EXPECT_EQ("eebeebeegeeleemeegee", markow(s,s1,s2));
}
TEST(AlgoritmMarkowaTest, Test4) {
	string s = "nice";
	string s1 = "nice";
	string s2 = "awful";
	EXPECT_EQ("awful", markow(s,s1,s2));
}
TEST(AlgoritmMarkowaTest, Test5) {
	string s = "avvvvvbv";
	string s1 = "b";
	string s2 = "boo";
	EXPECT_EQ("avvvvvboov", markow(s,s1,s2));
}