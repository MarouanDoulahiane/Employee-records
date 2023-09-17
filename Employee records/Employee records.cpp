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
    try {
        ifstream file(file_path, ios::binary | ios::ate);
        if (file)
        {
            streampos size = file.tellg();
            char* memblock = new char[size];
            file.read(memblock, size);
            file.close();

            long long byteIndex = 0;
            while (byteIndex < size)
            {
                Employee* employee = (Employee*)(memblock + byteIndex);
                allEmployee.push_back(employee);
                byteIndex += sizeof(Employee);
            }
        }
        else
            cerr << "Cannot open " << file_path << "!\n";
    }
    catch (exception& e) {
        cerr << "error when we add to the file {" << e.what() << "}" << endl;
    }
    return allEmployee;
}

int main()
{
    Employee name;
    name.name = "Marwan";
    name.salary = 120;
    name.position = "S.E";
    addTobin(name, FILE_PATH);
    std::cout << name.name << "\n";
    std::cout << name.salary << "\n";
    std::cout << name.position << "\n";
    return 0;
}