#include "pch.h"
#include <iostream>
using namespace std;

class Set
{
private:
	char s[4];
public:
	Set() 
	{
		for (int i = 0; i < 4; i++)
		{
			s[i] = 0;
		}
	}
	Set(const Set& a) 
	{
		for (int i = 0; i < 4; i++)
		{
			s[i] = a.s[i];
		}
	}
	~Set() {	}

	int get_position(char symbol) 
	{
		return symbol - 'a';
	}

	void add(char symbol) 
	{
		int position = get_position(symbol);
		s[position / 8] |= (1 << (position % 8));
	}

	bool is_in_set(char symbol) 
	{
		int position = get_position(symbol);
		return s[position / 8] & (1 << (position % 8));
	}

	void remove(char symbol) //delete
	{ 
		int position = get_position(symbol);
		s[position / 8] &= ~(1 << (position % 8));
	}

	void clear()
	{
		for (int i = 0; i < 4; i++)
		{
			s[i] = 0;
		}
	}

	Set unite(const Set& set1, const Set& set2) //об'Їднанн€
	{
		Set res(set1);
		for (int i = 0; i < 4; i++)
		{
			res.s[i] |= set2.s[i];
		}
		return res;
	}

	Set intersection(const Set& set1, const Set& set2) { //перетин
		Set res(set1);
		for (int i = 0; i < 4; i++)
		{
			res.s[i] &= set2.s[i];
		}
		return res;
	}

	Set difference(const Set& set1,const Set& set2) { //р≥зниц€
		Set res(set1);
		for (int i = 0; i < 4; i++)
		{
			res.s[i] &= !set1.s[i];
		}
		return res;
	}
	
	bool operator ==(const Set& s) {
		bool res = false;
		for (int i = 0; i < 4; i++)
		{
			if (this->s[i] == s.s[i]) {
				res = true;
			}
			else res = false;
		}
		return res;
	}
};
TEST(Binary_Set_test, get_position_test) {
	Set a;
	EXPECT_EQ(3, a.get_position('d'));
}
TEST(Binary_Set_test, add_test) {
	Set s;
	s.add('m');
	EXPECT_TRUE(s.is_in_set('m'));
}
TEST(Binary_Set_test, remove_test) {
	Set s;
	s.add('v');
	s.remove('v');
	EXPECT_FALSE(s.is_in_set('v'));
}
TEST(Binary_Set_test, unite_test) {
	Set a, b, res;
	a.add('a');
	a.add('v');

	b.add('w');
	b.add('r');
	b.add('h');

	res.unite(a, b);

	a.add('w');
	a.add('r');
	a.add('h');
	EXPECT_TRUE(res == a);
}
TEST(Binary_Set_test, intresection_test) {
	Set a, b, res;
	a.add('a');
	a.add('v');

	b.add('a');
	b.add('r');
	b.add('h');

	res.intersection(a, b);
	a.clear();
	a.add('a');
	EXPECT_TRUE(res == a);
}
TEST(Binary_Set_test, differnce_test) {
	Set a, b, res;
	a.add('a');
	a.add('v');
	a.add('f');
	a.add('r');

	b.add('a');
	b.add('r');
	b.add('h');

	res.difference(a, b);
	a.clear();
	a.add('v');
	a.add('f');
	a.add('h');
	EXPECT_TRUE(res == a);
}