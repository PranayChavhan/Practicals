#include<iostream>
#include<fstream>
#include<string>

using namespace std;


class Student{
private:
    int rollNumber;
    string name;
    string division;
    string address;

public:

    void setRollNumber(int rollNumber){
        this->rollNumber = rollNumber;
    }

    void setName(const string& name){
        this->name = name;
    }

    void setDivison(const string& division){
        this->division = division;
    }

    void setAddress(const string& address){
        this->address = address;
    }

    void getRollNumber(){
        return rollNumber;
    }

    const string& getName()const{
        return name;
    }

    const string& getDivision()const{
        return division;
    }

    const string& getAddress()const{
        return address;
    }

}
class StudentInformationSystem{
private:
    string filename;

public:

    StudentInformationSystem(const string& filename): filename(filename){}

    void addStudent(){
        ofstream file(filename, ios::app);
        if(!file){
            cerr<<"Error opening file."<<endl;
            return;
        }

        Student student;

        cout<<"Enter Roll number: ";
        int rollNumber;
        cin >> rollNumber;
        student.setRollNumber(rollNumber);

        cout<<<"Enter name: ";
        string name;
        cin.ignore();
        getline(cin, name);
        student.setName(name);

        cout <<"Enter Divisin: ";
        string division;
        getline(cin, division);
        student.setDivison(division);

        cout<<"Enter Address: ";
        string address;
        getline(cin, address);
        student.setAddress(address);

        file << student.getRollNumber()<<","
             << student.getName()<<","
             << student.getDivision()<<","
             << student.getAddress()<<endl;

        file.close();


        cout <<"Student info added successfully."<<endl;
    }

    void deleteStudent(){
        ofstream inFile(filename);
        if(!inFile){
            cerr <<"Error while opening file." <<endl;
            return;
        }

        ifstream outFile("temp.txt");
        if(!outFile){
            cerr << "Erro while creating temp file."<<endl;
            inFile.close();
            return;
        }

        int rollNumber;
        cout<<"Enter roll number of std to delete: ";
        cin >> rollNumber;

        Student Student;

        bool found = false;

        string line;

        while(getline(inFile, line)){
            size_t pos = line.find(',');
            student.setRollNumber(stoi(line.substr(o, pos)));

            if (student.getRollNumber == rollNumber)
            {
                found = true;
                continue;
            }
            outFile << line << endl;
            
        }

        inFile.close();
        outFile.close();

        remove(filename.c_str());
        remove("temp.txt", filename.c_str());

        if (found)
        {
            cout<<"deleted successfully"<<endl;
        }else{
            cout<<"Student not found"<<endl;
        }
        
    }

    void displayStudent(){
        ifstream file(filename);
        if(!file){
            cerr<<"Error opening file."<<endl;
            return;
        }

        int rollNumber;
        cout<<"Enter rollnumber of student to display: ";
        cin >> rollNumber;


        Student student;
        bool found = false;

        string line;

        while(getline(file, line)){
            size_t pos = line.find(',');
            student.setRollNumber(stoi(line.substr(0, pos)));


            if(student.getRollNumber() == rollNumber){
                found = true;
                student.setName(line.substr(pos+1, line.find(',', pos+1) - pos-1));
                pos = line.find(',' pos+1);

                student.setDivison(line.substr(pos+1, line.find(',', pos+1) - pos-1));
                pos = line.find(',', pos+1);

                student.getAddress(line.substr(pos+1,));


                cout<<"RollNumber:"<<student.getRollNumber()<<endl;
                cout << "NameP: " << student.getName()<<endl;
                cout <<"division" << student.getDivision()<<endl;
                cout <<"Addres: " << student.getAddress()<<endl;


                break;
            }
        }

        file.close();

        if(!file){
            cout<<"Student not found"<<endl;
        }
    }

    void run(){
        while(true){
            cout<<"Student Info System"<<endl;
            cout<<"1. Add student" << endl;


            int choice;
            cin >> choice;

            switch(choice){
                case 1:
                addStudent();
                break;
            }
        }
    }
}


int main(){

    StudentInformationSystem sis("new_file.txt");

    sis.run();



    return 0;
}