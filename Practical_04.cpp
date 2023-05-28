#include <iostream>
#include <string>
using namespace std;

class Client {
public:
    string name;
    string phoneNumber;

    Client(const string& n, const string& num) {
        name = n;
        phoneNumber = num;
    }
};

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    Client** table;
    int numCollisions;
    int numComparisons;

    int hashFunction(const string& key) {
        int sum = 0;
        for (char ch : key)
            sum += ch;
        return sum % TABLE_SIZE;
    }

public:
    HashTable() {
        table = new Client * [TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
        numCollisions = 0;
        numComparisons = 0;
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr)
                delete table[i];
        }
        delete[] table;
    }

    void insert(const string& name, const string& phoneNumber, bool replace) {
        Client* newClient = new Client(name, phoneNumber);
        int index = hashFunction(name);

        while (table[index] != nullptr) {
            numComparisons++;
            if (table[index]->name == name) {
                if (replace) {
                    delete table[index];
                    table[index] = newClient;
                }
                else {
                    numCollisions++;
                    return;
                }
            }
            index = (index + 1) % TABLE_SIZE;
        }

        table[index] = newClient;
    }

    string search(const string& name) {
        int index = hashFunction(name);

        while (table[index] != nullptr) {
            numComparisons++;
            if (table[index]->name == name)
                return table[index]->phoneNumber;
            index = (index + 1) % TABLE_SIZE;
        }

        return "Not found";
    }

    int getNumCollisions() {
        return numCollisions;
    }

    int getNumComparisons() {
        return numComparisons;
    }
};

int main() {
    HashTable hashTable;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "Telephone Book Database" << endl;
        cout << "1. Add a client" << endl;
        cout << "2. Search for a client's phone number" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, phoneNumber;
            cout << "Enter client's name: ";
            cin >> name;
            cout << "Enter client's phone number: ";
            cin >> phoneNumber;

            hashTable.insert(name, phoneNumber, true);
            cout << "Client added successfully!" << endl;
            break;
        }
        case 2: {
            string name;
            cout << "Enter client's name to search: ";
            cin >> name;

            string phoneNumber = hashTable.search(name);
            if (phoneNumber == "Not found")
                cout << "Client not found!" << endl;
            else
                cout << "Phone number: " << phoneNumber << endl;
            break;
        }
        case 3:
            exitMenu = true;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
