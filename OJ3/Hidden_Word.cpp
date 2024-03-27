#include <iostream>
#include <string>

using namespace std;

void insertionSort(int num[], char ch[], int n, int* step);
void selectionSort(int num[], char ch[], int n, int* step);
bool check(char arr[], int n);

// With period excluded
string insSort = "Word found in insertion sort step ";
string selSort = "Word found in selection sort step ";
string bothSort1 = "Word found in insertion sort step "; 
string bothSort2 = " and selection sort step ";
string NF = "Word not found.";

string str;

int main(){
    int nums[100], b_nums[100]; // With one backup
    char ch[100], b_ch[100];
    int n = 0; // The number of (num, char) tuples
    
    string line1, line2;
    getline(cin, str);
    getline(cin, line1);
    getline(cin, line2);

    string numStr = "";
    for (char c : line1) {
        if (c == ' ' && !numStr.empty()) { // Encountering a blank && Having a number to be stored 
            int num = stoi(numStr);
            nums[n] = num;
            n++;
            numStr.clear();
        } else {
            numStr.push_back(c);
        }
    }
    if (!numStr.empty()) {
        int num = stoi(numStr);
        nums[n] = num;
        n++;
        numStr.clear();
    }
    
    int check_cnt = 0;
    for (char c : line2) {
        if (c != ' '){
            ch[check_cnt] = c;
            check_cnt++;
        }
        // else, next iteration
    }
    if (check_cnt != n){
        cout << "Invalid input!" << endl;
        return 1;
    }
    // Inputs have been collected
    
    // Now, duplicate
    for(int i = 0; i < n; i++){
        b_nums[i] = nums[i];
        b_ch[i] = ch[i];
    }

    // Insertion Sort
    int stepIns = -1;
    insertionSort(nums, ch, n, &stepIns);
    
    // Selection sort
    int stepSel = -1;
    selectionSort(b_nums, b_ch, n, &stepSel);

    // Result
    if(stepIns != -1 && stepSel != -1){ // Both
        cout << bothSort1 << stepIns << bothSort2 << stepSel << "." << endl;
    }
    else if(stepIns != -1){
        cout << insSort << stepIns << "." << endl;
    }
    else if(stepSel != -1){
        cout << selSort << stepSel << "." << endl;
    }
    else{
        cout << NF << endl;
    }
    // Print the sorted chars
    for (int i = 0; i < n; i++){
        cout << ch[i];
    }

    return 0;
}

void insertionSort(int num[], char ch[], int n, int* step){ // n is size
    bool kept = false;

    for(int i = 1; i < n; i++){
        int tmp = num[i];
        char c = ch[i];
        int j = i - 1;
        while(tmp <= num[j]){
            num[j + 1] = num[j];
            ch[j + 1] = ch[j];
            j--;
            if(j == -1){
                break;
            }
        }
        num[j + 1] = tmp;
        ch[j + 1] = c;
        // the ith step of sort has finished here
        
        if(check(ch, n) && !kept){ // Check if the strings match
            kept = true;
            *step = i + 1; // i = 1 has two sorted numbers on the left -> step 2
        }
    }
}

void selectionSort(int num[], char ch[], int n, int* step){
    bool kept = false;
    for(int i = 0; i < n - 1; i++){
        int pos = i;
        int smallest = num[i];
        for(int j = i + 1; j < n; j++){
            if(smallest > num[j]){
                smallest = num[j];
                pos = j;
            }
        }
        // Swap two ints and chars
        int temp = num[pos];
        num[pos] = num[i];
        num[i] = temp;
        char c = ch[pos];
        ch[pos] = ch[i];
        ch[i] = c;
        // the (i+1)th step of sort has finished here
        
        if(check(ch, n) && !kept){ // Check if the strings match
            kept = true;
            *step = i + 1; // i = 0 has one sorted numbers on the left -> step 1
        }
    }
}

bool check(char arr[], int n){
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == str[i]) cnt++;
    }
    if(cnt == n) return true;
    return false;
}