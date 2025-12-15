#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
private:
    int keys[TABLE_SIZE];
    string values[TABLE_SIZE];
    bool occupied[TABLE_SIZE];

    // Primary hash
    int hash1(int key) {
        return key % TABLE_SIZE;
    }

    // Secondary hash (step size), must be non-zero
    int hash2(int key) {
        int R = 7; // prime smaller than TABLE_SIZE
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

int main() {
    HashTable h;

    h.insert(1, "Ali");
    h.insert(11, "Sara"); 
    h.insert(21, "Raza");  
    h.insert(2, "Taha");

    cout << "Search key 11: " << h.search(11) << endl;
    cout << "Search key 21: " << h.search(21) << endl;
    cout << "Search key 5 : " << h.search(5) << endl;

    cout << "\nHash table:\n";
    h.display();

    return 0;
}