#include <iostream>
#include <string>

using namespace std;

template <class T>
class Node{
public:
    T data; // can save a char
    Node* next;
    Node(T i){
        data = i;
        next = nullptr;
    }
};

class TreeNode{
public:
    int val; // can save a char
    char c; // color
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : c('r'), parent(nullptr), left(nullptr), right(nullptr) {}
    TreeNode(int i) : val(i), c('r'), parent(nullptr), left(nullptr), right(nullptr) {}
};

class LinkedList{
private:
    Node<int>* head;
    Node<int>* tail;
    int listLen;

public:
    LinkedList(){
        head = nullptr;
        tail = nullptr;
        listLen = 0;
    }

    Node<int>* Head(){
        return head;
    }
    Node<int>* Tail(){
        return tail;
    }

    void insert(int x){
        Node<int>* n = new Node<int>(x);
        if(head != nullptr){
            tail->next = n;
            tail = n;
        }
        else{ // if head == nullptr
            head = n;
            tail = n;
        }
        listLen++;
    }

    // void listLenm1(){
    //     listLen--;
    // }

    void print(){
        Node<int>* n = head;
        while(n != nullptr){
            cout << n->data << " ";
            n = n->next;
        }
        cout << endl;
    }
};

class Queue{ // For Level Order Traversal only
private:
    Node<TreeNode*>* first;

public:
    Queue(){
        first = nullptr;
    }

    Node<TreeNode*>* First(){
        return first;
    }

    void pop(){
        Node<TreeNode*>* newF = first->next;
        delete first;
        first = newF;
    }

    void push(TreeNode* i){
        Node<TreeNode*>* n = new Node<TreeNode*>(i);
        if(first == nullptr){
            first = n;
            return;
        }
        else{
            Node<TreeNode*>* t = first;
            while(t->next != nullptr)
                t = t->next;
            t->next = n;
        }
    }
};

void preOrderTvsl(TreeNode* root);
void postOrderTvsl(TreeNode* root);
void levelOrderTvsl(TreeNode* root);
void insertCheck(TreeNode* tr, TreeNode* n);
TreeNode* insertNew(TreeNode* tr, TreeNode* n);
TreeNode* balance(TreeNode* tr, TreeNode* n);
TreeNode* grandParent(TreeNode* tr);
void swapColor(TreeNode* tr);

unsigned int NoR = 0; // Number of Rotations
TreeNode* root = nullptr;

int main(){
    LinkedList ll;
    
    string inputLine;
    getline(cin, inputLine);

    string numStr;
    for(char c : inputLine){
        if(c == ' ' && !numStr.empty()){ // Encountering a blank && Having a number to be stored
            int num;
            if(numStr.length() > 1 || (numStr.length() == 1 && numStr[0] >= '0' && numStr[0] <= '9'))
                num = stoi(numStr);
            else 
                num = int(numStr[0]);
            ll.insert(num);
            numStr.clear();
        }
        else{
            numStr.push_back(c);
        }
    }
    if(!numStr.empty()){
        int num;
        if(numStr.length() > 1 || (numStr[0] >= '0' && numStr[0] <= '9'))
            num = stoi(numStr);
        else 
            num = int(numStr[0]);
        ll.insert(num);
        numStr.clear();
    }
    // Inputs have been collected
    // ll.print();

    // Start inserting the password into the rbtree
    Node<int>* c = ll.Head();
    while(c != nullptr){
        // cout << c->data << " is to be inserted\n";
        TreeNode* newNode = new TreeNode(c->data);
        insertCheck(root, newNode);
        root = insertNew(root, newNode);
        // cout << c->data << " Inserted\n";
        // cout << endl;
        // levelOrderTvsl(root);
        // cout << endl;
        root = balance(root, newNode);
        // cout << "Balanced NoR = " << NoR << endl;
        // levelOrderTvsl(root);
        // cout << endl;
        root->c = 'b';
        c = c->next;
    }
    
    // Output ----------------------------------------------------------------
    postOrderTvsl(root);
    cout << "_";
    preOrderTvsl(root);
    cout << "_" << NoR;
}

// We have to consider the case in which we should output a char instead of an int
void preOrderTvsl(TreeNode* root){ // Only outputs the red nodes
    if(root != nullptr){
        if(root->c == 'r')
            cout << root->val;
        preOrderTvsl(root->left);
        preOrderTvsl(root->right);
    }
}

void postOrderTvsl(TreeNode* root){ // Only outputs the black nodes
    if(root != nullptr){
        postOrderTvsl(root->left);
        postOrderTvsl(root->right);
        if(root->c == 'b')
            cout << root->val;
    }
}

void levelOrderTvsl(TreeNode* root){
    if(root == nullptr) return;
    Queue q;
    cout << root->val << root->c << " ";
    if(root->left)
        q.push(root->left);
    if(root->right)
        q.push(root->right);
    while(q.First()){
        cout << q.First()->data->val << q.First()->data->c << " ";
        if(q.First()->data->left)
            q.push(q.First()->data->left);
        if(q.First()->data->right)
            q.push(q.First()->data->right);  
        q.pop();
    }
    cout << endl;
}

void insertCheck(TreeNode* tr, TreeNode* n){ // Find two consequent nodes and do rotation
    if(tr == nullptr){
        return;
    }
    while(tr != nullptr){
        if(n->val < tr->val){ // tr can be a local root (same function called by itself)
            if(tr->left && tr->right){
                if(tr->left->c == 'r' && tr->right->c == 'r'){
                    swapColor(tr);
                    root = balance(root, tr);
                }
            }
            tr = tr->left;
        }
        else if(n->val >= tr->val){
            if(tr->left && tr->right){
                if(tr->left->c == 'r' && tr->right->c == 'r'){
                    swapColor(tr);
                    root = balance(root, tr);
                }
            }
            tr = tr->right;
        }
    }
}

TreeNode* insertNew(TreeNode* tr, TreeNode* n){ // n is the new node to be inserted
    // If this is a leaf node (subtree doesn't exist), return this node to end the recursion.
    // If the tree doesn't exist, return n as the root node.
    if(tr == nullptr){ 
        return n;
    }
    
    if(n->val < tr->val){ // tr can be a local root (same function called by itself)
        tr->left = insertNew(tr->left, n); // Return the inserted Node to its parent node's pointer
        tr->left->parent = tr; // Make the inserted node the child of the current node tr
    }
    else if(n->val >= tr->val){
        tr->right = insertNew(tr->right, n);
        tr->right->parent = tr;
    }

    return tr; // Internal nodes exit here
}

TreeNode* balance(TreeNode* tr, TreeNode* n){ 
    // n is the newly inserted node or a black-to-red node, tr is the root
    // A single rotation only can balance the tree

    TreeNode* g = grandParent(n);
    if(!g) return tr; // No need to rotate // tr is equal to root here
    TreeNode* p = n->parent;

    if(n != tr){ // No need to balance the tree if the node is the root
        if(n->parent->c == 'r'){ // Two consequent nodes that are red // Problem here - Do I have to check n->c?
            if(n == p->left){ // XL
                if(p == g->left){ // LL
                    TreeNode* temp = p->right;
                    p->parent = g->parent;
                    if(p->parent){
                        if(p->parent->left == g){ // Left Child
                            p->parent->left = p;
                        }
                        else{ // Right Child
                            p->parent->right = p;                        
                        }
                    }
                    p->right = g;
                    g->parent = p;
                    g->left = temp;
                    if(g->left)
                        g->left->parent = g;
                    p->c = 'b';
                    n->c = 'r';
                    g->c = 'r';
                    NoR++;
                    TreeNode* newRoot = p;
                    while(newRoot->parent != nullptr) newRoot = newRoot->parent;
                    return newRoot;
                }
                else if(p == g->right){ // RL
                    TreeNode* tempL = n->left;
                    TreeNode* tempR = n->right;
                    n->parent = g->parent;
                    if(n->parent){
                        if(n->parent->left == g){ // Left Child
                            n->parent->left = n;
                        }
                        else{ // Right Child
                            n->parent->right = n;                        
                        }
                    }
                    n->left = g;
                    n->right = p;
                    p->left = tempR;
                    if(p->left)
                        p->left->parent = p;
                    g->right = tempL;
                    if(g->right)
                        g->right->parent = g;
                    p->parent = n;
                    g->parent = n;
                    n->c = 'b';
                    p->c = 'r';
                    g->c = 'r';
                    NoR++;
                    TreeNode* newRoot = n;
                    while(newRoot->parent != nullptr) newRoot = newRoot->parent;
                    return newRoot;
                }
            }
            else if(n == p->right){ // XR
                if(p == g->left){ // LR
                    TreeNode* tempL = n->left;
                    TreeNode* tempR = n->right;
                    n->parent = g->parent;
                    if(n->parent){
                        if(n->parent->left == g){ // Left Child
                            n->parent->left = n;
                        }
                        else{ // Right Child
                            n->parent->right = n;                        
                        }
                    }
                    n->left = p;
                    n->right = g;
                    p->right = tempL;
                    if(p->right)
                        p->right->parent = p;
                    g->left = tempR;
                    if(g->left)
                        g->left->parent = g;
                    p->parent = n;
                    g->parent = n;
                    n->c = 'b';
                    p->c = 'r';
                    g->c = 'r';
                    NoR++;
                    TreeNode* newRoot = n;
                    while(newRoot->parent != nullptr) newRoot = newRoot->parent;
                    return newRoot;
                }
                else if(p == g->right){ // RR
                    TreeNode* temp = p->left;
                    p->parent = g->parent;
                    if(p->parent){
                        if(p->parent->left == g){ // Left Child
                            p->parent->left = p;
                        }
                        else{ // Right Child
                            p->parent->right = p;                        
                        }
                    }
                    p->left = g;
                    g->parent = p;
                    g->right = temp;
                    if(g->right)
                        g->right->parent = g;
                    p->c = 'b';
                    n->c = 'r';
                    g->c = 'r';
                    NoR++;
                    TreeNode* newRoot = p;
                    while(newRoot->parent != nullptr) newRoot = newRoot->parent;
                    return newRoot;
                }
            }
        }
    }
    return tr;
}

TreeNode* grandParent(TreeNode* tr){
    if(tr != nullptr && tr->parent != nullptr)
        return tr->parent->parent;
    else
        return nullptr;
}

void swapColor(TreeNode* tr){
    tr->left->c = 'b';
    tr->right->c = 'b';
    tr->c = 'r';
}