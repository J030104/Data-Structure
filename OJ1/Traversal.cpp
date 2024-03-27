#include<iostream>
#include<string>

using namespace std;

class Node{
public:
    string s;
    Node* left;
    Node* right;
    Node(){
        s = ""; // Null value ?
    }
    Node(string str){
        s = str;
        left = nullptr;
        right = nullptr;
    }
};

class Tree{
public:
    Node* root;

    Tree(){
        Node* n = new Node();
        root = n;
    }
    
    void traverseInOrder(Node *p){
        if(p){
            traverseInOrder(p->left);
            cout << p->s;
            traverseInOrder(p->right);
        }
    }

    void traversePreOrder(Node *p){
        if(p){
            cout << p->s;
            traversePreOrder(p->left);
            traversePreOrder(p->right);
        }
    }
    
    void traversePostOrder(Node *p){
        if(p){
            traversePostOrder(p->left);
            traversePostOrder(p->right);
            cout << p->s;
        }
    }
};

class QueueNode {
public:
	Node *data;
	QueueNode *next;

    QueueNode(){
        next = nullptr;
    }

    QueueNode(Node* n){
        data = n;
        next = nullptr;
    }
};

class Queue {
    public:
    QueueNode* front;
    QueueNode* rear;

    Queue(){
        front = nullptr;
        rear = nullptr;
    }

    ~Queue(){
        while(front != nullptr){
            pop();
        }
    }
    
    // front->_ _ _ _ _<-rear
    void push(Node* n){
        QueueNode* a = new QueueNode(n);
        if(front == nullptr && rear == nullptr){
            front = a;
            rear = a;
        }
        else{
            rear->next = a;
            rear = a;
        }
    }

    Node* pop(){
        if(front == nullptr){
            return nullptr;
        }
        else if(front == rear){ // Only one in the Queue
            Node* ret = front->data;
            delete front;
            front = nullptr;
            rear = nullptr;
            return ret;
        }
        else{
            QueueNode* temp = front;
            Node* ret = front->data;
            front = front->next;
            delete temp;
            return ret;
        }
    }
};

string infix;
string pfix; // The expression
void ConstructBinaryTree(Tree &t, string typ);
void ConstructSubtree_Pre(Tree& t);
void ConstructSubtree_Post(Tree& t);
void LevelTraversal(Node* root);
Node* LevelTraversal_Find(Node* root, char c);
unsigned int charIdx;

int main(){
    string type1; // infix + prefix / infix + postfix
    string type2; // A specified way of expression

    Tree tr;

    // input
    getline(cin, infix);
    getline(cin, type1);
    getline(cin, pfix);
    getline(cin, type2);

    // infix = "DBEAFCG";
    // type1 = "prefix";
    // pfix = "ABDECFG";
    // type2 = "postfix";

    // infix = "DBHEIAFJCG";
    // type1 = "postfix";
    // pfix = "DHIEBJFGCA";
    // type2 = "prefix";

    // infix ="AaBbCcDdE";
    // type1 = "postfix";
    // pfix = "ABCbaDEdc";
    // type2 = "prefix";

    (tr.root)->s = infix;
    ConstructBinaryTree(tr, type1);
    // tr.traverseInOrder(tr.root);
    // cout << endl;
    if(type2 == "prefix"){
        tr.traversePreOrder(tr.root);
        cout << endl;
    }
    else if(type2 == "postfix"){    
        tr.traversePostOrder(tr.root);
        cout << endl;
    }
    LevelTraversal(tr.root);

    return 0;
}

void ConstructBinaryTree(Tree &t, string typ){
    if(typ == "prefix"){
        ConstructSubtree_Pre(t);
    }
    else if(typ == "postfix"){
        ConstructSubtree_Post(t);
    }
}

void ConstructSubtree_Pre(Tree& t){
    for(int i = 0; i < pfix.length(); i++){
        Node* n;
        string str = "";

        if(n = LevelTraversal_Find(t.root, pfix[i])){
            str = n->s; // keep the string n->s
            n->s = str[charIdx]; // pfix[i] is assigned to the node n
        }
        else
            cerr << pfix[i] << " not found\n";
        
        if(str.length() > 1){ // if it's 1 or 0, we don't need to do anything
            string s1 = str.substr(0, charIdx); // left substring
            string s2 = str.substr(charIdx + 1); // right substring
            if(s1.length() != 0){
                Node* subn = new Node(s1);
                n->left = subn;
            }
            if(s2.length() != 0){
                Node* subn = new Node(s2);
                n->right = subn;            
            }
        }
    }

}

void ConstructSubtree_Post(Tree& t){
    for(int i = pfix.length() - 1; i >= 0; i--){
        Node* n;
        string str = "";

        if(n = LevelTraversal_Find(t.root, pfix[i])){
            str = n->s; // keep the string n->s
            n->s = str[charIdx]; // pfix[i] is assigned to the node n
        }
        else
            cerr << pfix[i] << " not found\n";
        
        if(str.length() > 1){ // if it's 1 or 0, we don't need to do anything
            string s1 = str.substr(0, charIdx); // left substring
            string s2 = str.substr(charIdx + 1); // right substring
            if(s1.length() != 0){
                Node* subn = new Node(s1);
                n->left = subn;
            }
            if(s2.length() != 0){
                Node* subn = new Node(s2);
                n->right = subn;            
            }
        }
    }

}

void LevelTraversal(Node* root){
    Queue q;
    if(root){ // If root is not nullptr
        q.push(root); // Just push it into the Queue
        while(1){
            Node* a = q.pop(); // Just keep poping
            if(a)
                cout << a->s;
            else
                break;
            if(a->left)
                q.push(a->left); // Queue this Node so that it will be processed
            if(a->right)
                q.push(a->right); // It will be processed later than the last one
        }
    }
    cout << endl;
}

Node* LevelTraversal_Find(Node* root, char c){
    Queue q;
    if(root){ // If root is not nullptr
        q.push(root); // Just push it into the Queue
        while(1){
            Node* a = q.pop(); // Just keep poping
            if(a){
                string str = a->s;
                for(int i = 0; i < str.length(); i++){
                    if(c == str[i]){
                        charIdx = i;
                        return a;
                    }
                    // else, continue
                }
            }
            else break;

            if(a->left)
                q.push(a->left); // Queue this Node so that it will be processed
            if(a->right)
                q.push(a->right); // It will be processed later than the last one
        }
        return nullptr;
    }
}