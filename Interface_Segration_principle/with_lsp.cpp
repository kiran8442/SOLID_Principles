#include <iostream>
using namespace std;

class IPrinter
{
    public:
    virtual void print() = 0; 
};
class IScanner
{
    public:
    virtual void scan() = 0;
};
class IFax
{
    public:
    virtual void fax() = 0;
};
class BasicPrinter: public IPrinter
{
    public:
    void print() override
    {
        cout<< "\nPrinting using Basic Printer\n";
    }
};
class AdvancePrinter: public IPrinter, 
                      public IScanner, 
                      public IFax
{
    public:
    void print() override
    {
        cout<< "\nPrinting using Advance Printer\n";
    }
    void scan() override
    {
        cout<< "\nScanning using Advance Printer\n";
    }
    void fax() override
    {
        cout<< "\nFax using Advance Printer\n";
    }
};
int main()
{
    AdvancePrinter printer1;
    printer1.print();
    printer1.scan();
    printer1.fax();

    BasicPrinter printer2;
    printer2.print();
    return 0;
}