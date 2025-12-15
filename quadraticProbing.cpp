#include <iostream>
#include <string>
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
            keys[i] = 0;
            values[i] = "";
            occupied[i] = false;
        }
    }

    void insert(int key, const string& name) {
        int hash = hashFunction(key);
        int index;
        int i = 0;

        // Quadratic probing
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

            if (!occupied[index]) return "NOT FOUND"; // empty slot ? key not present
            if (keys[index] == key) return values[index];

            i++;
        }

        return "NOT FOUND"; // searched all slots
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

    // Insert keys
    h.insert(1, "Ali");
    h.insert(11, "Sara");  // collision with key 1
    h.insert(21, "Raza");  // another collision
    h.insert(2, "Taha");
    h.insert(31, "Usman");  // another collision

    cout << "Search key 11: " << h.search(11) << endl;
    cout << "Search key 21: " << h.search(21) << endl;
    cout << "Search key 5 : " << h.search(5) << endl;

    cout << "\nHash table:\n";
    h.display();

    return 0;
}