#include "pch.h"
#include<iostream>
#include<string>
using namespace std;

class Queue
{
private:

    int size;
    string* queue;
    int head_index;
    int tail_index;

public:

    Queue()
    {
        size = 5;
        queue = new string[size];
        for (int i = 0; i < size; i++)
        {
            queue[i] = "";
        }
        head_index = 0;
        tail_index = 0;
    }

    void resize()
    {
        string* new_queue = new string[size + 5];

        for (int i = 0; i < size; i++)
        {
            new_queue[i] = queue[i];
        }
        for (int i = size; i < size + 5; i++)
        {
            new_queue[i] = "";
        }
        tail_index = size;
        size += 5;
        head_index = (head_index) % size;

        delete[] queue;
        queue = new_queue;
    }

    int get_size() {
        return size;
    }

    bool is_empty()
    {
        return head_index == tail_index;
    }

    void add_element(string value)
    {
        queue[tail_index] = value;
        tail_index = (tail_index + 1) % size;
        //if is full then resize
        if (head_index == tail_index)
        {
            resize();
        }
    }

    string get_element()
    {
        if (!is_empty())
        {
            string el = queue[head_index];
            queue[head_index] = "";
            head_index = (head_index + 1) % size;
            return el;
        }
        else {
            cout << "queue is empty\n";
            return queue[0];
        }
    }

    void show() {
        for (int i = 0; i < size; i++)
            cout << queue[i] << "  ";
        cout << endl;
    }

    ~Queue()
    {
        delete[] queue;
    }
};

TEST(QueueTest, CtorTest1) {
    Queue q;
    EXPECT_EQ("", q.get_element());
}

TEST(QueueTest, CtorTest2) {
    Queue q;
    EXPECT_EQ(5, q.get_size());
}

TEST(QueueTest, Is_empty_Test1 ) {
    Queue q;
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, Is_empty_Test2 ) {
    Queue q;
    q.add_element("jgdf");
    q.add_element("bdjks");
    EXPECT_FALSE(q.is_empty());
}

TEST(QueueTest, Resize_Test ) {
    Queue q;
    q.resize();
    EXPECT_EQ(10,q.get_size());
}

TEST(QueueTest, Get_element_Test1 ) {
    Queue q;
    q.add_element("jku");
    q.add_element("kjhg");
    q.add_element("wer");
    q.add_element("pou");
    EXPECT_EQ("jku",q.get_element());
}

TEST(QueueTest, Get_element_Test2 ) {
    Queue q;
    q.add_element("jku");
    q.add_element("kjhg");
    q.add_element("wer");
    q.add_element("pou");

    q.get_element();
    q.get_element();
    q.get_element();
    EXPECT_EQ("pou",q.get_element());
}

TEST(QueueTest, Get_element_Test3 ) {
    Queue q;
    q.add_element("jku");
    q.add_element("kjhg");
    q.add_element("wer");
    q.add_element("pou");
    q.get_element();
    q.get_element();
    q.get_element();
    q.add_element("jku");
    q.add_element("kjhg");
        
    EXPECT_EQ("pou",q.get_element());
}

