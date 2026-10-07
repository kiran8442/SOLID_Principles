#include <iostream>
#include <string>
using namespace std;

class PaymentProcessor
{
    PaymentProcessor* payment;
    public:
    virtual ~PaymentProcessor() = default;
    virtual void processPayment() = 0;
};
class CreditCard: public PaymentProcessor
{
    public:
    void processPayment() override
    {
        cout << "Processing Credit Card Payment" << endl;
    }
};
class UPI: public PaymentProcessor
{
    public:
    void processPayment()  override
    {
        cout << "Processing Credit UPI Payment" << endl;
    }
};
class NetBanking: public PaymentProcessor
{
    public:
    void processPayment() override
    {
        cout << "Processing NetBanking Payment" << endl;
    }
};
int main()
{
    PaymentProcessor* payment1 = new CreditCard();
    payment1->processPayment();
    PaymentProcessor* payment2 = new CreditCard();
    payment2->processPayment();
    PaymentProcessor* payment3 = new CreditCard();
    payment3->processPayment();
    return 0;
}