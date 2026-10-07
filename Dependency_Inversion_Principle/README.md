# Dependency Inversion Principle — DIP

## Before Understanding DIP

Before understanding **Dependency Inversion Principle**, we need to understand four things:

1. What is a high-level module?
2. What is a low-level module?
3. What is a dependency?
4. What is an abstraction?

Once these are clear, DIP becomes much easier.

---

# 1. What is a High-Level Module?

A **high-level module** contains the main logic or main decision-making part of the application.

In simple words:

> A high-level module decides **what needs to be done**.

Example:

Suppose we are building a notification system.

We have:

```text
NotificationManager
```

Its job is:

```text
Send notification to user
```

It does not need to care whether the notification is sent using:

```text
Email
SMS
WhatsApp
```

Its main responsibility is simply:

```text
Send Notification
```

So:

```text
NotificationManager
```

is a **high-level module**.

---

# Another Example

Suppose we have:

```text
CommunicationManager
```

Its responsibility is:

```text
Receive some data
Process that data
Continue application flow
```

It should not care too much about exactly where the data comes from.

The data may come from:

```text
CAN
Ethernet
Serial
File
```

So `CommunicationManager` is a high-level module.

---

# High-Level Module in Simple Words

Remember:

```text
High-Level Module
        ↓
Main Application Logic
        ↓
What needs to be done
```

Examples:

```text
NotificationManager
PaymentService
CommunicationManager
OrderManager
RobotController
```

---

# 2. What is a Low-Level Module?

A **low-level module** contains implementation details.

In simple words:

> A low-level module knows **how something is actually done**.

For our notification example:

```text
EmailService
SMSService
```

are low-level modules.

Why?

Because they contain the actual implementation of sending the notification.

For example:

```cpp
class EmailService
{
public:
    void sendEmail()
    {
        cout << "Sending Email" << endl;
    }
};
```

This class knows exactly:

```text
How email is sent
```

So it is a low-level module.

---

# Another Example

Suppose we have:

```text
CANReader
EthernetReader
SerialReader
```

These classes know how to read data from specific communication technologies.

So they are low-level modules.

---

# Low-Level Module in Simple Words

Remember:

```text
Low-Level Module
        ↓
Implementation Details
        ↓
How something is done
```

Examples:

```text
EmailService
SMSService
CANReader
EthernetReader
MySQLDatabase
FileLogger
```

---

# High-Level vs Low-Level

The easiest way to understand them:

```text
High-Level Module
        ↓
WHAT to do


Low-Level Module
        ↓
HOW to do it
```

Example:

```text
NotificationManager
        ↓
Send Notification

EmailService
        ↓
How to send using Email
```

Another example:

```text
CommunicationManager
        ↓
Get incoming data

CANReader
        ↓
How to get data from CAN
```

---

# 3. What is a Dependency?

Suppose one class directly creates or uses another specific class.

Example:

```cpp
class EmailService
{
public:
    void send()
    {
        cout << "Sending Email" << endl;
    }
};
```

Now:

```cpp
class NotificationManager
{
private:
    EmailService emailService;

public:
    void notifyUser()
    {
        emailService.send();
    }
};
```

Here:

```text
NotificationManager
```

depends directly on:

```text
EmailService
```

We can say:

```text
NotificationManager
        ↓
depends on
        ↓
EmailService
```

This means `NotificationManager` is tightly connected to `EmailService`.

---

# Why Can This Become a Problem?

Suppose currently we send notifications using:

```text
Email
```

Later requirement changes:

```text
Use SMS
```

Now we create:

```cpp
class SMSService
{
public:
    void sendSMS()
    {
        cout << "Sending SMS" << endl;
    }
};
```

But `NotificationManager` directly uses:

```cpp
EmailService
```

So we need to modify `NotificationManager`.

Before:

```cpp
EmailService emailService;
```

After:

```cpp
SMSService smsService;
```

And:

```cpp
emailService.send();
```

becomes:

```cpp
smsService.sendSMS();
```

Our high-level module needs modification just because the low-level implementation changed.

That is the main problem DIP tries to solve.

---

# Current Design

Without DIP:

```text
NotificationManager
        |
        ↓
   EmailService
```

Here:

```text
High-Level Module
        ↓
directly depends on
        ↓
Low-Level Module
```

This creates tight coupling.

---

# What is Tight Coupling?

Tight coupling means:

> One class strongly depends on the exact implementation of another class.

For example:

```cpp
EmailService service;
```

means:

```text
I specifically need EmailService.
```

If tomorrow we want:

```text
SMSService
WhatsAppService
PushNotificationService
```

we may have to modify the high-level module again.

---

# 4. What is an Abstraction?

An abstraction is a common contract between classes.

In C++, we normally create abstraction using an abstract class or interface.

Example:

```cpp
class INotificationService
{
public:
    virtual void send() = 0;

    virtual ~INotificationService() = default;
};
```

This interface does not say:

```text
How Email works
How SMS works
```

It simply says:

```text
Any notification service must provide send()
```

Now different classes can implement it.

```cpp
class EmailService : public INotificationService
{
public:
    void send() override
    {
        cout << "Sending Email" << endl;
    }
};
```

And:

```cpp
class SMSService : public INotificationService
{
public:
    void send() override
    {
        cout << "Sending SMS" << endl;
    }
};
```

Now both follow the same contract:

```text
INotificationService
        |
        ├── EmailService
        └── SMSService
```

---

# Now Understand Dependency Inversion Principle

The Dependency Inversion Principle says:

> High-level modules should not depend directly on low-level modules. Both should depend on abstractions.

In simple words:

> The main application logic should depend on an interface, not on a specific implementation.

---

# Without DIP

We have:

```text
NotificationManager
        |
        ↓
   EmailService
```

High-level module:

```text
NotificationManager
```

Low-level module:

```text
EmailService
```

Direct dependency exists.

---

# With DIP

We introduce an abstraction:

```text
       INotificationService
          ↑             ↑
          |             |
 EmailService       SMSService
          ^
          |
 NotificationManager
```

A simpler way to visualize:

```text
NotificationManager
        |
        ↓
INotificationService
        ↑
        |
---------------------
|                   |
EmailService     SMSService
```

Now `NotificationManager` does not care about the exact notification type.

It only knows:

```text
I need something that can send a notification.
```

---

# Issue Before Applying DIP

Consider:

```cpp
class EmailService
{
public:
    void sendEmail()
    {
        cout << "Sending Email" << endl;
    }
};
```

Now our high-level class:

```cpp
class NotificationManager
{
private:
    EmailService emailService;

public:
    void sendNotification()
    {
        emailService.sendEmail();
    }
};
```

This works.

But the problem appears when requirements change.

---

# Requirement Changes

Suppose we now want:

```text
SMS
```

Instead of:

```text
Email
```

We have to modify:

```cpp
NotificationManager
```

That means:

```text
Low-level implementation changed
        ↓
High-level business logic also changed
```

This creates unnecessary dependency.

---

# Main Problem

The design looks like:

```text
High-Level Module
NotificationManager
        |
        ↓
Low-Level Module
EmailService
```

The high-level module knows too much about the implementation.

It knows:

```text
We are specifically using EmailService.
```

---

# Idea Behind DIP

The high-level module should not care which implementation is being used.

It should only say:

```text
Give me something that can send a notification.
```

So we introduce:

```cpp
INotificationService
```

Now the high-level module depends on this abstraction.

---

# Code Without DIP

```cpp
#include <iostream>

using namespace std;

class EmailService
{
public:
    void sendEmail()
    {
        cout << "Sending Email" << endl;
    }
};

class NotificationManager
{
private:
    EmailService emailService;

public:
    void sendNotification()
    {
        emailService.sendEmail();
    }
};

int main()
{
    NotificationManager manager;

    manager.sendNotification();

    return 0;
}
```

---

# Problem in This Code

`NotificationManager` directly depends on:

```cpp
EmailService
```

So:

```text
NotificationManager
        ↓
EmailService
```

If the low-level implementation changes, the high-level class also changes.

---

# After Applying DIP

First create the abstraction:

```cpp
class INotificationService
{
public:
    virtual void send() = 0;

    virtual ~INotificationService() = default;
};
```

Now implement it:

```cpp
class EmailService : public INotificationService
{
public:
    void send() override
    {
        cout << "Sending Email" << endl;
    }
};
```

And:

```cpp
class SMSService : public INotificationService
{
public:
    void send() override
    {
        cout << "Sending SMS" << endl;
    }
};
```

Now change `NotificationManager`.

Instead of:

```cpp
EmailService emailService;
```

we use:

```cpp
INotificationService& service;
```

---

# NotificationManager After DIP

```cpp
class NotificationManager
{
private:
    INotificationService& service;

public:
    NotificationManager(INotificationService& service)
        : service(service)
    {
    }

    void sendNotification()
    {
        service.send();
    }
};
```

Now `NotificationManager` does not know whether the object is:

```text
EmailService
SMSService
WhatsAppService
PushNotificationService
```

It only knows:

```text
INotificationService
```

---

# Complete Code After Applying DIP

```cpp
#include <iostream>

using namespace std;

class INotificationService
{
public:
    virtual void send() = 0;

    virtual ~INotificationService() = default;
};

class EmailService : public INotificationService
{
public:
    void send() override
    {
        cout << "Sending Email" << endl;
    }
};

class SMSService : public INotificationService
{
public:
    void send() override
    {
        cout << "Sending SMS" << endl;
    }
};

class NotificationManager
{
private:
    INotificationService& service;

public:
    NotificationManager(INotificationService& service)
        : service(service)
    {
    }

    void sendNotification()
    {
        service.send();
    }
};

int main()
{
    EmailService emailService;

    NotificationManager emailManager(emailService);

    emailManager.sendNotification();


    SMSService smsService;

    NotificationManager smsManager(smsService);

    smsManager.sendNotification();

    return 0;
}
```

Output:

```text
Sending Email
Sending SMS
```

---

# What Changed?

Before DIP:

```text
NotificationManager
        ↓
EmailService
```

After DIP:

```text
NotificationManager
        ↓
INotificationService
        ↑
        |
-----------------
|               |
EmailService   SMSService
```

This is the most important diagram for DIP.

---

# Why is it Called Dependency "Inversion"?

Before DIP:

```text
High-Level
    ↓
Low-Level
```

The high-level class directly depends on the low-level class.

Example:

```text
NotificationManager
        ↓
EmailService
```

After DIP:

```text
High-Level
    ↓
Abstraction
    ↑
Low-Level
```

Example:

```text
NotificationManager
        ↓
INotificationService
        ↑
EmailService
```

The dependency direction has changed.

That is why it is called:

```text
Dependency Inversion
```

---

# Important Point

Do not misunderstand this diagram:

```text
INotificationService
        ↑
EmailService
```

It means:

```text
EmailService implements INotificationService
```

Now both high-level and low-level code are connected through an abstraction.

---

# Another Example: Communication System

Suppose we have:

```text
CommunicationManager
```

And currently data comes from:

```text
CANReader
```

Without DIP:

```cpp
class CANReader
{
public:
    void read()
    {
        cout << "Reading CAN frame" << endl;
    }
};
```

Then:

```cpp
class CommunicationManager
{
private:
    CANReader reader;

public:
    void receiveData()
    {
        reader.read();
    }
};
```

Here:

```text
CommunicationManager
        ↓
CANReader
```

---

# What Happens Later?

Suppose we want:

```text
EthernetReader
```

Now `CommunicationManager` must change.

Then later:

```text
SerialReader
```

Again it changes.

This is tight coupling.

---

# Better Design

Create:

```cpp
class IDataReader
{
public:
    virtual void read() = 0;

    virtual ~IDataReader() = default;
};
```

Then:

```cpp
class CANReader : public IDataReader
{
public:
    void read() override
    {
        cout << "Reading CAN frame" << endl;
    }
};
```

And:

```cpp
class EthernetReader : public IDataReader
{
public:
    void read() override
    {
        cout << "Reading Ethernet frame" << endl;
    }
};
```

Now:

```cpp
class CommunicationManager
{
private:
    IDataReader& reader;

public:
    CommunicationManager(IDataReader& reader)
        : reader(reader)
    {
    }

    void receiveData()
    {
        reader.read();
    }
};
```

Now:

```text
CommunicationManager
        ↓
IDataReader
        ↑
        |
---------------------
|                   |
CANReader       EthernetReader
```

---

# High-Level and Low-Level in This Example

High-level:

```text
CommunicationManager
```

Why?

Because it handles the main application logic:

```text
Receive data
```

Low-level:

```text
CANReader
EthernetReader
```

Why?

Because they contain details about:

```text
HOW to read data
```

Abstraction:

```text
IDataReader
```

It defines:

```text
Something capable of reading data
```

---

# Very Simple Real-Life Analogy

Think about an electrical appliance.

Suppose a laptop directly depended on one specific power station.

That would be strange.

Instead the laptop depends on:

```text
Power Socket Standard
```

Different power sources can provide electricity through that standard.

In software:

```text
Laptop
    ↓
Socket Interface
    ↑
Power Source
```

Similarly:

```text
NotificationManager
        ↓
INotificationService
        ↑
EmailService
```

The high-level module cares about the contract, not the exact implementation.

---

# Dependency Injection and DIP

You may notice this code:

```cpp
NotificationManager(INotificationService& service)
    : service(service)
{
}
```

We are passing the dependency from outside.

This is called:

```text
Dependency Injection
```

Dependency Injection is commonly used to implement DIP.

---

# Without Dependency Injection

The class creates its own dependency:

```cpp
class NotificationManager
{
private:
    EmailService service;
};
```

This means:

```text
NotificationManager decides the implementation.
```

---

# With Dependency Injection

```cpp
class NotificationManager
{
private:
    INotificationService& service;

public:
    NotificationManager(INotificationService& service)
        : service(service)
    {
    }
};
```

Now:

```text
Someone outside decides which implementation to provide.
```

For example:

```cpp
EmailService email;

NotificationManager manager(email);
```

or:

```cpp
SMSService sms;

NotificationManager manager(sms);
```

---

# DIP vs Dependency Injection

These two terms are related, but they are not exactly the same.

## DIP

DIP is a **design principle**.

It says:

```text
Depend on abstraction
instead of concrete implementation
```

---

## Dependency Injection

Dependency Injection is a **technique**.

It means:

```text
Pass the required dependency from outside
```

Example:

```cpp
NotificationManager(INotificationService& service)
```

Dependency Injection helps us follow DIP.

---

# How to Identify DIP Violation?

Look for high-level classes creating concrete low-level objects directly.

Example:

```cpp
class CommunicationManager
{
private:
    CANReader reader;
};
```

Ask:

```text
Does CommunicationManager really need CANReader specifically?
```

If the actual requirement is only:

```text
I need something that can read data
```

then an abstraction may be better.

---

# Another Warning Sign

If you frequently change:

```cpp
EmailService
```

to:

```cpp
SMSService
```

inside the high-level class, then the high-level class is probably too dependent on implementation details.

---

# DIP Does Not Mean Every Class Needs an Interface

Do not create interfaces unnecessarily.

For example:

```text
ICalculator
Calculator
```

may add no value if there will only ever be one simple calculator implementation.

Use abstraction where implementations may vary or where decoupling provides real value.

---

# Benefits of DIP

## 1. Lower Coupling

High-level logic is not tightly connected to specific implementations.

---

## 2. Easy to Replace Implementation

We can switch:

```text
Email
```

to:

```text
SMS
```

without changing `NotificationManager`.

---

## 3. Easier Extension

New implementations can be added.

Example:

```cpp
class WhatsAppService : public INotificationService
{
public:
    void send() override
    {
        cout << "Sending WhatsApp message" << endl;
    }
};
```

No change required inside `NotificationManager`.

---

## 4. Easier Testing

Because `NotificationManager` depends on an interface, we can provide a fake implementation.

Example:

```cpp
class FakeNotificationService : public INotificationService
{
public:
    void send() override
    {
        cout << "Fake notification" << endl;
    }
};
```

Then:

```cpp
FakeNotificationService fake;

NotificationManager manager(fake);
```

We do not need a real email or SMS service just to test `NotificationManager`.

---

## 5. Better Maintainability

Implementation details remain separated from main application logic.

---

# Easy Way to Remember

Remember these two questions:

```text
High Level
    ↓
WHAT should happen?


Low Level
    ↓
HOW does it happen?
```

And DIP says:

```text
High Level
    ↓
Do not depend directly on HOW
    ↓
Depend on an abstraction
```

---

# Before vs After DIP

| Without DIP                          | With DIP                          |
| ------------------------------------ | --------------------------------- |
| High-level depends on concrete class | High-level depends on abstraction |
| Tight coupling                       | Loose coupling                    |
| Difficult to replace implementation  | Easy to replace implementation    |
| High-level class changes frequently  | High-level logic remains stable   |
| Harder to test                       | Easier to test                    |

---

# Most Important Diagram

Without DIP:

```text
High-Level Module
        |
        ↓
Low-Level Module
```

Example:

```text
NotificationManager
        |
        ↓
EmailService
```

With DIP:

```text
High-Level Module
        |
        ↓
   Abstraction
        ↑
        |
Low-Level Module
```

Example:

```text
NotificationManager
        |
        ↓
INotificationService
        ↑
        |
   EmailService
```

With multiple implementations:

```text
                 INotificationService
                       ↑       ↑
                       |       |
                EmailService  SMSService
                       ↑
                       |
              NotificationManager
```

Or more simply:

```text
NotificationManager
        ↓
INotificationService
        ↑
   -------------
   |           |
EmailService SMSService
```

---

# One-Line Understanding

The easiest way to remember DIP is:

> **Do not depend on the exact class. Depend on what that class can do.**

Example:

Do not say:

```text
I need EmailService.
```

Say:

```text
I need something that can send a notification.
```

That "something" is represented by:

```cpp
INotificationService
```

---

# Summary

Dependency Inversion Principle says:

> High-level modules should not directly depend on low-level modules. Both should depend on abstractions.

First remember:

```text
High-Level Module
        ↓
WHAT to do


Low-Level Module
        ↓
HOW to do it
```

Without DIP:

```text
NotificationManager
        ↓
EmailService
```

The high-level module is directly coupled to the low-level implementation.

With DIP:

```text
NotificationManager
        ↓
INotificationService
        ↑
        |
-----------------
|               |
EmailService   SMSService
```

Now the high-level module only knows:

```text
I need a notification service.
```

It does not care:

```text
Email?
SMS?
WhatsApp?
Push Notification?
```

The most important sentence to remember is:

> **High-level logic should depend on abstraction, not on implementation details.**
