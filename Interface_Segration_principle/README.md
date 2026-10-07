# Interface Segregation Principle — ISP

## What is Interface Segregation Principle?

The **Interface Segregation Principle** says:

> A class should not be forced to implement methods that it does not need.

In simple words:

> **Instead of one large interface, create small and focused interfaces.**

A class should implement only the behavior that is actually required by it.

---

# Simple Meaning

Suppose we have one large interface:

```cpp
class IDevice
{
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};
```

Now we create:

```text
MultiFunctionPrinter
SimplePrinter
```

A `MultiFunctionPrinter` can:

```text
print
scan
fax
```

But a `SimplePrinter` may support only:

```text
print
```

Still, because `SimplePrinter` inherits from `IDevice`, it is forced to implement:

```cpp
scan()
fax()
```

even though it cannot support those operations.

That is the problem ISP tries to solve.

---

# Issue Before Applying ISP

Consider:

```cpp
class IOfficeMachine
{
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;

    virtual ~IOfficeMachine() = default;
};
```

Now we create:

```cpp
class MultiFunctionPrinter : public IOfficeMachine
{
public:
    void print() override
    {
        cout << "Printing document" << endl;
    }

    void scan() override
    {
        cout << "Scanning document" << endl;
    }

    void fax() override
    {
        cout << "Sending fax" << endl;
    }
};
```

This class is fine because it supports all the operations.

But now:

```cpp
class BasicPrinter : public IOfficeMachine
{
public:
    void print() override
    {
        cout << "Printing document" << endl;
    }

    void scan() override
    {
        cout << "Scan not supported" << endl;
    }

    void fax() override
    {
        cout << "Fax not supported" << endl;
    }
};
```

This is a design problem.

`BasicPrinter` is being forced to implement functions it does not need.

---

# Main Problem

Our interface is too large.

```text
IOfficeMachine
      |
      ├── print()
      ├── scan()
      └── fax()
```

Every class inheriting from it must implement all three operations.

Even if the class supports only one of them.

---

# Idea Behind ISP

Break one large interface into multiple small interfaces.

Instead of:

```text
IOfficeMachine
      |
      ├── print()
      ├── scan()
      └── fax()
```

create:

```text
IPrinter
   |
 print()

IScanner
   |
 scan()

IFax
   |
 fax()
```

Now each class implements only what it actually supports.

---

# After Applying ISP

We create small interfaces.

## Printer Interface

```cpp
class IPrinter
{
public:
    virtual void print() = 0;

    virtual ~IPrinter() = default;
};
```

## Scanner Interface

```cpp
class IScanner
{
public:
    virtual void scan() = 0;

    virtual ~IScanner() = default;
};
```

## Fax Interface

```cpp
class IFax
{
public:
    virtual void fax() = 0;

    virtual ~IFax() = default;
};
```

---

# BasicPrinter

A basic printer only prints.

So:

```cpp
class BasicPrinter : public IPrinter
{
public:
    void print() override
    {
        cout << "Printing document" << endl;
    }
};
```

It is no longer forced to implement:

```text
scan()
fax()
```

---

# MultiFunctionPrinter

A multifunction printer can support everything:

```cpp
class MultiFunctionPrinter : public IPrinter,
                             public IScanner,
                             public IFax
{
public:
    void print() override
    {
        cout << "Printing document" << endl;
    }

    void scan() override
    {
        cout << "Scanning document" << endl;
    }

    void fax() override
    {
        cout << "Sending fax" << endl;
    }
};
```

This class chooses all three interfaces because it actually supports all three behaviors.

---

# Code Without ISP

```cpp
#include <iostream>

using namespace std;

class IOfficeMachine
{
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;

    virtual ~IOfficeMachine() = default;
};

class MultiFunctionPrinter : public IOfficeMachine
{
public:
    void print() override
    {
        cout << "Printing document" << endl;
    }

    void scan() override
    {
        cout << "Scanning document" << endl;
    }

    void fax() override
    {
        cout << "Sending fax" << endl;
    }
};

class BasicPrinter : public IOfficeMachine
{
public:
    void print() override
    {
        cout << "Printing document" << endl;
    }

    void scan() override
    {
        cout << "Scan not supported" << endl;
    }

    void fax() override
    {
        cout << "Fax not supported" << endl;
    }
};

int main()
{
    MultiFunctionPrinter multiPrinter;
    BasicPrinter basicPrinter;

    multiPrinter.print();
    multiPrinter.scan();
    multiPrinter.fax();

    basicPrinter.print();
    basicPrinter.scan();
    basicPrinter.fax();

    return 0;
}
```

---

# What is Wrong With This Code?

`BasicPrinter` is forced to implement:

```cpp
scan()
fax()
```

even though it does not support them.

That is unnecessary.

We are making the class depend on methods it does not need.

---

# Code After Applying ISP

```cpp
#include <iostream>

using namespace std;

class IPrinter
{
public:
    virtual void print() = 0;

    virtual ~IPrinter() = default;
};

class IScanner
{
public:
    virtual void scan() = 0;

    virtual ~IScanner() = default;
};

class IFax
{
public:
    virtual void fax() = 0;

    virtual ~IFax() = default;
};

class BasicPrinter : public IPrinter
{
public:
    void print() override
    {
        cout << "Printing document" << endl;
    }
};

class ScannerDevice : public IScanner
{
public:
    void scan() override
    {
        cout << "Scanning document" << endl;
    }
};

class MultiFunctionPrinter : public IPrinter,
                             public IScanner,
                             public IFax
{
public:
    void print() override
    {
        cout << "Printing document" << endl;
    }

    void scan() override
    {
        cout << "Scanning document" << endl;
    }

    void fax() override
    {
        cout << "Sending fax" << endl;
    }
};

int main()
{
    BasicPrinter basicPrinter;
    ScannerDevice scanner;
    MultiFunctionPrinter multiPrinter;

    basicPrinter.print();

    scanner.scan();

    multiPrinter.print();
    multiPrinter.scan();
    multiPrinter.fax();

    return 0;
}
```

---

# Design Before ISP

```text
             IOfficeMachine
                    |
        --------------------------
        |                        |
BasicPrinter             MultiFunctionPrinter
    |                           |
    ├── print()                  ├── print()
    ├── scan() ❌                ├── scan()
    └── fax()  ❌                └── fax()
```

The problem is that `BasicPrinter` gets methods it does not need.

---

# Design After ISP

```text
IPrinter
   |
   ├── BasicPrinter
   └── MultiFunctionPrinter


IScanner
   |
   ├── ScannerDevice
   └── MultiFunctionPrinter


IFax
   |
   └── MultiFunctionPrinter
```

Now every class gets only the functionality it actually supports.

---

# What Does "Interface" Mean Here?

In C++, an interface is usually represented using an abstract class containing pure virtual functions.

Example:

```cpp
class IPrinter
{
public:
    virtual void print() = 0;

    virtual ~IPrinter() = default;
};
```

This tells derived classes:

> If you implement `IPrinter`, you must provide printing behavior.

---

# Why Large Interfaces Become a Problem

Suppose an interface grows like this:

```cpp
class IRobot
{
public:
    virtual void move() = 0;
    virtual void lift() = 0;
    virtual void scanQR() = 0;
    virtual void charge() = 0;
    virtual void connectWifi() = 0;
    virtual void detectObstacle() = 0;
};
```

Now imagine a small robot that only supports:

```text
move
detectObstacle
```

It is still forced to implement:

```text
lift
scanQR
charge
connectWifi
```

This is a sign that the interface is too large.

---

# Better Design

Split the capabilities:

```text
IMovable
   |
 move()

ILiftable
   |
 lift()

IQRScanner
   |
 scanQR()

IChargeable
   |
 charge()

IWifiDevice
   |
 connectWifi()

IObstacleDetector
   |
 detectObstacle()
```

Now a robot can implement only the required capabilities.

For example:

```cpp
class SimpleRobot : public IMovable,
                    public IObstacleDetector
{
};
```

While another robot may implement:

```cpp
class WarehouseRobot : public IMovable,
                       public ILiftable,
                       public IChargeable,
                       public IObstacleDetector
{
};
```

This is much more flexible.

---

# How to Identify ISP Violation?

Look for derived classes containing methods like:

```cpp
void scan() override
{
    // Not supported
}
```

or:

```cpp
void fax() override
{
    throw runtime_error("Not supported");
}
```

or empty implementations:

```cpp
void connectWifi() override
{
}
```

These are signs that the class may have been forced to implement an interface that is too large.

---

# Another Sign

If you frequently say:

```text
This class implements the interface,
but it only needs 2 out of 10 functions.
```

then the interface probably needs to be split.

---

# Important Point

ISP does not mean:

> Every interface must contain only one function.

That would be unnecessary.

For example:

```cpp
class IFileReader
{
public:
    virtual void open() = 0;
    virtual void read() = 0;
    virtual void close() = 0;
};
```

These functions are closely related to one responsibility.

So keeping them together can be completely valid.

The important idea is:

> Keep interfaces focused around a specific capability or responsibility.

---

# ISP and Multiple Inheritance

In C++, ISP often naturally leads to multiple inheritance of interfaces.

For example:

```cpp
class MultiFunctionPrinter :
    public IPrinter,
    public IScanner,
    public IFax
{
};
```

This is different from inheriting implementation from multiple concrete classes.

Here we are combining small behavioral contracts.

---

# Benefits of ISP

## 1. No Unnecessary Functions

Classes implement only what they need.

---

## 2. Cleaner Design

Each interface has a clear purpose.

---

## 3. Easier Changes

Changing scanner functionality does not affect printer-only classes.

---

## 4. Better Reusability

Small interfaces can be combined as required.

---

## 5. Easier Testing

We can test each capability separately.

---

## 6. Lower Coupling

Classes do not depend on functions they never use.

---

# Common Mistake

Do not split interfaces unnecessarily.

For example:

```text
IOpenFile
IReadFile
ICloseFile
```

may be too fragmented if these operations always belong together.

The goal is not:

```text
Smallest possible interface
```

The goal is:

```text
Focused interface
```

---

# Easy Way to Remember

```text
I = Interface Segregation Principle
```

Remember:

> **Do not force a class to implement functions it does not need.**

Or:

```text
Large Interface
      ↓
Split into
      ↓
Small Focused Interfaces
```

---

# Before vs After ISP

| Before ISP                            | After ISP                               |
| ------------------------------------- | --------------------------------------- |
| One large interface                   | Multiple focused interfaces             |
| Classes implement unnecessary methods | Classes implement only required methods |
| Unsupported operations appear         | Unsupported operations disappear        |
| Higher coupling                       | Lower coupling                          |
| Harder to maintain                    | Easier to maintain                      |

---

# Summary

Interface Segregation Principle says:

> A class should not be forced to depend on or implement methods that it does not need.

Instead of:

```text
IOfficeMachine
      |
      ├── print()
      ├── scan()
      └── fax()
```

create:

```text
IPrinter
   ↓
print()


IScanner
   ↓
scan()


IFax
   ↓
fax()
```

Then each class chooses only the required interfaces.

The easiest way to remember ISP is:

> **Prefer small, focused interfaces over one large general-purpose interface.**
