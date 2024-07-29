#include <iostream>

using namespace std;

template <class T>
class Node {
public:
    int id;
    T data;
    Node<T>* next;
    Node(int id) {
        this->id = id;
        next = nullptr;
    }
};

template <class U>
class List {
public:
    Node<U>* head;
    Node<U>* tail;
    List() {
        head = nullptr;
        tail = nullptr;
    }
    List(Node<U>* h) {
        head = h;
        tail = h;
    }
    
    void addNode(int id) {
        Node<U>* n = new Node<U>(id);
        Node<U>* h = head;
        if (h == nullptr) {
            head = n;
            tail = n;
            return;
        }

        while (h->next != nullptr) {
            h = h->next;
        }
        h->next = n;
        tail = n;
    }

    int size() {
        int count = 0;
        Node<U>* h = head;
        while (h != nullptr) {
            ++count;
            h = h->next;
        }
        return count;
    }
};

int BFS(List<int>* llarr, int n);

int numNode;
int main() {
    cin >> numNode;
    
    // Handle special case 
    if (numNode == 0) {
        cout << "This is an empty graph." << endl;
        return 0;
    }

    // Create an array of nodes of type List, each of which is a list of nodes of type int
    List<int>* llArr = new List<int>[numNode];
    for (int i = 0; i < numNode - 1; ++i) {
        int e1, e2;
        cin >> e1 >> e2;
        llArr[e1].addNode(e2);
        llArr[e2].addNode(e1);
    }
    
    int* heights = new int[numNode];
    for (int i = 0; i < numNode; ++i) {
        heights[i] = BFS(llArr, i);
    }
    
    int min = 99999;
    for (int i = 0; i < numNode; ++i) {
        if (heights[i] < min)
            min = heights[i];
    }
    for (int i = 0; i < numNode; ++i) {
        if (heights[i] == min) {
            cout << i << " ";
        }
    }
    cout << endl;

    delete [] heights;
    delete [] llArr;
    return 0;
}

// Graph in llarr, BFS from n
int BFS(List<int>* llarr, int n) {
    bool* visited = new bool[numNode];
    for (int i = 0; i < numNode; ++i) {
        visited[i] = false;
    }
    visited[n] = true;
    
    int i = 0; // The index of layer
    List<int>* layer = new List<int>[numNode]; // Some space is wasted here
    layer[0].addNode(n);
    
    while (layer[i].size() != 0) {
        for (Node<int>* n = layer[i].head; n != nullptr; n = n->next) {
            for (Node<int>* edge = llarr[n->id].head; edge != nullptr; edge = edge->next) { // llarr[n] is never an empty List
                if (!visited[edge->id]) {
                    visited[edge->id] = true;
                    layer[i + 1].addNode(edge->id);
                }
            }
        }
        ++i;
    }
    
    int height;
    for (int i = 0; i < numNode; ++i) {
        if (layer[i].size() == 0) {
            height = i;
            break;
        }
    }

    delete [] layer;
    delete [] visited;
    return height;
}
