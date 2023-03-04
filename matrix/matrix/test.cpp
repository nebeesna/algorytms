#include "pch.h"
#include <iostream>
using namespace std;
struct Element
{
    int row;
    int col;
    int value;
    Element* up;
    Element* left;
    Element()
    {
        value = 0;
        row = 0;
        col = 0;
        up = left = nullptr;
    }
    ~Element() {    }
};
class SparseMatrix
{
private:
    
    static const int rows_quantity = 5;
    static const int columns_quantity = 5;
    Element rows[rows_quantity + 1];
    Element cols[columns_quantity + 1];

public:
    SparseMatrix()
    {
        for (int i = 0; i < rows_quantity; i++)
        {
            rows[i].left = &rows[i];
        }

        for (int j = 0; j < columns_quantity; j++)
        {
            cols[j].up = &cols[j];
        }
    }
    ~SparseMatrix() {    }
    Element* get_prev_by_row(int row_number, int column_number)
    {
        Element* current = &rows[row_number];
        while (current->left->col > column_number)
        {
            current = current->left;
        }
        return current;
    };

    Element* get_prev_by_column(int row_number, int column_number)
    {
        if (row_number < rows_quantity && column_number < columns_quantity) {
            Element* current = &cols[column_number];
            while (current->row > row_number)
            {
                current = current->up;
            }
            return current;
        }
        else return &cols[0];
    };

    void remove_element(int row_number, int column_number)
    {
        Element* prev_by_row = get_prev_by_row(row_number, column_number);
        Element* prev_by_col = get_prev_by_column(row_number, column_number);
        Element* current = prev_by_row->left;

        prev_by_row->left = current->left;
        prev_by_col->up = current->up;
        delete current;
    }

    void add_element(int value, int row_number, int column_number)
    {
        Element* prev_by_row = get_prev_by_row(row_number, column_number);
        Element* prev_by_col = get_prev_by_column(row_number, column_number);
        Element* new_element = new Element();
        new_element->row = row_number;
        new_element->col = column_number;
        new_element->value = value;

        new_element->left = prev_by_row->left;
        prev_by_row->left = new_element;
        new_element->up = prev_by_col->up;
        prev_by_col->up = new_element;
    }

    int get_element(int row_number, int column_number)
    {
        Element* prev_by_row = get_prev_by_row(row_number, column_number);
        Element* result = prev_by_row->left;

        return result->value;
    }

    SparseMatrix operator +(SparseMatrix& other) {
        SparseMatrix matr;
        int value;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                value = this->get_element(i, j) + other.get_element(i, j);
                matr.add_element(value, i, j);
            }
        }
        return matr;
    }

    friend bool operator==(SparseMatrix& other, SparseMatrix& another) {
        bool result = false;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (other.get_element(i, j) == another.get_element(i, j)) {
                    result = true;
                }
                else {
                    result = false;
                }
            }
        }
        return result;
    }
};
TEST(SparseMatrix, remove_test) {
    SparseMatrix matr, res;
    matr.add_element(9, 1, 3);
    matr.add_element(11, 3, 2);
    matr.add_element(13, 4, 4);

    matr.remove_element(3, 2);

    res.add_element(9, 1, 3);
    res.add_element(13, 4, 4);
    EXPECT_TRUE(res == matr);
}
TEST(SparseMatrix, operator_plus_test) {
    SparseMatrix matr, matr1, matr2, res;
    matr1.add_element(100, 0, 1);
    matr1.add_element(10, 2, 3);
    matr1.add_element(15, 3, 4);

    matr2.add_element(100, 0, 1);
    matr2.add_element(10, 2, 3);
    matr2.add_element(15, 3, 4);

    matr = matr1 + matr2;
    
    res.add_element(200, 0, 1);
    res.add_element(20, 2, 3);
    res.add_element(30, 3, 4);
    EXPECT_TRUE(res == matr);
}
TEST(SparseMatrix, get_element_test) {
    SparseMatrix matr;
    matr.add_element(8, 1, 3);
    EXPECT_EQ(8, matr.get_element(1, 3));
}

