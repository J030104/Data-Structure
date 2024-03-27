#include<iostream>
#include<string>

using namespace std;

class Node{
public:
    int w;
    Node* next;
    Node(int x){
        w = x;
        next = nullptr;
    }
};

class LinkedList{
private:
    Node* head;
    Node* tail;
    int listLen;

public:
    LinkedList(){
        head = nullptr;
        tail = nullptr;
        listLen = 0;
    }

    Node* Head(){
        return head;
    }
    Node* Tail(){
        return tail;
    }

    void insert(int x){
        Node *n = new Node(x);
        if(head != nullptr){
            // Node* t = head;
            // while(t->next != nullptr) t = t->next;
            // t->next = n;
            tail->next = n;
            tail = n;
        }
        else{ // if head == nullptr
            head = n;
            tail = n;
        }
        listLen++;
    }

    void print(){
        Node *n = head;
        // cout << endl;
        while(n != nullptr){
            cout << n->w << " ";
            n = n->next;
        }
        cout << endl;
    }
};

class Stack{
private:
    LinkedList l;
    int cnt = 0;

public:
    void push(Node* front, Node* end){ // Pushing in a linkedlist (end->w will be stored)
        LinkedList l_new;
        while(front != end){
            l_new.insert(front->w);
            front = front->next;
        }
        l_new.insert(front->w);
        if(l_new.Tail() != nullptr){
            l_new.Tail()->next = l.Head();
            l = l_new;
            cnt++;
        }
    }
    
    void get_cnt(){
        cout << cnt << endl;
    }
    void print(){
        l.print();
    }
};

int main(){
    LinkedList ll;
    
    string inputLine;
    getline(cin, inputLine);

    string numStr;
    for (char c : inputLine) {
        if (c == ' ' && !numStr.empty()) { // Encountering a blank && Having a number to be stored 
            int num = stoi(numStr);
            ll.insert(num);
            numStr.clear();
        } else {
            numStr.push_back(c);
        }
    }
    if (!numStr.empty()) {
        int num = stoi(numStr);
        ll.insert(num);
    }
    // inputs have been collected
    
    Node* h = ll.Head();
    Stack s;
    int w_t = 0;
    while(h != nullptr){
        // Both start and end are used to keep the position
        Node* start = h;
        w_t = 0;
        while(1){
            w_t += h->w;
            if(h->next != nullptr){ // There are still nodes come after this node
                if(w_t + h->next->w > 200){ // Next people cannot get on
                    s.push(start, h);
                    h = h->next;
                    break;
                }
            }
            else{ // h is the last node
                s.push(start, h);
                s.get_cnt();
                s.print();
                return 0;
            }
            h = h->next;
        }
    }
}