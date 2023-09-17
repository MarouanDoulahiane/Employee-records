#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct {
    string name;
    double salary;
    string position;
} Employee;

#define FILE_PATH "data.bin"

void    addTobin(Employee employee, string file_path)
{
    try {
        ofstream file(file_path, ios::app | ios::binary);
        if (!file) {
            cerr << "Cannot open " << file_path << "!\n";
            return;
        }
        file.write((char*)&employee, sizeof(Employee));
        file.close();
        cout << "\033[1;32m[SUCCESS]\033[0m the employee added.\n";
    }
    catch (exception& e) {
        cerr << "error when we add to the file {" << e.what() << "}" << endl;
    }
}

vector<Employee*> readFromBin(string file_path)
{
    vector<Employee*> allEmployee;
    ifstream file(file_path, ios::in | ios::binary | ios::ate);
    streampos size = file.tellg();
    char* memblock = new char[size];
    file.seekg(0, ios::beg);
    file.read(memblock, size);
    file.close();

    long long byteIndex = 0;
    while (byteIndex < size)
    {
        if (byteIndex + sizeof(Employee) <= size)
        {
            Employee* employee = new Employee;
            memcpy(employee, memblock + byteIndex, sizeof(Employee));
            allEmployee.push_back(employee);
            byteIndex += sizeof(Employee);
        }
        else
        {
            cerr << "Error: Incomplete data in file." << endl;
            break;
        }
    }

    delete[] memblock;
    return allEmployee;
}


int main()
{
    Employee test;
    test.name = "Marwan";
    test.salary = 129;
    test.position = "S-F";

    addTobin(test, FILE_PATH);
    vector<Employee*> allEmployee = readFromBin(FILE_PATH);
    // Iterate through each employee in the vector
    for (auto employeePtr : allEmployee) {
        std::cout << "Name: " << employeePtr->name << "\n";
        std::cout << "Salary: " << employeePtr->salary << "\n";
        std::cout << "Position: " << employeePtr->position << "\n";
        std::cout << "---------------------------\n"; // Optional separator
    }
    for (auto employeePtr : allEmployee) {
        delete employeePtr;
    }

    return 0;
}


    //try {
        //if (file)
        //{
        //}
        //else
        //    cerr << "Cannot open " << file_path << "!\n";
    //}
    //catch (exception& e) {
        //cerr << "error when we add to the file {" << e.what() << "}" << endl;
    //}