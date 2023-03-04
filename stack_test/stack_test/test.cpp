#include<iostream>
#include "pch.h"
using namespace std;
class Stack
{
private:
    int top;
    int size;
    int* arr;

public:
    Stack()
    {
        top = 0;
        size = 10;
        arr = new int[size];
    }
    ~Stack()
    {
        delete[] arr;
    }

    void push(int value)
    {
        arr[++top] = value;
    }
    int peek() {
        if (!isEmpty()) {
            return arr[top];
        }
    }
    int pop()
    {
        if (!isEmpty())
        {
            peek();
            return arr[top--];
        }
        if (isEmpty())
        {
            cout << "Stack is empty. eror\n";
        }

    }
    bool isEmpty()
    {
        return top == 0;
    }
    int getSize()
    {
        return size;
    }

};

TEST(Stack_Test_STL, Starts_Empty) {
    Stack st;
    EXPECT_EQ(10, st.getSize());
}

TEST(Stack_Test_STL, Empty_Test) {
    Stack st;
    st.push(1);
    st.pop();
    EXPECT_TRUE(st.isEmpty());
}

TEST(Stack_Test_STL, Pop_Test) {
    Stack st;
    st.push(2);
    st.push(12);
    st.push(6);
    st.push(7);
    st.pop();
    EXPECT_EQ(6, st.peek());
}

TEST(Stack_Test_STL, Push_Test) {
    Stack st;
    st.push(2);
    st.push(12);
    st.push(6);
    st.push(7);

    EXPECT_EQ(7, st.peek());
}

TEST(Stack_Test_STL, Peek_Test) {
    Stack st;
    st.push(2);
    st.push(12);
    st.push(6);
    st.push(7);

    EXPECT_EQ(7, st.peek());
}
