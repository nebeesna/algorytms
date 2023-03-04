#include "pch.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;
class Table
{
private:
	struct Row
	{
		int key;
		string content;
	};

	vector<Row> r;

public:
	Table()
	{
	}

	Table(int key, string content)
	{
		Row temp;
		temp.key = key;
		temp.content = content;
		r.push_back(temp);
	}

	~Table()
	{

	}

	bool Find(int key)
	{
		bool found = false;
		for (int i = 0; i < r.size(); i++) {
			if (r[i].key == key)
				found = true;
		}
		return found;
	}

	void Add(int key, string content)
	{
		if (Find(key)) {
			cout << "Key is existed\n";
		}
		else {
			Row temp;
			temp.key = key;
			temp.content = content;
			r.push_back(temp);
			//sorting for keys
			for (int i = 0; i < r.size(); i++) {
				for (int j = 0; j < r.size(); j++) {
					if (r[i].key < r[j].key) {
						swap(r[i], r[j]);
					}
				}
			}
		}
	}

	void Delete(int key)
	{
		bool found = false;
		if (r.size() == 0) {
			cout << "Table is empty\n";
		}
		else if (!Find(key))
			cout << "Table has not this key\n";
		else if (Find(key)) {
			for (int i = 0; i < r.size(); i++) {
				if (r[i].key == key) {
					r.erase(r.begin() + i);
				}
			}
		}
	}

	void show() {
		for (int i = 0; i < r.size(); i++) {
			cout << r[i].key << "  " << r[i].content << endl;
		}
	}

	int get_size() {
		return r.size();
	}

	string get_content(int key) {
		for (int i = 0; i < r.size(); i++) {
			if (r[i].key == key)
				return r[i].content;
		}
	}
};

TEST(Table_test, Delete_test1) {
	Table t;
	t.Add(3, "fgh");
	t.Add(4, "fff");
	t.Add(1, "dj");
	t.Delete(3);
	EXPECT_FALSE(t.Find(3));
}

TEST(Table_test, Delete_test2) {
	Table t;
	t.Add(3, "fgh");
	t.Add(4, "fff");
	t.Add(1, "dj");
	t.Delete(6);
	EXPECT_EQ(3, t.get_size());
}

TEST(Table_test, Add_test1) {
	Table t;
	t.Add(3, "fgh");
	t.Add(4, "fff");
	t.Add(1, "dj");

	EXPECT_TRUE(t.Find(3));
}

TEST(Table_test, Add_test2) {
	Table t;
	t.Add(3, "fgh");
	t.Add(4, "fff");
	t.Add(1, "dj");

	t.Add(1, "jjj");
	EXPECT_EQ(3, t.get_size());
}

TEST(Table_test, ctor_add_test) {
	Table t(2, "hh");
	EXPECT_TRUE(t.Find(2));
}

TEST(Table_test, show_test) {
	Table t;
	t.Add(3, "fgh");
	t.Add(4, "fff");
	t.Add(1, "dj");
	t.show();
}

TEST(Table_test, get_content_test) {
	Table t;
	t.Add(3, "fgh");
	t.Add(4, "fff");
	t.Add(1, "dj");
	EXPECT_EQ("fff", t.get_content(4));
}