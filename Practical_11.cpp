#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    string division;
    string address;

public:
    void setRollNumber(int rollNumber) {
        this->rollNumber = rollNumber;
    }

    void setName(const string& name) {
        this->name = name;
    }

    void setDivision(const string& division) {
        this->division = division;
    }

    void setAddress(const string& address) {
        this->address = address;
    }

    int getRollNumber() const {
        return rollNumber;
    }

    const string& getName() const {
        return name;
    }

    const string& getDivision() const {
        return division;
    }

    const string& getAddress() const {
        return address;
    }
};

class StudentInformationSystem {
private:
    string filename;

public:
    StudentInformationSystem(const string& filename) : filename(filename) {}

    void addStudent() {
        ofstream file(filename, ios::app);
        if (!file) {
            cerr << "Error opening file." << endl;
            return;
        }

        Student student;
        cout << "Enter Roll Number: ";
        int rollNumber;
        cin >> rollNumber;
        student.setRollNumber(rollNumber);
        cout << "Enter Name: ";
        cin.ignore();
        string name;
        getline(cin, name);
        student.setName(name);
        cout << "Enter Division: ";
        string division;
        getline(cin, division);
        student.setDivision(division);
        cout << "Enter Address: ";
        string address;
        getline(cin, address);
        student.setAddress(address);

        file << student.getRollNumber() << ","
             << student.getName() << ","
             << student.getDivision() << ","
             << student.getAddress() << endl;

        file.close();

        cout << "Student information added successfully!" << endl;
    }

    void deleteStudent() {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error opening file." << endl;
            return;
        }

        ofstream outFile("temp.txt");
        if (!outFile) {
            cerr << "Error creating temporary file." << endl;
            inFile.close();
            return;
        }

        int rollNumber;
        cout << "Enter the Roll Number of the student to delete: ";
        cin >> rollNumber;

        Student student;
        bool found = false;
        string line;
        while (getline(inFile, line)) {
            size_t pos = line.find(',');
            student.setRollNumber(stoi(line.substr(0, pos)));

            if (student.getRollNumber() == rollNumber) {
                found = true;
                continue;
            }

            outFile << line << endl;
        }

        inFile.close();
        outFile.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        if (found) {
            cout << "Student information deleted successfully!" << endl;
        } else {
            cout << "Student not found!" << endl;
        }
    }

    void displayStudent() {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file." << endl;
            return;
        }

        int rollNumber;
        cout << "Enter the Roll Number of the student to display: ";
        cin >> rollNumber;

        Student student;
        bool found = false;
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            student.setRollNumber(stoi(line.substr(0, pos)));

            if (student.getRollNumber() == rollNumber) {
                found = true;
                student.setName(line.substr(pos + 1, line.find(',', pos + 1) - pos - 1));
                pos = line.find(',', pos + 1);
                student.setDivision(line.substr(pos + 1, line.find(',', pos + 1) - pos - 1));
                pos = line.find(',', pos + 1);
                student.setAddress(line.substr(pos + 1));

                cout << "Roll Number: " << student.getRollNumber() << endl;
                cout << "Name: " << student.getName() << endl;
                cout << "Division: " << student.getDivision() << endl;
                cout << "Address: " << student.getAddress() << endl;

                break;
            }
        }

        file.close();

        if (!found) {
            cout << "Student not found!" << endl;
        }
    }

    void run() {
        while (true) {
            cout << "Student Information System" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Delete Student" << endl;
            cout << "3. Display Student" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    deleteStudent();
                    break;
                case 3:
                    displayStudent();
                    break;
                case 4:
                    cout << "Exiting... Thank you!" << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }

            cout << endl;
        }
    }
};

int main() {
    StudentInformationSystem sis("student_info.txt");
    sis.run();

    return 0;
}
