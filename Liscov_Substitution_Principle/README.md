# Liskov Substitution Principle — LSP

## What is Liskov Substitution Principle?

The **Liskov Substitution Principle** says:

> An object of a derived class should be able to replace an object of its base class without breaking the expected behavior of the program.

In simple words:

> **If Child is derived from Parent, then Child should behave correctly wherever Parent is used.**

So if we have:

```text
Parent
  |
  ↓
Child
```

and the program expects a `Parent`, we should be able to pass a `Child` object without causing incorrect behavior.

---

# Simple Meaning

Suppose we have:

```cpp
class Bird
{
public:
    virtual void fly() = 0;
};
```

Then we create:

```text
Bird
 |
 ├── Sparrow
 |
 └── Penguin
```

A `Sparrow` can fly.

But a `Penguin` cannot fly.

So if `Penguin` inherits from `Bird` and is forced to implement `fly()`, our inheritance design becomes incorrect.

For example:

```cpp
class Penguin : public Bird
{
public:
    void fly() override
    {
        cout << "Penguin cannot fly" << endl;
    }
};
```

This is a design problem.

The base class promises:

```text
Bird can fly
```

but `Penguin` cannot satisfy that behavior.

---

# Issue Before Applying LSP

Consider this base class:

```cpp
class Bird
{
public:
    virtual void fly() const = 0;

    virtual ~Bird() = default;
};
```

Now:

```cpp
class Sparrow : public Bird
{
public:
    void fly() const override
    {
        cout << "Sparrow is flying" << endl;
    }
};
```

This is fine.

But then:

```cpp
class Penguin : public Bird
{
public:
    void fly() const override
    {
        cout << "Penguin cannot fly" << endl;
    }
};
```

Now suppose we have:

```cpp
void makeBirdFly(const Bird& bird)
{
    bird.fly();
}
```

And call:

```cpp
Sparrow sparrow;
Penguin penguin;

makeBirdFly(sparrow);
makeBirdFly(penguin);
```

Output:

```text
Sparrow is flying
Penguin cannot fly
```

The second case violates the expectation of `makeBirdFly()`.

The function expects every `Bird` passed to it to support flying.

---

# What is Wrong Here?

The inheritance relationship was designed incorrectly.

We assumed:

```text
All Birds can fly
```

But this is not true.

So this hierarchy:

```text
        Bird
         |
    -----------
    |         |
 Sparrow   Penguin
```

is incorrect if `Bird` requires `fly()`.

---

# Main Idea Behind LSP

Inheritance should be based on **behavior**, not only on real-world classification.

Real-world statement:

```text
Penguin is a Bird
```

is true.

But in software design, if our `Bird` abstraction means:

```text
Something that can fly
```

then:

```text
Penguin IS NOT a valid substitute
```

for that abstraction.

This is the important part.

---

# Better Design

We can separate general bird behavior from flying behavior.

For example:

```text
               Bird
              /    \
             /      \
      FlyingBird   Penguin
           |
        Sparrow
```

Now:

```cpp
class Bird
{
public:
    virtual void eat() const = 0;

    virtual ~Bird() = default;
};
```

Flying birds can have another abstraction:

```cpp
class FlyingBird : public Bird
{
public:
    virtual void fly() const = 0;
};
```

Then:

```cpp
class Sparrow : public FlyingBird
{
public:
    void eat() const override
    {
        cout << "Sparrow is eating" << endl;
    }

    void fly() const override
    {
        cout << "Sparrow is flying" << endl;
    }
};
```

And:

```cpp
class Penguin : public Bird
{
public:
    void eat() const override
    {
        cout << "Penguin is eating" << endl;
    }
};
```

Now `Penguin` is no longer forced to provide behavior it cannot support.

---

# Code Without LSP

```cpp
#include <iostream>

using namespace std;

class Bird
{
public:
    virtual void fly() const = 0;

    virtual ~Bird() = default;
};

class Sparrow : public Bird
{
public:
    void fly() const override
    {
        cout << "Sparrow is flying" << endl;
    }
};

class Penguin : public Bird
{
public:
    void fly() const override
    {
        cout << "Penguin cannot fly" << endl;
    }
};

void makeBirdFly(const Bird& bird)
{
    bird.fly();
}

int main()
{
    Sparrow sparrow;
    Penguin penguin;

    makeBirdFly(sparrow);

    makeBirdFly(penguin);

    return 0;
}
```

---

# Problem in the Above Code

`makeBirdFly()` expects:

```text
Bird
 ↓
Can Fly
```

But when we pass:

```text
Penguin
```

the expected behavior is not satisfied.

So `Penguin` cannot correctly substitute `Bird`.

---

# After Applying LSP

Create separate abstractions for separate capabilities.

```cpp
#include <iostream>

using namespace std;

class Bird
{
public:
    virtual void eat() const = 0;

    virtual ~Bird() = default;
};

class FlyingBird : public Bird
{
public:
    virtual void fly() const = 0;
};

class Sparrow : public FlyingBird
{
public:
    void eat() const override
    {
        cout << "Sparrow is eating" << endl;
    }

    void fly() const override
    {
        cout << "Sparrow is flying" << endl;
    }
};

class Penguin : public Bird
{
public:
    void eat() const override
    {
        cout << "Penguin is eating" << endl;
    }
};

void feedBird(const Bird& bird)
{
    bird.eat();
}

void makeBirdFly(const FlyingBird& bird)
{
    bird.fly();
}

int main()
{
    Sparrow sparrow;
    Penguin penguin;

    feedBird(sparrow);
    feedBird(penguin);

    makeBirdFly(sparrow);

    return 0;
}
```

Now the design is correct.

---

# How Does This Follow LSP?

Consider:

```cpp
void feedBird(const Bird& bird)
```

Both:

```text
Sparrow
Penguin
```

can replace `Bird`.

Because both correctly support:

```cpp
eat()
```

So:

```cpp
feedBird(sparrow);
feedBird(penguin);
```

works correctly.

---

But:

```cpp
void makeBirdFly(const FlyingBird& bird)
```

accepts only birds that actually support flying.

Therefore:

```cpp
makeBirdFly(sparrow);
```

is valid.

But:

```cpp
makeBirdFly(penguin);
```

is not allowed by the design.

This prevents incorrect behavior.

---

# Another Simple Example

Consider a rectangle and square.

We create:

```cpp
class Rectangle
{
protected:
    int width;
    int height;

public:
    virtual void setWidth(int w)
    {
        width = w;
    }

    virtual void setHeight(int h)
    {
        height = h;
    }

    int getArea() const
    {
        return width * height;
    }
};
```

Then:

```cpp
class Square : public Rectangle
{
public:
    void setWidth(int w) override
    {
        width = w;
        height = w;
    }

    void setHeight(int h) override
    {
        width = h;
        height = h;
    }
};
```

At first this seems logical because:

```text
Square is a Rectangle
```

But there is a problem.

---

# Expected Rectangle Behavior

Suppose:

```cpp
void resize(Rectangle& rectangle)
{
    rectangle.setWidth(5);
    rectangle.setHeight(10);

    cout << rectangle.getArea() << endl;
}
```

For a normal `Rectangle`:

```text
Width = 5
Height = 10

Area = 50
```

So:

```cpp
Rectangle rectangle;

resize(rectangle);
```

prints:

```text
50
```

---

# What Happens With Square?

Now:

```cpp
Square square;

resize(square);
```

First:

```cpp
square.setWidth(5);
```

sets:

```text
width = 5
height = 5
```

Then:

```cpp
square.setHeight(10);
```

sets:

```text
width = 10
height = 10
```

Area becomes:

```text
100
```

But `resize()` expected:

```text
50
```

So replacing `Rectangle` with `Square` changes the expected behavior.

This violates LSP.

---

# What Does LSP Really Protect?

LSP protects the **behavioral contract** of the base class.

Suppose the base class promises:

```text
Do X
```

The derived class should also correctly do:

```text
X
```

It should not:

```text
Ignore X
Throw unexpected errors
Change the meaning of X
Disable X
Produce completely different behavior
```

---

# Common LSP Violation

Suppose:

```cpp
class File
{
public:
    virtual void read() = 0;
    virtual void write() = 0;
};
```

Then:

```cpp
class ReadOnlyFile : public File
{
public:
    void read() override
    {
        cout << "Reading file" << endl;
    }

    void write() override
    {
        throw runtime_error("Cannot write to read-only file");
    }
};
```

This may indicate a design problem.

The base class says:

```text
File supports read + write
```

but `ReadOnlyFile` does not support writing.

So `ReadOnlyFile` cannot completely replace `File`.

---

# Better Design

Separate the capabilities:

```text
IReadable
   |
   ├── NormalFile
   └── ReadOnlyFile


IWritable
   |
   └── NormalFile
```

Example:

```cpp
class IReadable
{
public:
    virtual void read() const = 0;

    virtual ~IReadable() = default;
};

class IWritable
{
public:
    virtual void write() = 0;

    virtual ~IWritable() = default;
};
```

Then:

```cpp
class NormalFile : public IReadable, public IWritable
{
public:
    void read() const override
    {
        cout << "Reading file" << endl;
    }

    void write() override
    {
        cout << "Writing file" << endl;
    }
};
```

And:

```cpp
class ReadOnlyFile : public IReadable
{
public:
    void read() const override
    {
        cout << "Reading read-only file" << endl;
    }
};
```

Now each class supports only valid behavior.

---

# Rules to Follow for LSP

A derived class should respect the expectations created by the base class.

Some important points are:

## 1. Do Not Remove Base-Class Behavior

If the base class supports:

```cpp
start()
```

the derived class should not do:

```cpp
void start() override
{
    throw exception;
}
```

just because that derived type cannot start.

That usually means the inheritance hierarchy is wrong.

---

## 2. Do Not Change the Meaning of a Function

Suppose:

```cpp
class Account
{
public:
    virtual void withdraw(double amount);
};
```

A derived class should not interpret:

```cpp
withdraw(100)
```

as:

```text
Deposit 100
```

The basic behavior should remain consistent.

---

## 3. Do Not Introduce Unexpected Restrictions

Suppose a base class accepts:

```text
Any positive amount
```

but the derived class suddenly accepts only:

```text
Amount greater than 1000
```

This may violate expectations.

---

## 4. Preserve Expected Results

If code works correctly using the base class, replacing it with a derived class should not suddenly produce logically incorrect results.

---

# How to Identify LSP Violation?

Ask:

> Can I replace the base object with this derived object without changing the correctness of the program?

If the answer is:

```text
No
```

then the inheritance design may violate LSP.

---

# Warning Signs

Look for derived classes containing things like:

```cpp
throw runtime_error("Not supported");
```

or:

```cpp
void someFunction() override
{
    // do nothing
}
```

or:

```cpp
void someFunction() override
{
    cout << "This operation is not available";
}
```

These can indicate that the derived class cannot actually satisfy the base-class contract.

---

# LSP Is Not Only About Compilation

This is important.

Suppose:

```cpp
Bird& bird = penguin;
```

compiles successfully.

That does **not** automatically mean LSP is satisfied.

LSP is about:

```text
Correct behavior
```

not only:

```text
Correct syntax
```

The code may compile and still violate LSP.

---

# Inheritance vs LSP

Whenever we use inheritance:

```text
Base
  |
Derived
```

we should ask:

```text
Is Derived really capable of behaving like Base?
```

Not just:

```text
Is Derived somehow related to Base?
```

This is why:

```text
IS-A
```

should represent a behavioral relationship.

---

# Benefits of LSP

## Correct Inheritance

LSP helps us create meaningful inheritance hierarchies.

---

## Safe Polymorphism

Base references and pointers can safely refer to derived objects.

Example:

```cpp
Bird* bird = new Sparrow();
```

The caller can trust that the expected `Bird` behavior is supported.

---

## Fewer Runtime Surprises

We avoid derived classes that unexpectedly:

```text
Throw errors
Ignore operations
Change expected behavior
```

---

## Cleaner Abstractions

The base class contains only behavior that all valid derived classes can support.

---

# Common Mistake

A common mistake is creating inheritance only because two things look related in the real world.

For example:

```text
Penguin is a Bird
Square is a Rectangle
ReadOnlyFile is a File
```

These statements may be logically true in the real world.

But software inheritance requires something stronger:

> The derived type must satisfy the behavior expected from the base type.

---

# Easy Way to Remember

```text
L = Liskov Substitution Principle
```

Remember:

```text
Parent Expected
      ↓
Child Provided
      ↓
Program Should Still Work Correctly
```

Or simply:

> **Child should correctly replace Parent.**

---

# Before vs After LSP

| Before LSP                                 | After LSP                                     |
| ------------------------------------------ | --------------------------------------------- |
| Derived class cannot support base behavior | Derived class supports expected base behavior |
| Unsupported functions may exist            | Interfaces contain valid capabilities         |
| Runtime surprises                          | Predictable behavior                          |
| Wrong inheritance hierarchy                | Correct hierarchy                             |
| Polymorphism may break behavior            | Safe polymorphism                             |

---

# Summary

Liskov Substitution Principle says:

> A derived class should be usable in place of its base class without breaking the expected behavior of the program.

The main idea is:

```text
Base Class
    ↑
Derived Class

Derived object replaces Base object
              ↓
Program still behaves correctly
```

Bad design:

```text
Bird
 |
 ├── Sparrow → can fly
 |
 └── Penguin → cannot fly
```

when `Bird` requires:

```cpp
fly()
```

Better design:

```text
             Bird
            /    \
           /      \
    FlyingBird   Penguin
         |
      Sparrow
```

Now every derived class supports the behavior promised by its parent.

The easiest sentence to remember is:

> **If B is derived from A, B should be able to replace A without breaking the program.**
