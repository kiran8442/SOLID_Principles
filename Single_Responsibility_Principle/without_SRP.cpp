#include <iostream>
#include <string>

using namespace std;
class Employee
{
    string EmpName;
    int EmpId;
    double basicSalary;
    public:
    Employee( int id,const string& name, double salary):
                EmpName(name), EmpId(id), basicSalary(salary)
    {

    }

    void displayEmployee() const
    {
        cout << "Employee ID   : " << EmpId << endl;
        cout << "Employee Name : " << EmpName << endl;
        cout << "Basic Salary  : " << basicSalary << endl;
    }

    double calculateSalary() const
    {
        return basicSalary + 5000;
    }

    void saveToFile() const
    {
        cout << "Saving employee "
             << EmpName
             << " into file"
             << endl;
    }

    void sendEmail() const
    {
        cout << "Sending email to "
             << EmpName
             << endl;
    }
};
int main()
{
    Employee employee(101, "kiran", 50000);

    employee.displayEmployee();

    cout << "Final Salary   : "
         << employee.calculateSalary()
         << endl;

    employee.saveToFile();

    employee.sendEmail();

    return 0;
}