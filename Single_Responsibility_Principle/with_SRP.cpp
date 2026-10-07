#include <iostream>
#include <string>

using namespace std;


// Employee has only one responsibility:
// Store employee information.
class Employee
{
private:
    int empId;
    string empName;
    double basicSalary;

public:
    Employee(int id, const string& name, double salary)
        : empId(id), empName(name), basicSalary(salary)
    {
    }

    int getId() const
    {
        return empId;
    }

    const string& getName() const
    {
        return empName;
    }

    double getBasicSalary() const
    {
        return basicSalary;
    }
};

// Responsible only for salary calculation.
class SalaryCalculator
{
    public:
    double calculateSalary(const Employee& employee)
    {
        const double allowance = 5000.0;
        return employee.getBasicSalary() + allowance;
    }
};

// Responsible only for storing employee information.
class EmployeeRepository
{
public:
    void saveToFile(const Employee& employee) const
    {
        cout << "Saving employee "
             << employee.getName()
             << " into file"
             << endl;
    }
};

// Responsible only for sending emails.
class EmailService
{
public:
    void sendEmail(const Employee& employee) const
    {
        cout << "Sending email to "
             << employee.getName()
             << endl;
    }
};

// Responsible only for displaying employee information
class EmployeePrinter
{
    public:
    void print(const Employee& employee) const
    {
        cout << "Employee ID   : "
             << employee.getId()
             << endl;

        cout << "Employee Name : "
             << employee.getName()
             << endl;

        cout << "Basic Salary  : "
             << employee.getBasicSalary()
             << endl;
    }
};
int main()
{
    Employee employee(101, "Kiran", 50000);

    EmployeePrinter printer;
    SalaryCalculator salaryCalculator;
    EmployeeRepository repository;
    EmailService emailService;

    printer.print(employee);

    double finalSalary =
        salaryCalculator.calculateSalary(employee);

    cout << "Final Salary   : "
         << finalSalary
         << endl;

    repository.saveToFile(employee);

    emailService.sendEmail(employee);

    return 0;
}