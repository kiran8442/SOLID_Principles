# Single Responsibility Principle — SRP

## What is Single Responsibility Principle?

**Single Responsibility Principle** says:

> A class should have only one responsibility and only one reason to change.

In simple words:

> **One class should do one main job.**

A class should not handle multiple unrelated responsibilities.

For example, an `Employee` class should not:

* Store employee information
* Calculate employee salary
* Save employee data into a file
* Send employee notification

All of these are different responsibilities.

Instead, we should separate them into different classes.

---

# Simple Example

Suppose we create:

```cpp
class Employee
{
};
```

Initially, its responsibility is only:

```text
Store employee information
```

But later we start adding:

```text
Calculate salary
Save employee information
Print employee information
Send email
```

Now the same class is doing many different jobs.

This violates SRP.

---

# Issue Before Applying SRP

Consider this class:

```cpp
class Employee
{
private:

    int empId;
    string empName;
    double basicSalary;

public:

    Employee(int id, string name, double salary)
        : empId(id),
          empName(name),
          basicSalary(salary)
    {
    }

    double calculateSalary()
    {
        return basicSalary + 5000;
    }

    void saveToFile()
    {
        cout << "Saving employee information into file" << endl;
    }

    void sendEmail()
    {
        cout << "Sending email to employee" << endl;
    }

    void displayEmployee()
    {
        cout << "Employee ID   : " << empId << endl;
        cout << "Employee Name : " << empName << endl;
    }
};
```

At first sight, this may look fine.

But the `Employee` class is currently handling:

```text
Employee data
Salary calculation
File storage
Email communication
Display logic
```

These are completely different responsibilities.

---

# What is Wrong With This Design?

The class has multiple reasons to change.

For example:

### Requirement 1

Salary calculation changes.

We modify:

```cpp
Employee
```

### Requirement 2

Instead of saving employee data into a file, we want to save it into a database.

Again we modify:

```cpp
Employee
```

### Requirement 3

Email implementation changes.

Again:

```cpp
Employee
```

### Requirement 4

Employee information changes.

Again:

```cpp
Employee
```

So the class has many reasons to change.

That means it violates the Single Responsibility Principle.

---

# Main Problem

Our design looks like:

```text
                 Employee
                    |
        -----------------------------
        |           |        |      |
        ↓           ↓        ↓      ↓
      Data       Salary     File   Email
```

One class is controlling everything.

This creates **tight coupling between responsibilities**.

---

# Why Is This a Problem?

Suppose `Employee` contains 1000 lines of code.

Now the salary calculation team changes some logic.

While modifying the same class, they can accidentally affect:

```text
File saving
Email sending
Employee information
```

Even though those features had nothing to do with salary calculation.

This makes maintenance difficult.

---

# Idea Behind SRP

Separate different responsibilities into different classes.

Instead of:

```text
Employee
   |
   +--- Employee Data
   +--- Salary Calculation
   +--- File Storage
   +--- Email
```

We create:

```text
Employee
    |
    └── Employee Data


SalaryCalculator
    |
    └── Salary Calculation


EmployeeRepository
    |
    └── Employee Storage


EmailService
    |
    └── Email Communication
```

Now every class has one main responsibility.

---

# After Applying SRP

We can divide the previous class into separate classes.

---

## 1. Employee Class

The responsibility of `Employee` is only:

> Store and provide employee information.

```cpp
class Employee
{
private:

    int empId;
    string empName;
    double basicSalary;

public:

    Employee(int id, string name, double salary)
        : empId(id),
          empName(name),
          basicSalary(salary)
    {
    }

    int getId() const
    {
        return empId;
    }

    string getName() const
    {
        return empName;
    }

    double getBasicSalary() const
    {
        return basicSalary;
    }
};
```

This class does not:

```text
Calculate salary
Save file
Send email
```

It only represents employee information.

---

# 2. SalaryCalculator Class

The responsibility of this class is:

> Calculate employee salary.

```cpp
class SalaryCalculator
{
public:

    double calculateSalary(const Employee& employee)
    {
        return employee.getBasicSalary() + 5000;
    }
};
```

If salary calculation changes, we modify only:

```text
SalaryCalculator
```

We do not touch the `Employee` class.

---

# 3. EmployeeRepository Class

The responsibility of this class is:

> Store employee information.

```cpp
class EmployeeRepository
{
public:

    void saveToFile(const Employee& employee)
    {
        cout << "Saving employee "
             << employee.getName()
             << " into file"
             << endl;
    }
};
```

If storage changes from:

```text
File
```

to:

```text
Database
```

the employee model does not need to change.

---

# 4. EmailService Class

The responsibility of this class is:

> Send employee-related email.

```cpp
class EmailService
{
public:

    void sendEmail(const Employee& employee)
    {
        cout << "Sending email to "
             << employee.getName()
             << endl;
    }
};
```

If our email provider changes, only this class needs modification.

---

# Complete Code Without SRP

```cpp
#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:

    int empId;
    string empName;
    double basicSalary;

public:

    Employee(int id, string name, double salary)
        : empId(id),
          empName(name),
          basicSalary(salary)
    {
    }

    double calculateSalary()
    {
        return basicSalary + 5000;
    }

    void saveToFile()
    {
        cout << "Saving employee information into file" << endl;
    }

    void sendEmail()
    {
        cout << "Sending email to employee" << endl;
    }

    void displayEmployee()
    {
        cout << "Employee ID   : " << empId << endl;
        cout << "Employee Name : " << empName << endl;
    }
};

int main()
{
    Employee employee(101, "Suraj", 50000);

    employee.displayEmployee();

    cout << "Salary : "
         << employee.calculateSalary()
         << endl;

    employee.saveToFile();

    employee.sendEmail();

    return 0;
}
```

---

# Responsibilities in the Above Class

```text
Employee
   |
   ├── Store Employee Data
   |
   ├── Calculate Salary
   |
   ├── Save Employee
   |
   ├── Send Email
   |
   └── Display Employee
```

This is a clear SRP violation.

---

# Complete Code After Applying SRP

```cpp
#include <iostream>
#include <string>

using namespace std;


// ---------------------------------------------------
// Employee
// Responsibility:
// Store employee information
// ---------------------------------------------------

class Employee
{
private:

    int empId;
    string empName;
    double basicSalary;

public:

    Employee(int id, string name, double salary)
        : empId(id),
          empName(name),
          basicSalary(salary)
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


// ---------------------------------------------------
// SalaryCalculator
// Responsibility:
// Calculate employee salary
// ---------------------------------------------------

class SalaryCalculator
{
public:

    double calculateSalary(const Employee& employee)
    {
        const double allowance = 5000;

        return employee.getBasicSalary() + allowance;
    }
};


// ---------------------------------------------------
// EmployeeRepository
// Responsibility:
// Store employee information
// ---------------------------------------------------

class EmployeeRepository
{
public:

    void saveToFile(const Employee& employee)
    {
        cout << "Saving employee "
             << employee.getName()
             << " into file"
             << endl;
    }
};


// ---------------------------------------------------
// EmailService
// Responsibility:
// Send emails
// ---------------------------------------------------

class EmailService
{
public:

    void sendEmail(const Employee& employee)
    {
        cout << "Sending email to "
             << employee.getName()
             << endl;
    }
};


// ---------------------------------------------------
// EmployeePrinter
// Responsibility:
// Display employee information
// ---------------------------------------------------

class EmployeePrinter
{
public:

    void print(const Employee& employee)
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


// ---------------------------------------------------
// Main
// ---------------------------------------------------

int main()
{
    Employee employee(
        101,
        "Suraj",
        50000
    );

    SalaryCalculator salaryCalculator;

    EmployeeRepository repository;

    EmailService emailService;

    EmployeePrinter printer;


    printer.print(employee);


    double salary =
        salaryCalculator.calculateSalary(employee);

    cout << "Final Salary   : "
         << salary
         << endl;


    repository.saveToFile(employee);

    emailService.sendEmail(employee);


    return 0;
}
```

---

# Output

```text
Employee ID   : 101
Employee Name : Suraj
Basic Salary  : 50000
Final Salary  : 55000
Saving employee Suraj into file
Sending email to Suraj
```

---

# Design After Applying SRP

Now our design looks like:

```text
                    Employee
                       |
                       ↓
                 Employee Data


               SalaryCalculator
                       |
                       ↓
              Salary Calculation


             EmployeeRepository
                       |
                       ↓
                   Storage


                EmailService
                       |
                       ↓
                 Email Sending


              EmployeePrinter
                       |
                       ↓
                   Display
```

Every class has its own responsibility.

---

# What Does "One Reason to Change" Mean?

This is one of the most important parts of SRP.

SRP does **not** literally mean:

> A class should contain only one function.

A class can have multiple functions.

The important point is that those functions should belong to the **same responsibility**.

For example:

```cpp
class Employee
{
public:

    int getId() const;

    string getName() const;

    double getSalary() const;

    void setName(string name);
};
```

This class has multiple functions.

But all the functions are related to:

```text
Employee Information
```

Therefore, this class can still follow SRP.

---

# Wrong Understanding of SRP

Do not think:

```text
One Class = One Function
```

That is not SRP.

The correct understanding is:

```text
One Class = One Responsibility
```

For example:

```cpp
class FileManager
{
public:

    void openFile();

    void readFile();

    void writeFile();

    void closeFile();
};
```

This class has four functions.

But all four functions are related to:

```text
File Management
```

So it can still have a single responsibility.

---

# Real-World C++ Example

Suppose we are developing a communication application.

Without SRP:

```cpp
class CommunicationManager
{
public:

    void readCANFrame();

    void parseCANFrame();

    void saveFrameToFile();

    void sendFrameToServer();

    void printLogs();
};
```

This class is responsible for:

```text
CAN communication
Frame parsing
File storage
Network communication
Logging
```

That is too much responsibility for one class.

---

# Better Design

We can split it into:

```text
CANReader
    ↓
Reads CAN Frames


FrameParser
    ↓
Parses Frames


FrameRepository
    ↓
Stores Frames


ServerCommunication
    ↓
Sends Frames


Logger
    ↓
Handles Logs
```

Example:

```cpp
class CANReader
{
public:

    void readFrame()
    {
        cout << "Reading CAN frame" << endl;
    }
};


class FrameParser
{
public:

    void parseFrame()
    {
        cout << "Parsing CAN frame" << endl;
    }
};


class FrameRepository
{
public:

    void saveFrame()
    {
        cout << "Saving frame" << endl;
    }
};


class ServerCommunication
{
public:

    void sendFrame()
    {
        cout << "Sending frame to server" << endl;
    }
};


class Logger
{
public:

    void log()
    {
        cout << "Writing log" << endl;
    }
};
```

Each class now has one clear responsibility.

---

# How to Identify SRP Violation?

During code review, ask:

### Question 1

Can I describe this class using one simple sentence?

For example:

```text
Employee stores employee information.
```

Good.

But if the description becomes:

```text
Employee stores employee information,
calculates salary,
saves data,
prints reports,
and sends emails.
```

Then the class probably has too many responsibilities.

---

### Question 2

How many different reasons can cause this class to change?

Suppose:

```text
Salary policy changes
Database changes
Email provider changes
Employee information changes
```

If all of these require changing the same class, SRP is likely violated.

---

### Question 3

Does the class contain unrelated functionality?

Example:

```cpp
calculateSalary()

sendEmail()

saveToDatabase()

generatePDF()
```

These operations represent different responsibilities.

---

# SRP and Coupling

One benefit of SRP is reduced coupling.

Without SRP:

```text
Employee
   |
   ├── Database
   ├── Email
   ├── Salary
   └── Logging
```

The class may depend on many systems.

After SRP:

```text
Employee
   |
   ↓
Employee Information
```

Other responsibilities live in separate classes.

This makes the system easier to maintain.

---

# SRP and Testing

Suppose we have:

```cpp
class Employee
{
    calculateSalary();
    saveToDatabase();
    sendEmail();
};
```

Testing salary calculation might require dealing with:

```text
Database
Email
Other dependencies
```

This makes unit testing difficult.

After SRP:

```cpp
class SalaryCalculator
{
public:

    double calculateSalary(const Employee&);
};
```

Now we can test salary calculation independently.

Example:

```cpp
Employee employee(101, "Suraj", 50000);

SalaryCalculator calculator;

double salary =
    calculator.calculateSalary(employee);
```

No database.

No email.

No file handling.

Testing becomes much easier.

---

# SRP and Code Reusability

Suppose salary calculation exists inside:

```cpp
Employee
```

Another part of the application may have difficulty reusing it.

But when salary calculation exists inside:

```cpp
SalaryCalculator
```

we can reuse that class anywhere.

Example:

```text
Payroll Application
        |
        ↓
SalaryCalculator


HR Application
        |
        ↓
SalaryCalculator


Reporting Application
        |
        ↓
SalaryCalculator
```

---

# Advantages of SRP

## 1. Easy Maintenance

Each class has a clear purpose.

So finding the correct code becomes easier.

---

## 2. Easy Testing

Each responsibility can be tested independently.

---

## 3. Reduced Risk of Bugs

Changing salary calculation does not affect email functionality.

---

## 4. Better Readability

Class names clearly explain their purpose.

Example:

```text
SalaryCalculator
EmployeeRepository
EmailService
EmployeePrinter
```

---

## 5. Better Reusability

Small focused classes can be reused in different parts of the application.

---

## 6. Easier Team Development

Different developers can work on different responsibilities.

For example:

```text
Developer A
    ↓
SalaryCalculator

Developer B
    ↓
EmployeeRepository

Developer C
    ↓
EmailService
```

Changes are less likely to conflict.

---

# Can SRP Be Overused?

Yes.

We should not unnecessarily create hundreds of tiny classes.

For example, this would be unnecessary:

```text
EmployeeNameGetter

EmployeeIdGetter

EmployeeSalaryGetter
```

just because SRP says "single responsibility."

SRP means:

> Separate responsibilities that change for different reasons.

It does not mean:

> Create one class for every function.

---

# When Should We Apply SRP?

Consider applying SRP when:

* A class becomes very large
* A class handles multiple unrelated tasks
* A class changes frequently for different reasons
* Unit testing becomes difficult
* A class has many unrelated dependencies
* Multiple developers frequently modify the same class
* Small changes break unrelated functionality

---

# Interview Example

If the interviewer asks:

**What is the Single Responsibility Principle?**

A simple answer is:

> Single Responsibility Principle says that a class should have only one responsibility or one reason to change.

For example, an `Employee` class should only represent employee data. Salary calculation, database operations and email functionality should be handled by separate classes.

This makes the code easier to maintain, test and modify.

---

# Important Interview Question

## Does SRP mean one class should contain only one method?

**No.**

A class can contain multiple methods as long as all those methods belong to the same responsibility.

Example:

```cpp
class FileManager
{
public:

    void open();

    void read();

    void write();

    void close();
};
```

All these functions are related to file management.

So the class can still follow SRP.

---

# Before vs After SRP

| Before SRP                        | After SRP                    |
| --------------------------------- | ---------------------------- |
| One class handles many jobs       | Each class has a focused job |
| Difficult to maintain             | Easier to maintain           |
| Difficult to test                 | Easier to test               |
| Changes may affect unrelated code | Changes remain isolated      |
| High coupling                     | Lower coupling               |
| Large classes                     | Smaller focused classes      |

---

# Easy Way to Remember

Remember this sentence:

```text
One Class
   ↓
One Responsibility
   ↓
One Reason to Change
```

For example:

```text
Employee
    ↓
Employee Data


SalaryCalculator
    ↓
Salary Logic


EmployeeRepository
    ↓
Employee Storage


EmailService
    ↓
Email Sending
```

---

# Summary

**Single Responsibility Principle — SRP**

```text
S = Single Responsibility Principle
```

Main rule:

> A class should have only one responsibility and one reason to change.

Do not create:

```text
Employee
   ↓
Data + Salary + Database + Email + Printing
```

Instead create:

```text
Employee
        ↓
Employee Data

SalaryCalculator
        ↓
Salary Logic

EmployeeRepository
        ↓
Storage

EmailService
        ↓
Email

EmployeePrinter
        ↓
Display
```

The biggest benefit is:

```text
Change in one responsibility
          ↓
Changes only one class
          ↓
Other functionality remains unaffected
```

That makes the software easier to:

```text
Understand
Maintain
Test
Extend
Reuse
```
