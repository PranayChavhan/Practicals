#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Record {
    int recordNumber;
    string data;
};

class DirectAccessFile {
private:
    fstream file;

public:
    DirectAccessFile(const string& filename) {
        file.open(filename, ios::in | ios::out | ios::binary | ios::app);
        if (!file) {
            cerr << "Error opening file." << endl;
        }
    }

    ~DirectAccessFile() {
        if (file.is_open()) {
            file.close();
        }
    }

    void insertRecord() {
        Record record;
        cout << "Enter Record Number: ";
        cin >> record.recordNumber;
        cout << "Enter Data: ";
        cin.ignore();
        getline(cin, record.data);

        file.seekp(record.recordNumber * sizeof(Record));
        file.write(reinterpret_cast<char*>(&record), sizeof(Record));

        cout << "Record inserted successfully!" << endl;
    }

    void deleteRecord() {
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
    }

    void viewRecord() {
        int recordNumber;
        cout << "Enter the Record Number of the record to view: ";
        cin >> recordNumber;

        file.seekg(recordNumber * sizeof(Record));
        Record record;
        file.read(reinterpret_cast<char*>(&record), sizeof(Record));

        if (record.recordNumber == recordNumber) {
            cout << "Record Number: " << record.recordNumber << endl;
            cout << "Data: " << record.data << endl;
        } else {
            cout << "Record not found!" << endl;
        }
    }

    void viewAllRecords() {
        file.seekg(0, ios::end);
        int numRecords = file.tellg() / sizeof(Record);
        file.seekg(0, ios::beg);

        if (numRecords == 0) {
            cout << "No records found." << endl;
            return;
        }

        for (int i = 0; i < numRecords; ++i) {
            Record record;
            file.read(reinterpret_cast<char*>(&record), sizeof(Record));

            if (record.recordNumber != -1) {
                cout << "Record Number: " << record.recordNumber << endl;
                cout << "Data: " << record.data << endl;
                cout << "-------------------------" << endl;
            }
        }
    }
};

int main() {
    DirectAccessFile directAccessFile("direct_access_file.txt");

    while (true) {
        cout << "Direct Access File" << endl;
        cout << "1. Insert Record" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. View Record" << endl;
        cout << "4. View All Records" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                directAccessFile.insertRecord();
                break;
            case 2:
                directAccessFile.deleteRecord();
                break;
            case 3:
                directAccessFile.viewRecord();
                break;
            case 4:
                directAccessFile.viewAllRecords();
                break;
            case 5:
                cout << "Exiting... Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }
}
