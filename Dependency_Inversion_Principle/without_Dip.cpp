#include <iostream>

using namespace std;

class EmailService
{
    public:
    void sendEmail()
    {
        cout << "Sending Email\n";
    }
};

class NotificationManager 
{
    EmailService service;
    public:
    void sendNotification()
    {
        service.sendEmail();
    }
};

int main()
{
    NotificationManager manager;

    manager.sendNotification();

    return 0;
}