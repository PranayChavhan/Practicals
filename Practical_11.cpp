#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
    string address;
};

void addStudent() {
    ofstream file("student_info.txt", ios::app);
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    file << student.rollNumber << ","
         << student.name << ","
         << student.division << ","
         << student.address << endl;

    file.close();

    cout << "Student information added successfully!" << endl;
}

void deleteStudent() {
    ifstream inFile("student_info.txt");
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
        student.rollNumber = stoi(line.substr(0, pos));

        if (student.rollNumber == rollNumber) {
            found = true;
            continue;
        }

        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    remove("student_info.txt");
    rename("temp.txt", "student_info.txt");

    if (found) {
        cout << "Student information deleted successfully!" << endl;
    } else {
        cout << "Student not found!" << endl;
    }
}

void displayStudent() {
    ifstream file("student_info.txt");
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
        student.rollNumber = stoi(line.substr(0, pos));

        if (student.rollNumber == rollNumber) {
            found = true;
            student.name = line.substr(pos + 1, line.find(',', pos + 1) - pos - 1);
            pos = line.find(',', pos + 1);
            student.division = line.substr(pos + 1, line.find(',', pos + 1) - pos - 1);
            pos = line.find(',', pos + 1);
            student.address = line.substr(pos + 1);

            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;

            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Student not found!" << endl;
    }
}

int main() {
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
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }
}
