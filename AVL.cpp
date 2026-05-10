#include <iostream>
#include <queue>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1;
    }
};

class AVL {
public:
    Node* root;

    AVL() {
        root = nullptr;
    }

    // Get height
    int getHeight(Node* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    // Get balance factor
    int getBalance(Node* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Right rotation (LL case)
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Left rotation (RR case)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Insert
    Node* insert(Node* node, int key) {

        // Normal BST insert
        if (node == nullptr)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;

        // Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Get balance
        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && key < node->left->data)
            return rightRotate(node);

        // RR Case
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

        // LR Case
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Find minimum
    Node* minValue(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Delete
    Node* deleteNode(Node* node, int key) {

        if (node == nullptr)
            return node;

        // BST delete
        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            // one or zero child
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                // two children
                Node* temp = minValue(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr)
            return node;

        // Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        // LL
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        // LR
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RR
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        // RL
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Search
    Node* search(Node* node, int key) {
        if (node == nullptr || node->data == key)
            return node;

        if (key > node->data)
            return search(node->right, key);

        return search(node->left, key);
    }

    // DFS Traversals
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    // BFS
    void bfs(Node* node) {
        if (node == nullptr) return;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
    }
};

int main() {

    AVL tree;

    int keys[] = {10, 20, 30, 25, 28, 27, 5, 4, 3};


    for (int i = 0; i < 9; i++) {
        tree.root = tree.insert(tree.root, keys[i]);
    }

    cout << "Inorder: ";
    tree.inorder(tree.root);
    cout << endl;



    return 0;
}