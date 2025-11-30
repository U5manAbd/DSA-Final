#include <iostream>
using namespace std;

// Max Heap
class MaxHeap {
private:
    int *heap;
    int capacity;
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapifyDown(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && heap[l] > heap[largest])
            largest = l;

        if (r < size && heap[r] > heap[largest])
            largest = r;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    MaxHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[cap];
    }

    void insert(int key) {
        if (size == capacity) {
            cout << "Heap full!\n";
            return;
        }

        int i = size;
        heap[size++] = key;
        heapifyUp(i);
    }

    int getMax() {
        if (size == 0) {
            cout << "Heap empty!\n";
            return -1;
        }
        return heap[0];
    }

    int extractMax() {
        if (size == 0) {
            cout << "Heap empty!\n";
            return -1;
        }

        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;

        heapifyDown(0);
        return root;
    }

    void buildHeap(int arr[], int n) {
        if (n > capacity) return;

        size = 0;

        for (int i = 0; i < n; i++) {
            heap[size] = arr[i];
            heapifyUp(size);
            size++;
        }
    }

    void print() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << "\n";
    }
};

// Min Heap
class MinHeap {
private:
    int *heap;
    int capacity;
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && heap[l] < heap[smallest])
            smallest = l;

        if (r < size && heap[r] < heap[smallest])
            smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    MinHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[cap];
    }

    void insert(int key) {
        if (size == capacity) {
            cout << "Heap full!\n";
            return;
        }

        int i = size;
        heap[size++] = key;
        heapifyUp(i);
    }

    int getMin() {
        if (size == 0) {
            cout << "Heap empty!\n";
            return -1;
        }
        return heap[0];
    }

    int extractMin() {
        if (size == 0) {
            cout << "Heap empty!\n";
            return -1;
        }

        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;

        heapifyDown(0);
        return root;
    }

    void buildHeap(int arr[], int n) {
        if (n > capacity) return;

        size = n;
        for (int i = 0; i < n; i++)
            heap[i] = arr[i];

        for (int i = (n/2) - 1; i >= 0; i--)
            heapifyDown(i);
    }

    void print() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << "\n";
    }
};

// Heap Sort
void heapifyMaxArr(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyMaxArr(arr, n, largest);
    }
}

void heapSortAsc(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) heapifyMaxArr(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapifyMaxArr(arr, i, 0); 
    }
}

// Hashing
// Separate Chaining
const int TABLE_SIZE = 10;

struct Node {
    int key;           
    string value;    
    Node* next;        

    Node(int k, const string& v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable {
private:
    Node* table[TABLE_SIZE];  

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void insert(int key, const string& name) {
        int index = hashFunction(key);

        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = name;  
                return;
            }
            current = current->next;
        }
        
        Node* newNode = new Node(key, name);
        newNode->next = table[index];
        table[index] = newNode;
    }

    string search(int key) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        return "NOT FOUND";
    }


    void remove(int key) {
        int index = hashFunction(key);
        Node* temp = table[index];
        Node* prev = nullptr;

        while (temp != nullptr && temp->key!=key) {
            prev = temp;
            temp = temp->next;
        }
        if(temp==nullptr){
        	cout << "Key " << key << " not found\n";
		}
        if (prev == nullptr) {
            table[index] = temp->next;
        } 
		else {
            prev->next = temp->next;
        }
        delete temp;
        cout << "Key " << key << " deleted\n";
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << " : ";
            Node* current = table[i];
            if (!current) {
                cout << "EMPTY";
            }
            while (current != nullptr) {
                cout << " -> [Key: " << current->key
                     << ", Name: " << current->value << "]";
                current = current->next;
            }
            cout << endl;
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

// Linear Probing
const int TABLE_SIZE = 10;

class HashTable {
private:
    int keys[TABLE_SIZE];        
    string values[TABLE_SIZE];   
    bool occupied[TABLE_SIZE];   

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            occupied[i] = false;
            keys[i] = 0;
            values[i] = "";
        }
    }

    void insert(int key, const string& name) {
        int index = hashFunction(key);
        int startIndex = index; 

        while (occupied[index]) {
            if (keys[index] == key) {
                values[index] = name;
                return;
            }

            index = (index + 1) % TABLE_SIZE;

            if (index == startIndex) {
                cout << "Hash table is full, cannot insert key " << key << endl;
                return;
            }
        }

        keys[index] = key;
        values[index] = name;
        occupied[index] = true;
    }

    string search(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (occupied[index]) {
            if (keys[index] == key) {
                return values[index];   
            }

            index = (index + 1) % TABLE_SIZE;

            if (index == startIndex) {
                break;
            }
        }

        return "NOT FOUND";
    }

    void display() {
        cout << "Index\tKey\tName\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i]) {
                cout << i << "\t" << keys[i] << "\t" << values[i] << "\n";
            } else {
                cout << i << "\t" << "-\t" << "-\n";
            }
        }
    }
};

// Quadratic Probing
const int TABLE_SIZE = 10;

class HashTable {
private:
    int keys[TABLE_SIZE];
    string values[TABLE_SIZE];
    bool occupied[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            keys[i] = 0;
            values[i] = "";
            occupied[i] = false;
        }
    }

    void insert(int key, const string& name) {
        int hash = hashFunction(key);
        int index;
        int i = 0;

        while (i < TABLE_SIZE) {
            index = (hash + i * i) % TABLE_SIZE;

            if (!occupied[index] || keys[index] == key) {
                keys[index] = key;
                values[index] = name;
                occupied[index] = true;
                return;
            }

            i++;
        }

        cout << "Hash table full, cannot insert key " << key << endl;
    }

    string search(int key) {
        int hash = hashFunction(key);
        int index;
        int i = 0;

        while (i < TABLE_SIZE) {
            index = (hash + i * i) % TABLE_SIZE;

            if (!occupied[index]) return "NOT FOUND";
            if (keys[index] == key) return values[index];

            i++;
        }

        return "NOT FOUND";
    }

    void display() {
        cout << "Index\tKey\tName\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i])
                cout << i << "\t" << keys[i] << "\t" << values[i] << "\n";
            else
                cout << i << "\t-\t-\n";
        }
    }
};

// Double Hashing
const int TABLE_SIZE = 10;

class HashTable {
private:
    int keys[TABLE_SIZE];
    string values[TABLE_SIZE];
    bool occupied[TABLE_SIZE];

    int hash1(int key) {
        return key % TABLE_SIZE;
    }

    int hash2(int key) {
        int R = 7;
        return R - (key % R);
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            keys[i] = 0;
            values[i] = "";
            occupied[i] = false;
        }
    }

    void insert(int key, const string& name) {
        int h1 = hash1(key);
        int h2 = hash2(key);
        int index;
        int i = 0;

        while (i < TABLE_SIZE) {
            index = (h1 + i * h2) % TABLE_SIZE;

            if (!occupied[index] || keys[index] == key) {
                keys[index] = key;
                values[index] = name;
                occupied[index] = true;
                return;
            }

            i++;
        }

        cout << "Hash table full, cannot insert key " << key << endl;
    }

    string search(int key) {
        int h1 = hash1(key);
        int h2 = hash2(key);
        int index;
        int i = 0;

        while (i < TABLE_SIZE) {
            index = (h1 + i * h2) % TABLE_SIZE;

            if (!occupied[index]) return "NOT FOUND";
            if (keys[index] == key) return values[index];

            i++;
        }

        return "NOT FOUND";
    }

    void display() {
        cout << "Index\tKey\tName\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i])
                cout << i << "\t" << keys[i] << "\t" << values[i] << "\n";
            else
                cout << i << "\t-\t-\n";
        }
    }
};

// String Searching Algorithms
// Brute Force
void bruteForceSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; i++) {
        int j = 0;

        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }

        if (j == m) {  // Match found
            cout << "Pattern found at index " << i << endl;
        }
    }
}

// Rabin-Karp
#define d 256

void rabinKarp(string text, string pattern, int q) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0 || m > n) {
        cout << "No valid pattern to search.\n";
        return;
    }

    int p = 0;
    int t = 0;
    int h = 1;

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {

        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0)
                t = t + q;
        }
    }
}

// KMP
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void computeLPSArray(const string &pattern, vector<int> &lps) {
    int m = pattern.length();
    lps[0] = 0;
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0;
    int j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++; j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

// Boyer-Moore
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define NO_OF_CHARS 256

void badCharHeuristic(const string &pattern, vector<int> &badChar) {
    int m = pattern.length();
    for (int i = 0; i < NO_OF_CHARS; i++)
        badChar[i] = -1;
    for (int i = 0; i < m; i++)
        badChar[(int)pattern[i]] = i;
}

void boyerMooreSearch(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> badChar(NO_OF_CHARS);
    badCharHeuristic(pattern, badChar);

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            cout << "Pattern found at index " << s << endl;

            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        } else {
            int shift = max(1, j - badChar[text[s + j]]);
            s += shift;
        }
    }
}