# Open/Closed Principle — OCP

## What is Open/Closed Principle?

The **Open/Closed Principle** says:

> Software entities should be open for extension but closed for modification.

In simple words:

> **We should be able to add new functionality without changing existing working code again and again.**

The goal is to reduce unnecessary modification of already tested code.

---

# Simple Meaning

Suppose we have a payment system.

Initially, it supports:

```text
Credit Card
```

Later we want to add:

```text
UPI
Net Banking
Wallet
```

If every new payment type requires us to modify the same existing function, then our design is not following OCP properly.

Instead, we should design the code so that new payment types can be added by creating new classes.

---

# Issue Before Applying OCP

Consider this code:

```cpp
class PaymentProcessor
{
public:
    void processPayment(const string& paymentType)
    {
        if(paymentType == "CreditCard")
        {
            cout << "Processing Credit Card payment" << endl;
        }
        else if(paymentType == "UPI")
        {
            cout << "Processing UPI payment" << endl;
        }
    }
};
```

Initially it supports:

```text
CreditCard
UPI
```

Now suppose we want to add:

```text
NetBanking
```

We need to modify the existing class:

```cpp
else if(paymentType == "NetBanking")
{
    cout << "Processing Net Banking payment" << endl;
}
```

Later we add:

```text
Wallet
PayPal
Crypto
```

Again and again we have to modify the same class.

---

# What is Wrong With This Design?

The problem is:

```text
New Requirement
      ↓
Modify Existing Class
      ↓
Retest Existing Class
      ↓
Risk of Breaking Existing Logic
```

Every new payment type changes `PaymentProcessor`.

So the class is not closed for modification.

---

# Main Problem

The design looks like:

```text
PaymentProcessor
       |
       ├── CreditCard logic
       ├── UPI logic
       ├── NetBanking logic
       ├── Wallet logic
       └── More future logic
```

As the number of payment types increases, the class keeps growing.

---

# Idea Behind OCP

Instead of putting all payment logic inside one class, create an abstraction.

For example:

```text
        IPayment
           |
     ----------------
     |       |      |
     ↓       ↓      ↓
CreditCard  UPI   NetBanking
```

Each payment type provides its own implementation.

Now when we want a new payment type, we create a new class.

Existing payment classes do not need modification.

---

# What Does "Open for Extension" Mean?

It means:

> We can add new behavior.

Example:

```text
Existing:
CreditCardPayment
UPIPayment

New Requirement:
WalletPayment
```

We can extend the system by adding:

```cpp
class WalletPayment : public IPayment
{
};
```

---

# What Does "Closed for Modification" Mean?

It does **not** mean that we can never modify existing code.

It means:

> We should avoid modifying stable, already working code every time a new feature is added.

For example:

```text
Adding Wallet Payment
```

should ideally not require changing:

```text
CreditCardPayment
UPIPayment
Payment processing logic
```

---

# Code Without OCP

```cpp
#include <iostream>
#include <string>

using namespace std;

class PaymentProcessor
{
public:
    void processPayment(const string& paymentType)
    {
        if(paymentType == "CreditCard")
        {
            cout << "Processing Credit Card payment" << endl;
        }
        else if(paymentType == "UPI")
        {
            cout << "Processing UPI payment" << endl;
        }
        else if(paymentType == "NetBanking")
        {
            cout << "Processing Net Banking payment" << endl;
        }
    }
};

int main()
{
    PaymentProcessor processor;

    processor.processPayment("CreditCard");
    processor.processPayment("UPI");
    processor.processPayment("NetBanking");

    return 0;
}
```

---

# Problem in the Above Code

Suppose tomorrow we need:

```text
Wallet
```

We must modify:

```cpp
PaymentProcessor::processPayment()
```

Then add:

```cpp
else if(paymentType == "Wallet")
{
    cout << "Processing Wallet payment" << endl;
}
```

Every new payment type changes the same function.

That is the main issue.

---

# After Applying OCP

We create a common abstraction:

```cpp
class IPayment
{
public:
    virtual void process() const = 0;

    virtual ~IPayment() = default;
};
```

Now each payment type implements this interface.

---

# CreditCardPayment

```cpp
class CreditCardPayment : public IPayment
{
public:
    void process() const override
    {
        cout << "Processing Credit Card payment" << endl;
    }
};
```

---

# UPIPayment

```cpp
class UPIPayment : public IPayment
{
public:
    void process() const override
    {
        cout << "Processing UPI payment" << endl;
    }
};
```

---

# NetBankingPayment

```cpp
class NetBankingPayment : public IPayment
{
public:
    void process() const override
    {
        cout << "Processing Net Banking payment" << endl;
    }
};
```

---

# PaymentProcessor

Now `PaymentProcessor` depends only on the abstraction:

```cpp
class PaymentProcessor
{
public:
    void processPayment(const IPayment& payment)
    {
        payment.process();
    }
};
```

It does not need to know whether the payment is:

```text
CreditCard
UPI
NetBanking
Wallet
```

---

# Complete Code After Applying OCP

```cpp
#include <iostream>

using namespace std;


class IPayment
{
public:
    virtual void process() const = 0;

    virtual ~IPayment() = default;
};


class CreditCardPayment : public IPayment
{
public:
    void process() const override
    {
        cout << "Processing Credit Card payment" << endl;
    }
};


class UPIPayment : public IPayment
{
public:
    void process() const override
    {
        cout << "Processing UPI payment" << endl;
    }
};


class NetBankingPayment : public IPayment
{
public:
    void process() const override
    {
        cout << "Processing Net Banking payment" << endl;
    }
};


class PaymentProcessor
{
public:
    void processPayment(const IPayment& payment)
    {
        payment.process();
    }
};


int main()
{
    PaymentProcessor processor;

    CreditCardPayment creditCard;
    UPIPayment upi;
    NetBankingPayment netBanking;

    processor.processPayment(creditCard);
    processor.processPayment(upi);
    processor.processPayment(netBanking);

    return 0;
}
```

---

# Now Add a New Requirement

Suppose we want:

```text
Wallet Payment
```

We create:

```cpp
class WalletPayment : public IPayment
{
public:
    void process() const override
    {
        cout << "Processing Wallet payment" << endl;
    }
};
```

Then:

```cpp
WalletPayment wallet;

processor.processPayment(wallet);
```

We did not modify:

```text
CreditCardPayment
UPIPayment
NetBankingPayment
PaymentProcessor
```

We only added new code.

---

# This is the Main Idea of OCP

Without OCP:

```text
New Requirement
      ↓
Modify Existing Code
```

With OCP:

```text
New Requirement
      ↓
Add New Class
```

---

# Design Before OCP

```text
PaymentProcessor
      |
      ├── if CreditCard
      ├── else if UPI
      ├── else if NetBanking
      └── else if Wallet
```

---

# Design After OCP

```text
                   IPayment
                       |
        --------------------------------
        |              |               |
        ↓              ↓               ↓
CreditCardPayment   UPIPayment   NetBankingPayment
                                       |
                                       |
                              Future implementations
```

And:

```text
PaymentProcessor
       |
       ↓
    IPayment
```

---

# Why This Design is Better

Each payment type owns its own behavior.

For example:

```text
CreditCardPayment
        ↓
Credit Card logic

UPIPayment
        ↓
UPI logic

WalletPayment
        ↓
Wallet logic
```

Adding one payment type does not affect another.

---

# Real-World C++ Example

Consider a communication system.

Initially, we support:

```text
CAN
Ethernet
```

Without OCP:

```cpp
class FrameReader
{
public:
    void read(const string& type)
    {
        if(type == "CAN")
        {
            cout << "Reading CAN frame" << endl;
        }
        else if(type == "ETH")
        {
            cout << "Reading Ethernet frame" << endl;
        }
    }
};
```

Later we want to add:

```text
LIN
FlexRay
Serial
```

Every new type requires changing `FrameReader`.

---

# Better Design

Create:

```cpp
class IFrameReader
{
public:
    virtual void read() const = 0;

    virtual ~IFrameReader() = default;
};
```

Then:

```text
IFrameReader
     |
     ├── CANReader
     ├── EthernetReader
     ├── LINReader
     └── SerialReader
```

Example:

```cpp
class CANReader : public IFrameReader
{
public:
    void read() const override
    {
        cout << "Reading CAN frame" << endl;
    }
};


class EthernetReader : public IFrameReader
{
public:
    void read() const override
    {
        cout << "Reading Ethernet frame" << endl;
    }
};
```

Later:

```cpp
class LINReader : public IFrameReader
{
public:
    void read() const override
    {
        cout << "Reading LIN frame" << endl;
    }
};
```

Existing readers remain unchanged.

---

# How to Identify OCP Violation?

Look for code like:

```cpp
if(type == ...)
else if(type == ...)
else if(type == ...)
```

or:

```cpp
switch(type)
{
    case ...
    case ...
    case ...
}
```

This does not automatically mean the code is bad.

But if every new feature requires adding another condition to the same class, it may indicate an OCP problem.

---

# Another Common Sign

Suppose you frequently say:

```text
Whenever we add a new type,
we must modify this same class.
```

That class may need a better abstraction.

---

# OCP Does Not Mean "Never Use If/Switch"

This is important.

OCP does **not** say:

```text
Never use if
Never use switch
```

Conditions are normal programming constructs.

The problem is when:

```text
Every new implementation
        ↓
Requires modifying the same large conditional logic
```

---

# Benefits of OCP

## 1. Easier Extension

New functionality can be added using new classes.

---

## 2. Existing Code Remains Stable

Already working code requires fewer changes.

---

## 3. Reduced Risk

Adding one new implementation is less likely to break another implementation.

---

## 4. Better Maintainability

Different behaviors remain separated.

---

## 5. Better Testing

Each implementation can be tested independently.

---

# Common Mistake

Do not create abstraction for every small thing just because of OCP.

For example:

```text
IAddTwoNumbers
AddTwoNumbersImpl
```

may be unnecessary if the behavior is simple and unlikely to vary.

Create abstractions when there is a real possibility of multiple implementations or changing behavior.

---

# Important Relationship With Polymorphism

OCP is often implemented using:

```text
Abstraction
Inheritance
Virtual Functions
Runtime Polymorphism
```

Example:

```cpp
IPayment& payment
```

At runtime, it may refer to:

```text
CreditCardPayment
UPIPayment
WalletPayment
```

The caller does not need to know the exact implementation.

---

# Easy Way to Remember

```text
O = Open for Extension
C = Closed for Modification
```

Meaning:

```text
New Feature
    ↓
Add New Code

Avoid

New Feature
    ↓
Keep Changing Existing Stable Code
```

---

# Before vs After OCP

| Before OCP                             | After OCP                     |
| -------------------------------------- | ----------------------------- |
| One class contains logic for all types | Each type has its own class   |
| New type modifies existing code        | New type is added as new code |
| Large if/else chains                   | Polymorphic design            |
| Higher risk of breaking existing logic | Existing logic remains stable |
| Difficult to extend                    | Easier to extend              |

---

# Summary

The Open/Closed Principle says:

> Software should be open for extension but closed for modification.

The main goal is:

```text
Add new behavior
      ↓
Without repeatedly changing existing working code
```

Instead of:

```text
PaymentProcessor
      ↓
CreditCard + UPI + Wallet + NetBanking logic
```

use:

```text
IPayment
   |
   ├── CreditCardPayment
   ├── UPIPayment
   ├── WalletPayment
   └── NetBankingPayment
```

Then the main code works with:

```text
IPayment
```

rather than specific payment implementations.

This makes the system easier to extend, maintain, and test.
