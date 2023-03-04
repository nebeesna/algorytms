#include "pch.h"
#include<iostream>
#include<string>
using namespace std;

class Queue_with_priority
{
private:

    struct element {
        int value;
        int priority;
    };

    int size;
    element* queue;
    int head_index;
    int tail_index;

public:

    Queue_with_priority()
    {
        size = 5;
        queue = new element[size];
        for (int i = 0; i < size; i++)
        {
            queue[i].value = 0;
            queue[i].priority = 10000;
        }
        head_index = 0;
        tail_index = 0;
    }

    void resize()
    {
        element* new_queue = new element[size + 5];

        for (int i = 0; i < size; i++)
        {
            new_queue[i].value = queue[i].value;
            new_queue[i].priority = queue[i].priority;
        }
        for (int j = size; j < size + 5; j++)
        {
            new_queue[j].value = 0;
            new_queue[j].priority = 10000;
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

    void add_element(int value, int priority)
    {
        queue[tail_index].value = value;
        queue[tail_index].priority = priority;
        tail_index = (tail_index + 1) % size;

        //if is full then resize
        if (head_index == tail_index)
        {
            resize();
        }
        //sorting by priorities
        bool sorted = false;
        while (!sorted) {
            sorted = true;
            for (int i = 1; i < size - 1; i += 2)  // Odd
            {
                if (queue[i].priority > queue[i + 1].priority) {
                    swap(queue[i], queue[i + 1]);
                    sorted = false;
                }
            }

            for (int i = 0; i < size - 1; i += 2)  // Even
            {
                if (queue[i].priority > queue[i + 1].priority) {
                    swap(queue[i], queue[i + 1]);
                    sorted = false;
                }
            }
        }

    }


    int get_element()
    {
        if (!is_empty())
        {
            int el = queue[head_index].value;
            queue[head_index].value = 0;
            queue[head_index].priority = 10000;
            head_index = (head_index + 1) % size;
            return el;
        }
        else {
            cout << "queue is empty\n";
            return 0;
        }
    }

    void show() {
        for (int i = 0; i < size; i++)
            cout << queue[i].priority << "\t" << queue[i].value << endl;

        cout << endl;
    }

    ~Queue_with_priority()
    {
        delete[] queue;
    }
};


TEST(Queue_with_priority_Test, AddTest1) {
    Queue_with_priority q;
    q.add_element(18, 2);
    q.add_element(4, 1);
    q.add_element(56, 2);
    EXPECT_EQ(4, q.get_element());
};

TEST(Queue_with_priority_Test, AddTest2) {
    Queue_with_priority q;
    q.add_element(18, 2);
    q.add_element(7, 1);
    q.add_element(56, 2);
    q.add_element(5, 3);
    q.add_element(67, 1);
    q.add_element(99, 2);
    EXPECT_EQ(7, q.get_element());
}
TEST(Queue_with_priorirty_Test, Get_Test1) {
    Queue_with_priority q;
    q.add_element(18, 2);
    q.add_element(7, 1);
    q.add_element(56, 2);
    q.add_element(4, 1);
    q.add_element(71, 1);
    q.get_element();
    q.get_element();
    q.get_element();
    q.show();
    EXPECT_EQ(18, q.get_element());
}
TEST(Queue_with_priorirty_Test, Get_Test2) {
    Queue_with_priority q;
    q.add_element(18, 2);
    q.add_element(7, 1);
    q.add_element(56, 3);
    cout << "--------\n";
    q.show();
    q.add_element(4, 1);
    q.add_element(71, 2);
    q.add_element(88, 1);
    q.add_element(3, 2);
    cout << "--------\n";
    q.show();
    q.get_element();
    q.get_element();
    q.get_element();
    cout << "--------\n";
    q.show();
    EXPECT_EQ(18, q.get_element());
}
TEST(Queue_with_priorirty_Test, Ctor_Test1) {
    Queue_with_priority q;
    EXPECT_TRUE(q.is_empty());
}
TEST(Queue_with_priorirty_Test, Ctor_Test2) {
    Queue_with_priority q;
    EXPECT_EQ(5, q.get_size());
}
TEST(Queue_with_priorirty_Test, Resize_Test) {
    Queue_with_priority q;
    q.resize();
    EXPECT_EQ(10, q.get_size());
}
