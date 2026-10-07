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
            cout << "Processing Credit Card Payment" << endl;
        }
        else if(paymentType == "UPI")
        {
            cout << "Processing Credit NetBanking" << endl;
        }
        else if(paymentType == "NetBanking")
        {
            cout << "Processing Credit Wallet" << endl;
        }
    }
};
int main()
{
    PaymentProcessor payment;
    payment.processPayment("CreditCard");

    payment.processPayment("UPI");

    payment.processPayment("NETBanking");
    return 0;
}