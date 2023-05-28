#include <iostream>
using namespace std;

template <typename K, typename V>
class Dictionary {
private:
    struct KeyValuePair {
        K key;
        V value;
        KeyValuePair* next;

        KeyValuePair(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    KeyValuePair** hashTable;
    int size;
    int capacity;
    static const int DEFAULT_CAPACITY = 10;

    int hashFunction(const K& key) {
        // Hash function implementation (can be customized)
        // For simplicity, we assume the keys are integers
        return key % capacity;
    }

public:
    Dictionary(int initialCapacity = DEFAULT_CAPACITY) {
        capacity = initialCapacity;
        size = 0;
        hashTable = new KeyValuePair*[capacity]();
    }

    ~Dictionary() {
        clear();
        delete[] hashTable;
    }

    void insert(const K& key, const V& value) {
        int index = hashFunction(key);
        KeyValuePair* newPair = new KeyValuePair(key, value);

        if (hashTable[index] == nullptr) {
            hashTable[index] = newPair;
        } else {
            KeyValuePair* curr = hashTable[index];
            while (curr->next != nullptr) {
                if (curr->key == key) {
                    curr->value = value; // Update existing key's value
                    delete newPair;      // Clean up duplicate key-value pair
                    return;
                }
                curr = curr->next;
            }
            if (curr->key == key) {
                curr->value = value; // Update existing key's value
                delete newPair;      // Clean up duplicate key-value pair
                return;
            }
            curr->next = newPair;
        }
        size++;
    }

    V find(const K& key) {
        int index = hashFunction(key);
        KeyValuePair* curr = hashTable[index];
        while (curr != nullptr) {
            if (curr->key == key)
                return curr->value;
            curr = curr->next;
        }
        // Key not found, return a default value (assuming V is a class with a default constructor)
        return V();
    }

    void remove(const K& key) {
        int index = hashFunction(key);
        KeyValuePair* curr = hashTable[index];
        KeyValuePair* prev = nullptr;

        while (curr != nullptr) {
            if (curr->key == key) {
                if (prev == nullptr)
                    hashTable[index] = curr->next;
                else
                    prev->next = curr->next;
                delete curr;
                size--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void clear() {
        for (int i = 0; i < capacity; i++) {
            KeyValuePair* curr = hashTable[i];
            while (curr != nullptr) {
                KeyValuePair* next = curr->next;
                delete curr;
                curr = next;
            }
            hashTable[i] = nullptr;
        }
        size = 0;
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }
};

int main() {
    Dictionary<int, string> dictionary;

    int choice;
    do {
        cout << "Dictionary Menu:" << endl;
        cout << "1. Insert key-value pair" << endl;
        cout << "2. Find value by key" << endl;
        cout << "3. Remove key-value pair" << endl;
        cout << "4. Clear dictionary" << endl;
        cout << "5. Print dictionary size" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int key;
                string value;
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dictionary.insert(key, value);
                cout << "Key-value pair inserted." << endl;
                break;
            }
            case 2: {
                int key;
                cout << "Enter key: ";
                cin >> key;
                string value = dictionary.find(key);
                if (!value.empty())
                    cout << "Value: " << value << endl;
                else
                    cout << "Key not found." << endl;
                break;
            }
            case 3: {
                int key;
                cout << "Enter key: ";
                cin >> key;
                dictionary.remove(key);
                cout << "Key-value pair removed." << endl;
                break;
            }
            case 4:
                dictionary.clear();
                cout << "Dictionary cleared." << endl;
                break;
            case 5:
                cout << "Dictionary size: " << dictionary.getSize() << endl;
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 6);

    return 0;
}
