#include <iostream>
using namespace std;

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

        // Check if key already exists in the chain, update it
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
            // Node is at head
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

int main() {
    HashTable h;

    h.insert(101, "Ali");
    h.insert(205, "Sara");
    h.insert(309, "Raza");
    h.insert(115, "Taha");
    h.insert(125, "Imran");

    cout << "Name of roll 101 = " << h.search(101) << endl;
    cout << "Name of roll 205 = " << h.search(205) << endl;
    cout << "Name of roll 309 = " << h.search(309) << endl;
    cout << "Name of roll 555 = " << h.search(555) << endl; 

    cout << "\nHash table before deletion:\n";
    h.display();

    cout << "\nDeleting roll 205...\n";
    h.remove(205);

    cout << "\nHash table after deletion:\n";
    h.display();

    return 0;
}