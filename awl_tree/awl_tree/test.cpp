#include "pch.h"
#include<iostream>
using namespace std;

class  Node {
public:
    int value;
    Node* left;
    Node* right;

    Node() {
        value = 0;
        left = NULL;
        right = NULL;
    }
    Node(int v) {
        value = v;
        left = NULL;
        right = NULL;
    }
    ~Node()
    {    }
};
class AVLTree {
public:
    Node* root;
    AVLTree() {
        root = NULL;
    }
    ~AVLTree()
    {    }
    bool is_empty() {
        return root == NULL;
    }
    int get_height(Node* r) {
        if (r == NULL)
            return -1;
        else {
            int left_height = get_height(r->left);
            int right_height = get_height(r->right);

            if (left_height > right_height)
                return (left_height + 1);
            else return (right_height + 1);
        }
    }
    int get_balance_factor(Node* n) {
        if (n == NULL)
            return -1;
        return get_height(n->left) - get_height(n->right);
    }
    Node* right_rotate(Node* y) {
        Node* x = y->left;
        Node* z = x->right;

        x->right = y;
        y->left = z;

        return x;
    }
    Node* left_rotate(Node* x) {
        Node* y = x->right;
        Node* z = y->left;

        y->left = x;
        x->right = z;

        return y;
    }
    Node* insert(Node* r, Node* new_node) {
        if (r == NULL) {
            r = new_node;
            return r;
        }

        if (new_node->value < r->value) {
            r->left = insert(r->left, new_node);
        }
        else if (new_node->value > r->value) {
            r->right = insert(r->right, new_node);
        }
        else {
            throw exception("No duplicate values allowed!");
            return r;
        }

        int balance_factor = get_balance_factor(r);
        // Left Left   
        if (balance_factor > 1 && new_node->value < r->left->value)
            return right_rotate(root);

        // Right Right   
        else if (balance_factor < -1 && new_node->value > r->right->value)
            return left_rotate(root);

        // Left Right   
        else if (balance_factor > 1 && new_node->value > r->left->value) {
            r->left = left_rotate(root->left);
            return right_rotate(r);
        }

        // Right Left   
        else if (balance_factor < -1 && new_node->value < r->right->value) {
            r->right = right_rotate(r->right);
            return left_rotate(r);
        }

        return r;
    }
    Node* min_value_node(Node* node) {
        Node* current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }
    Node* delete_node(Node* r, int v) {
        if (r == NULL) {
            return r;
        }
        else if (v < r->value) {
            r->left = delete_node(r->left, v);
        }
        else if (v > r->value) {
            r->right = delete_node(r->right, v);
        }
        else {
            if (r->left == NULL) {
                Node* temp = r->right;
                delete r;
                return temp;
            }
            else if (r->right == NULL) {
                Node* temp = r->left;
                delete r;
                return temp;
            }
            else {
                Node* temp = min_value_node(r->right);
                r->value = temp->value;
                r->right = delete_node(r->right, temp->value);
            }
        }
        
        int balance_factor = get_balance_factor(r);

        if (balance_factor > 1 && get_balance_factor(r->left) >= 0)
            return right_rotate(r);
        else if (balance_factor > 1 && get_balance_factor(r->left) == -1) {
            r->left = left_rotate(r->left);
            return right_rotate(r);
        }
        else if (balance_factor < -1 && get_balance_factor(r->right) <= 0)
            return left_rotate(r);
        else if (balance_factor < -1 && get_balance_factor(r->right) == 1) {
            r->right = right_rotate(r->right);
            return left_rotate(r);
        }
        return r;
    }
    Node* search(Node* r, int val) {
        if (r == NULL || r->value == val)
            return r;

        else if (val < r->value)
            return search(r->left, val);

        else
            return search(r->right, val);
    }
};

TEST(AVLTreeTest, is_emptyTest) {
    AVLTree tree;
    EXPECT_TRUE(tree.is_empty());
}
TEST(AVLTreeTest, insertTest1) {
    AVLTree tree;
    Node* new_node = new Node(9);
    tree.root = tree.insert(tree.root, new_node);
    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(9, tree.root->value);
} 
TEST(AVLTreeTest, insertTest2) {
    AVLTree tree;
    Node* a = new Node(9);
    Node* b = new Node(10);
    Node* c = new Node(1);
    Node* d = new Node(3);
    tree.root = tree.insert(tree.root, a);
    tree.root = tree.insert(tree.root, b);
    tree.root = tree.insert(tree.root, c);
    tree.root = tree.insert(tree.root, d);
    EXPECT_FALSE(tree.is_empty());
    EXPECT_TRUE(tree.root->value == 9);
}
TEST(AVLTreeTest, searchTest) {
    AVLTree tree;
    Node* a = new Node(9);
    Node* b = new Node(10);
    Node* c = new Node(1);
    Node* d = new Node(3);
    tree.root = tree.insert(tree.root, a);
    tree.root = tree.insert(tree.root, b);
    tree.root = tree.insert(tree.root, c);
    tree.root = tree.insert(tree.root, d);
    EXPECT_TRUE(tree.search(tree.root, 3));
}
TEST(AVLTreeTest, get_hightTest) {
    AVLTree tree;
    AVLTree tree2;
    Node* a = new Node(9);
    Node* b = new Node(10);
    Node* c = new Node(1);
    Node* d = new Node(3);
    //      9
    //     / \
    //    1   10
    //     \
    //      3
    tree.root = tree.insert(tree.root, a);
    tree.root = tree.insert(tree.root, b);
    tree.root = tree.insert(tree.root, c);
    tree.root = tree.insert(tree.root, d);
    EXPECT_EQ(2, tree.get_height(tree.root));
    EXPECT_EQ(-1, tree2.get_height(tree2.root));
}
TEST(AVLTreeTest, get_balance_factorTest) {
    AVLTree tree;
    Node* a = new Node(9);
    Node* b = new Node(10);
    Node* c = new Node(1);
    Node* d = new Node(3);
    //      9
    //     / \
    //    1   10
    //     \
    //      3
    tree.root = tree.insert(tree.root, a);
    tree.root = tree.insert(tree.root, b);
    tree.root = tree.insert(tree.root, c);
    tree.root = tree.insert(tree.root, d);
    EXPECT_EQ(1, tree.get_balance_factor(tree.root));
}
TEST(AVLTreeTest, deleteTest) {
    AVLTree tree;
    Node* a = new Node(9);
    Node* b = new Node(10);
    Node* c = new Node(1);
    Node* d = new Node(3);
    Node* e = new Node(0);
    tree.root = tree.insert(tree.root, a);
    tree.root = tree.insert(tree.root, b);
    tree.root = tree.insert(tree.root, c);
    tree.root = tree.insert(tree.root, d);
    tree.root = tree.insert(tree.root, e);
    tree.delete_node(tree.root, 1);
    EXPECT_FALSE(tree.search(tree.root, 1));
}

