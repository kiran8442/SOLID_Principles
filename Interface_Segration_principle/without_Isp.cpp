#include <iostream>
using namespace std;

class IDevice
{
    public:
    virtual ~IDevice() = default;
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};
class BasicPrinter: public IDevice
{
    public:
    void print() override
    {
        cout<< "\nPrinting using Basic Printer\n";
    }
    void scan() override
    {
        cout<< "\nScanning is not supported with Basic Printer \n";
    }
    void fax() override
    {
        cout<< "\nFax is not supported with Basic Printer \n";
    }
};
class AdvancePrinter: public IDevice
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
    printer2.scan(); // problem is here
    printer2.fax(); // problem is here
    return 0;
}