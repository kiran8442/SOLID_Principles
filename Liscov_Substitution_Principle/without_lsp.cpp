#include <iostream>
#include <stdexcept>
using namespace std;

class StorageDevice
{
    public:
        virtual void read() = 0;
        virtual void write() =  0;
        virtual ~StorageDevice() = default; 
};
class HardDisk: public StorageDevice
{
    public:
    void read() override
    {
        cout << "\nReading data from the harddisk\n";
    }
    void write() override
    {
        cout << "\nWriting data to the harddisk\n";
    }
};
class ReadOnlyMemory: public StorageDevice
{
    public:
    void read() override
    {
        cout << "\nReading data from the ROM\n";
    }
    void write() override
    {
        throw runtime_error("Write operation is not supported in the ROM\n");
    }
};
int main()
{
    HardDisk hardDisk;
    ReadOnlyMemory rom;

    hardDisk.read();
    hardDisk.write();

    rom.read();
    rom.write(); // this is the problem
    
    return 0;
}   