#include <iostream>
#include <string>

using namespace std;

void SendSms(const string& number, const string& message);
void SendEmail(const string& email, const string& message);


//void SendSms(const string& number, const string& message) {
//  cout << "Send '" << message << "' to number " << number << endl;
//}

//void SendEmail(const string& email, const string& message) {
//  cout << "Send '" << message << "' to e-mail "  << email << endl;
//}


class INotifier
{
public:
    virtual void Notify(const string& message) const = 0;
};

class SmsNotifier : public INotifier
{
    const string number;
public:
    SmsNotifier(const string& where): number(where){}
    virtual void Notify(const string& message) const override
    {
        SendSms(number, message);
    }
};

class EmailNotifier : public INotifier
{
    const string address;
public:
    EmailNotifier(const string& where): address(where){}
    virtual void Notify(const string& message) const override
    {
        SendEmail(address, message);
    }
};



//void Notify(INotifier& notifier, const string& message) {
//  notifier.Notify(message);
//}


//int main() {
//  SmsNotifier sms{"+7-495-777-77-77"};
//  EmailNotifier email{"na-derevnyu@dedushke.ru"};

//  Notify(sms, "I have White belt in C++");
//  Notify(email, "And want a Yellow one");
//  return 0;
//}
