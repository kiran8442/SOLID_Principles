#include <iostream>

using namespace std;

class INotificationService
{
    public:
    virtual ~INotificationService() = default;
    virtual void send() = 0;
};
class EmailService : public INotificationService
{
    public:
    void send() override
    {
        cout << "Sending Email\n";
    }
};
class SMSService : public INotificationService
{
    public:
    void send() override
    {
        cout << "Sending SMS\n";
    }
};
class NotificationManager 
{
    INotificationService* service;
    public:
    NotificationManager(INotificationService* s): service(s)
    {

    }
    void sendNotification()
    {
        service->send();
    }
};

int main()
{
    //EmailService* emailservice;
    NotificationManager service1(new EmailService());
    service1.sendNotification();

    //SMSService smsservice;
    NotificationManager service2(new SMSService());
    service2.sendNotification();
    
    return 0;
}