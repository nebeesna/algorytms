#include "pch.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;
class HashTable
{
private:

	struct Row
	{
		string key;
		string content;
	};

	vector<Row> r{ 40 };

public:
	HashTable()
	{

	}

	~HashTable()
	{

	}

	bool Find(string key)
	{
		bool found = false;
		for (int i = 0; i < r.size(); i++) {
			if (r[i].key == key)
				found = true;
		}
		return found;
	}

	string Hash_find(string key) {
		int h = hashing(key);
		if (r[h].key == key)
			return r[h].content;
		else if (r[h].key != key) {
			while (r[h].key != key) {
				h = h + 3;
				if (h == 37) h = 0;
				if (h == 38) h = 1;
				if (h == 39) h = 2;
			}
			return r[h].content;
		}
	}

	void Add(string key, string content)
	{
		if (Find(key)) {
			cout << "Key is existed\n";
		}
		else {
			int h = hashing(key);
			for (int i = 0; i < r.size(); i++)
			{
				if (i == h && !is_filled(h))
				{
					r[i].key = key;
					r[i].content = content;
					break;
				}
				else if (i == h && is_filled(h)) {
					while (is_filled(h)) {
						h = h + 3;
						if (h == 37) h = 0;
						if (h == 38) h = 1;
						if (h == 39) h = 2;
					}
					r[h].key = key;
					r[h].content = content;
					break;
				}
			}
		}
	}

	void Delete(string key)
	{
		if (!Find(key))
			cout << "Table has not this key\n";
		else if (Find(key)) {
			for (int i = 0; i < r.size(); i++) {
				if (r[i].key == key) {
					r[i].key = "";
					r[i].content = "";
				}
			}
		}
	}

	void show() {
		for (int i = 0; i < r.size(); i++) {
			if (r[i].key != "")
				cout << r[i].key << "  " << r[i].content << endl;
		}
	}

	string get_content(string key) {
		for (int i = 0; i < r.size(); i++) {
			if (r[i].key == key)
				return r[i].content;
		}
	}

	int hashing(string s) {
		return ((int(s[0]) * int(s[1]) / 100) - 42);
	}

	bool is_filled(int hash) {
		if (r[hash].key != "")
			return true;
		else return false;
	}

	int get_size() {
		return r.size();
	}
};



TEST(Hash_table_test, Add_test1) {
	HashTable t;
	t.Add("AB", "content");
	EXPECT_EQ("content", t.get_content("AB"));
}


TEST(Hash_table_test, Add_test2) {
	HashTable t;
	t.Add("AB", "content");
	EXPECT_TRUE(t.Find("AB"));
}

TEST(Hash_table_test, Add_test3) {
	HashTable t;
	t.Add("AB", "content");
	t.Add("AB", "copy");
	
	EXPECT_EQ("content", t.get_content("AB"));
}

TEST(Hash_table_test, Add_test4) {
	HashTable t;
	t.Add("AB", "poiu");
	t.Add("AA", "lkjh");
	
	EXPECT_TRUE(t.Find("AA"));
}

TEST(Hash_table_test, Hash_find_test) {
	HashTable t;
	t.Add("AB", "poiu");
	t.Add("AA", "lkjh");

	EXPECT_EQ("poiu",t.Hash_find("AB"));
}

TEST(Hash_table_test, hashing_test) {
	HashTable t;
	EXPECT_EQ(0, t.hashing("AB"));
}

TEST(Hash_table_test, get_size_test) {
	HashTable t;
	EXPECT_EQ(40, t.get_size());
}

TEST(Hast_table_test, Find_test) {
	HashTable t;
	t.Add("CC", "jko");
	EXPECT_TRUE(t.Find("CC"));
}

TEST(Hast_table_test, is_filled_test) {
	HashTable t;
	t.Add("CC", "jko");
	int h = t.hashing("CC");
	EXPECT_TRUE(t.is_filled(h));
}

TEST(Hast_table_test, Delete_test1) {
	HashTable t;
	t.Add("JK", "khg");
	t.Add("ER", "lgfh");
	t.Add("BN", "yui");
	t.Add("IO", "qdn");
	t.Delete("BN");
	EXPECT_FALSE(t.Find("BN"));
}

TEST(Hast_table_test, Delete_test2) {
	HashTable t;
	t.Add("JK", "khg");
	t.Add("ER", "lgfh");
	t.Add("BN", "yui");
	t.Add("IO", "qdn");
	t.Delete("BN");
	EXPECT_EQ(40,t.get_size());
}



