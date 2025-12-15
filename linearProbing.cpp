
#include <iostream>
using namespace std;

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
            // If same key, update value
            if (keys[index] == key) {
                values[index] = name;
                return;
            }

            // Move to next index (linear probing)
            index = (index + 1) % TABLE_SIZE;

            if (index == startIndex) {
                cout << "Hash table is full, cannot insert key " << key << endl;
                return;
            }
        }

        // Found an empty slot
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

int main() {
    HashTable h;

    h.insert(1, "Ali");
    h.insert(11, "Sara");   
    h.insert(21, "Raza");
    h.insert(21, "Usman");   

    cout << "Name of key 1  = " << h.search(1) << endl;
    cout << "Name of key 11 = " << h.search(11) << endl;
    cout << "Name of key 21 = " << h.search(21) << endl;
    cout << "Name of key 5  = " << h.search(5) << endl;  

    cout << "\nHash table:\n";
    h.display();

    return 0;
}