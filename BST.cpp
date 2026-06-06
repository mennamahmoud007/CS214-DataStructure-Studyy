#include <iostream>
#include <queue>
using namespace std;

// Node structure with constructor
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left =right = nullptr;
    }
};
/*template <class T>
class BSTNode {
private:
    T key; 
BSTNode* left;
BSTNode* right;
  public:
BSTNode () {left = right = 0;}
BSTNode (T& el, BSTNode* l = 0, BSTNode* r = 0){
       key   = el;
       left  = l;
       right = r;
    }
    BSTNode* getLeft  {return left;}
    BSTNode* getRight {return right;}
};   
template <class T>
class BST {
protected:
BSTNode<T>* root
public:
BST ()         {root = 0;}
void clear()   {root = 0;}
bool isEmpty() {retun root == 0;}
T* search (T& el) {
   BSTNode<T>* p = root;
   while (p != 0) 
          if (el == p->getKey())
             return &p->getKey();
     else if (el < p->getKey())
             p =  getLeft();
          else p = getRight();
};
 */

class BST {
public:
    Node* root;

    BST() {
        root = nullptr;
    }
    //final questions i think
    int height(Node* root) { 
        if (root == nullptr)
            return 0; // height of empty tree is 0

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        return max(leftHeight, rightHeight) + 1; // height of a node is max height of its children + 1
    }
    int countNodes(Node* root) {
        if (root == nullptr)
            return 0;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    int countLeaves(Node* root) {
        if (root == nullptr)
            return 0;

        if (root->left == nullptr && root->right == nullptr)
            return 1;

        return countLeaves(root->left) + countLeaves(root->right);
    }
    int countInternal(Node* root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr))
            return 0;

        return 1 + countInternal(root->left) + countInternal(root->right);
    }

    // Insert
    Node* insert(Node* node, int data) { //worset case o(n) when tree is skewed, average and best case o(log n) when tree is balanced
        if (node == nullptr)
            return new Node(data);

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);

        return node;
    }

    Node* insertIterative(Node* node, int data) { //o(n) when tree is skewed, o(log n) when tree is balanced
        if (node == nullptr)
            return new Node(data);

        Node* parent = nullptr;
        Node* current = node;

        while (current != nullptr) {
            parent = current;
            if (data < current->data)
                current = current->left;
            else if (data > current->data)
                current = current->right;
            else
                return node; // duplicate data, do not insert
        }

        if (data < parent->data)
            parent->left = new Node(data);
        else
            parent->right = new Node(data);

        return node;
    }

    // Find minimum value
    Node* minValue(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;

        return node;
    }
    // Find maximum value
    Node* maxValue(Node* node) {
        while (node && node->right != nullptr)
            node = node->right;

        return node;
    }
    // Find successor
    Node* successor(Node* node) { // successor is minimum of right subtree
        if (node->right != nullptr)  // if right subtree exists, successor is minimum of right subtree
            return minValue(node->right);
        // if right subtree does not exist, successor is the lowest
        // ancestor(greater than node) of node whose left child is also an ancestor of node
        Node* succ = nullptr;
        Node* ancestor = root;
        while (ancestor != node) {
            if (node->data < ancestor->data) { //who is the lowest ancestor of node whose left child is also an ancestor of node?
                // the one that is greater than node and is the lowest among all ancestors that are greater than node
                succ = ancestor; // update successor to current ancestor before going left
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }
        return succ;
    }

    // Delete node
    Node* deleteNode(Node* node, int key) {

        if (node == nullptr)
            return nullptr;

        // search for the node
        if (key < node->data)
            node->left = deleteNode(node->left, key);

        else if (key > node->data)
            node->right = deleteNode(node->right, key);

        else {
            // Case 1: no child
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: one child
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: two children
            Node* temp = minValue(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }
//     Node* deleteNode(Node* root, int key) {
//     if (root == NULL) return NULL;

//     if (key < root->data)
//         root->left = deleteNode(root->left, key);

//     else if (key > root->data)
//         root->right = deleteNode(root->right, key);

//     else {
//         // case 1 & 2
//         if (root->left == NULL)
//             return root->right;

//         else if (root->right == NULL)
//             return root->left;

//         // case 3
//         Node* temp = root->right;
//         while (temp->left != NULL)
//             temp = temp->left;

//         root->data = temp->data;
//         root->right = deleteNode(root->right, temp->data);
//     }

//     return root;
// }
//--------------------------------
     //breadth first 
        
        // void breadthFirst(Node *root) {
        // Queue<Node<T>*> queue;
        // if (p = 0) {
        // }
        // queue.enqueue(p);
        // while (!queue.empty()) {
        // }
        // p = queue.dequeue();
        // visit(p);
        // if (p->left != 0)

        // queue.enqueue (p->left);
        // if (p->right != 0)
        // queue.enqueue (p->right);
        // }
//---------------------------------------------------------------------------------------------------------
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
    void bfs(Node* node) { //o(n) //print level by level from left to right
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
    Node*recursiveSearch(Node* node, int key) { //o(h) where h is the height of the tree
        if (node == nullptr || node->data == key)
            return node;
        if (key < node->data)
            return recursiveSearch(node->left, key);
        return recursiveSearch(node->right, key);
    }
    bool searchIterative(Node* node, int key) { //o(h) where h is the height of the tree
        while (node != nullptr) {
            if (node->data == key)
                return true;
            else if (key < node->data)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }
};

int main() {

    BST tree;

    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 70);
    tree.root = tree.insert(tree.root, 60);
    tree.root = tree.insert(tree.root, 80);

    cout << "Inorder: ";
    tree.inorder(tree.root);
    cout << endl;

    cout << "BFS: ";
    tree.bfs(tree.root);
    cout << endl;

    // Delete node
    tree.root = tree.deleteNode(tree.root, 20);

    cout << "After deleting 20\n";

    cout << "Inorder: ";
    tree.inorder(tree.root);
    cout << endl;

    cout << "BFS: ";
    tree.bfs(tree.root);
    cout << endl;

    return 0;
}