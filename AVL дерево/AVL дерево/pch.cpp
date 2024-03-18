//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to find the minimum node in the AVL tree
Node* findMinNode(Node* root) {
    if (root == nullptr)
        return nullptr;
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// Function to find the maximum node in the AVL tree
Node* findMaxNode(Node* root) {
    if (root == nullptr)
        return nullptr;
    while (root->right != nullptr)
        root = root->right;
    return root;
}

// Function to search for a node with a given key in the AVL tree
Node* searchNode(Node* root, int key) {
    if (root == nullptr || root->key == key)
        return root;
    if (key < root->key)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}
void updateHeight(Node* node) {
    if (node == nullptr)
        return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* insertNode(Node* root, int key) {
    if (root == nullptr)
        return newNode(key);
    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    else
        return root;
    updateHeight(root);
    int balance = getBalance(root);
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            root = temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == nullptr)
        return root;
    updateHeight(root);
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << root->key << " ";
        inOrderTraversal(root->right);
    }
}

bool isAVLTree(Node* root) {
    if (root == nullptr)
        return true;
    int balance = getBalance(root);
    if (balance < -1 || balance > 1)
        return false;
    return isAVLTree(root->left) && isAVLTree(root->right);
}

void printTree(Node* root, int level = 0) {
    if (root == nullptr)
        return;

    printTree(root->right, level + 1);

    if (root->right != nullptr || root->left != nullptr) {
        for (int i = 0; i < level; i++)
            cout << "    ";
        cout << " /";
        if (root->right != nullptr)
            cout << "  ";
        if (root->left != nullptr)
            cout << "\\";
        cout << endl;
    }

    for (int i = 0; i < level; i++)
        cout << "   ";
    cout << root->key << endl;

    printTree(root->left, level + 1);
}


int main() {
    Node* root = nullptr;

    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    cout << "AVL tree after inserting nodes:\n";
    printTree(root);
    cout << endl;

    root = insertNode(root, 45);
    root = insertNode(root, 75);
    root = insertNode(root, 56);
    root = deleteNode(root, 30);

    cout << "AVL tree after deleting a node:\n";
    printTree(root);
    cout << endl;

    if (isAVLTree(root))
        cout << "The tree is an AVL tree." << endl;
    else
        cout << "The tree is not an AVL tree." << endl;

    return 0;
}





///////////////////////////////////////TEST//////////////////////////////////



// Test case for insertNode function
TEST(AVLTreeTest, InsertNode) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);

    // Check if the tree is balanced
    EXPECT_TRUE(isAVLTree(root));
}

// Test case for deleteNode function
TEST(AVLTreeTest, DeleteNode) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);

    root = deleteNode(root, 20);

    // Check if the tree is still balanced
    EXPECT_TRUE(isAVLTree(root));

}

// Test case for isAVLTree function
TEST(AVLTreeTest, IsAVLTree) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);

    // Check if the tree is recognized as an AVL tree
    EXPECT_TRUE(isAVLTree(root));
}

// Test case for inOrderTraversal function
TEST(AVLTreeTest, InOrderTraversal) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);

    // Create a stream to capture the output
    testing::internal::CaptureStdout();
    inOrderTraversal(root);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "10 20 30 40 ");
}

// Test case for printTree function
TEST(AVLTreeTest, PrintTree) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);

    // Create a stream to capture the output
    testing::internal::CaptureStdout();
    printTree(root);
    string output = testing::internal::GetCapturedStdout();

    // Example assertion: Check if the output contains the expected pattern
    EXPECT_NE(output.find("10"), string::npos);
    EXPECT_NE(output.find("20"), string::npos);
    EXPECT_NE(output.find("30"), string::npos);
    EXPECT_NE(output.find("40"), string::npos);
}

// Test case for findMinNode function
TEST(AVLTreeTest, FindMinNode) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    Node* minNode = findMinNode(root);

    EXPECT_EQ(minNode->key, 10);
}

// Test case for findMaxNode function
TEST(AVLTreeTest, FindMaxNode) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);

    Node* maxNode = findMaxNode(root);

    EXPECT_EQ(maxNode->key, 40);
}

// Test case for searchNode function
TEST(AVLTreeTest, SearchNode) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);

    Node* foundNode = searchNode(root, 20);

    EXPECT_EQ(foundNode->key, 20);
}

// Test case for getHeight function
TEST(AVLTreeTest, GetHeight) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    int height = getHeight(root);

    EXPECT_EQ(height, 3);
}

// Test case for getBalanceFactor function
TEST(AVLTreeTest, GetBalanceFactor) {
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    int balanceFactor = getBalance(root);

    EXPECT_EQ(balanceFactor, -1);
}