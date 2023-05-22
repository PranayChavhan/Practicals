#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Record {
    int recordNumber;
    string data;
};

void insertRecord() {
    ofstream file("direct_access_file.txt", ios::app | ios::binary);
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    Record record;
    cout << "Enter Record Number: ";
    cin >> record.recordNumber;
    cout << "Enter Data: ";
    cin.ignore();
    getline(cin, record.data);

    file.seekp(record.recordNumber * sizeof(Record));
    file.write(reinterpret_cast<char*>(&record), sizeof(Record));

    file.close();

    cout << "Record inserted successfully!" << endl;
}

void deleteRecord() {
    fstream file("direct_access_file.txt", ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    int recordNumber;
    cout << "Enter the Record Number of the record to delete: ";
    cin >> recordNumber;

    file.seekp(recordNumber * sizeof(Record));
    Record record;
    file.read(reinterpret_cast<char*>(&record), sizeof(Record));

    if (record.recordNumber == recordNumber) {
        record.recordNumber = -1;
        record.data = "";

        file.seekp(recordNumber * sizeof(Record));
        file.write(reinterpret_cast<char*>(&record), sizeof(Record));

        cout << "Record deleted successfully!" << endl;
    } else {
        cout << "Record not found!" << endl;
    }

    file.close();
}

int main() {
    while (true) {
        cout << "Direct Access File" << endl;
        cout << "1. Insert Record" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                insertRecord();
                break;
            case 2:
                deleteRecord();
                break;
            case 3:
                cout << "Exiting... Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }
}
