#include <iostream>
using namespace std;

class ReadableStorageDevice
{
    public:
        virtual void read() = 0;
        virtual ~ReadableStorageDevice() = default; 
};
class WritableStorageDevice
{
    public:
        virtual void write() = 0;
        virtual ~WritableStorageDevice() = default; 
};
class HardDisk: public ReadableStorageDevice, WritableStorageDevice
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
class ReadOnlyMemory: public ReadableStorageDevice
{
    public:
    void read() override
    {
        cout << "\nReading data from the ROM\n";
    }
};
int main()
{
    HardDisk hardDisk;
    ReadOnlyMemory rom;

    hardDisk.read();
    hardDisk.write();

    rom.read();
    //rom.write(); //error
    
    return 0;
}   