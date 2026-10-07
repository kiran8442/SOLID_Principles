# SOLID Principles in C++

This repository is created to understand the **SOLID Principles** in a simple and practical way using **C++**.

SOLID is a set of **5 object-oriented design principles** that help us write code that is:

* Easy to understand
* Easy to modify
* Easy to test
* Easy to maintain
* Easy to extend
* Less tightly coupled
* More reusable

The word **SOLID** comes from the first letter of five principles:

| Letter | Principle                       |
| ------ | ------------------------------- |
| **S**  | Single Responsibility Principle |
| **O**  | Open/Closed Principle           |
| **L**  | Liskov Substitution Principle   |
| **I**  | Interface Segregation Principle |
| **D**  | Dependency Inversion Principle  |

---

# Why Do We Need SOLID?

Suppose we develop an application without following any design principles.

Initially, the code may look simple.

But as the project grows, we may start facing problems like:

* One class doing too many things
* Changing one feature breaks another feature
* Adding a new feature requires modifying existing working code
* Classes become highly dependent on each other
* Testing becomes difficult
* Code becomes difficult to understand
* Reusing code becomes difficult

SOLID principles help us avoid these problems.

The main idea is:

> **Write software in such a way that future changes become easier and safer.**

---

# 1. Single Responsibility Principle — SRP

> **A class should have only one responsibility or one reason to change.**

In simple words:

**One class should do one main job.**

For example, suppose we have an `Employee` class.

If the same class:

* stores employee information
* calculates salary
* saves employee data into a database
* sends email

then the class is handling too many responsibilities.

Instead, we can separate them into different classes.

Example:

```text
Employee
    ↓
Stores employee information

SalaryCalculator
    ↓
Calculates salary

EmployeeRepository
    ↓
Stores employee information

EmailService
    ↓
Sends email
```

Now every class has a clear responsibility.

### Main Idea

```text
One Class
   ↓
One Responsibility
```

Detailed explanation and examples:

```text
01_Single_Responsibility_Principle/
```

---

# 2. Open/Closed Principle — OCP

> **Software entities should be open for extension but closed for modification.**

In simple words:

**We should be able to add new functionality without changing existing working code.**

Suppose we have:

```cpp
if(type == "CAN")
{
    // CAN logic
}
else if(type == "ETH")
{
    // Ethernet logic
}
```

Later if we add:

```text
LIN
FlexRay
MQTT
```

we have to keep modifying the same code.

This increases the chance of breaking existing functionality.

Instead, we can design the system using abstraction.

Example:

```text
        IReader
        /     \
       /       \
CANReader     ETHReader
                 \
                LINReader
```

To add another reader, we simply create another implementation.

Existing code does not need major modification.

### Main Idea

```text
New Requirement
      ↓
Add New Code

Instead of

New Requirement
      ↓
Modify Existing Working Code
```

Detailed explanation and examples:

```text
02_Open_Closed_Principle/
```

---

# 3. Liskov Substitution Principle — LSP

> **A derived class should be usable wherever its base class is expected without breaking the program.**

In simple words:

**Child classes must correctly behave like their parent class.**

Suppose we have:

```text
Bird
 |
 +---- Sparrow
 |
 +---- Penguin
```

If the `Bird` class provides:

```cpp
fly();
```

then `Penguin` becomes a problem because penguins cannot fly.

This means our inheritance design is wrong.

Instead, we should create proper abstractions.

Example:

```text
          Bird
         /    \
        /      \
FlyingBird    Penguin
    |
 Sparrow
```

Now only birds that can actually fly implement flying behaviour.

### Main Idea

If:

```text
DerivedClass IS-A BaseClass
```

then the derived class should correctly support the behaviour expected from the base class.

Detailed explanation and examples:

```text
03_Liskov_Substitution_Principle/
```

---

# 4. Interface Segregation Principle — ISP

> **A class should not be forced to implement methods that it does not need.**

In simple words:

**Do not create one huge interface containing unrelated functions.**

Suppose we have:

```cpp
class IWorker
{
public:

    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
};
```

Now suppose we create a:

```text
RobotWorker
```

A robot can:

```text
work()
```

but it may not:

```text
eat()
sleep()
```

Still, because of the large interface, the robot is forced to implement those functions.

Instead, interfaces should be smaller.

Example:

```text
IWorkable
    |
   work()

IEatable
    |
   eat()

ISleepable
    |
   sleep()
```

Now classes implement only the interfaces they actually need.

### Main Idea

```text
Large Interface
      ↓
Split into
      ↓
Small Specific Interfaces
```

Detailed explanation and examples:

```text
04_Interface_Segregation_Principle/
```

---

# 5. Dependency Inversion Principle — DIP

> **High-level modules should not directly depend on low-level modules. Both should depend on abstractions.**

In simple words:

**Classes should depend on interfaces instead of directly depending on concrete classes.**

Suppose:

```text
Application
     |
     ↓
CANReader
```

Here the application directly depends on `CANReader`.

Later if we want:

```text
EthernetReader
```

we may need to modify the application.

Instead:

```text
Application
     |
     ↓
   IReader
   /     \
  /       \
CANReader ETHReader
```

Now the application depends on:

```text
IReader
```

instead of directly depending on:

```text
CANReader
```

This makes the application flexible.

### Important Terms

**High-level module**

The main business logic of the application.

Example:

```text
CommunicationManager
Application
Controller
```

**Low-level module**

Classes that perform actual implementation details.

Example:

```text
CANReader
EthernetReader
FileReader
Database
```

**Abstraction**

Usually an interface or abstract class.

Example:

```cpp
class IReader
{
public:
    virtual void read() = 0;
};
```

### Main Idea

Instead of:

```text
High Level
    ↓
Low Level
```

Use:

```text
High Level
    ↓
Abstraction
    ↑
Low Level
```

Detailed explanation and examples:

```text
05_Dependency_Inversion_Principle/
```

---

# SOLID in One Line

The easiest way to remember SOLID:

| Principle | Simple Meaning                                    |
| --------- | ------------------------------------------------- |
| **SRP**   | One class should have one responsibility          |
| **OCP**   | Add new behaviour without changing existing code  |
| **LSP**   | Child class should correctly replace parent class |
| **ISP**   | Keep interfaces small and specific                |
| **DIP**   | Depend on interfaces, not concrete classes        |

---

# Simple Memory Trick

```text
S → Single Job

O → Open to Add, Closed to Change

L → Child Must Behave Like Parent

I → Small Interfaces

D → Depend on Abstraction
```

---

# Repository Structure

```text
SOLID-Principles/
│
├── README.md
│
├── 01_Single_Responsibility_Principle/
│   ├── README.md
│   └── examples/
│
├── 02_Open_Closed_Principle/
│   ├── README.md
│   └── examples/
│
├── 03_Liskov_Substitution_Principle/
│   ├── README.md
│   └── examples/
│
├── 04_Interface_Segregation_Principle/
│   ├── README.md
│   └── examples/
│
└── 05_Dependency_Inversion_Principle/
    ├── README.md
    └── examples/
```

Each principle folder will contain:

```text
1. What is the principle?
2. Problem before applying the principle
3. Idea behind the principle
4. What problem does it solve?
5. Code without the principle
6. Problems in that code
7. Refactored code using the principle
8. Step-by-step explanation
9. Real-world C++ example
10. Advantages
11. When to use it
12. Common mistakes
13. Summary
14. Interview questions
```

---

# Final Summary

SOLID does not mean that every class must always follow some strict fixed structure.

The purpose of SOLID is to make software:

```text
Easy to Change
      +
Easy to Extend
      +
Easy to Test
      +
Easy to Maintain
```

The five principles work together:

```text
SRP
 ↓
Keep responsibilities separate

OCP
 ↓
Allow extension without modifying existing code

LSP
 ↓
Design inheritance correctly

ISP
 ↓
Keep interfaces focused

DIP
 ↓
Reduce dependency between concrete classes
```

Together, these principles help us build **clean, flexible and maintainable C++ software**.
