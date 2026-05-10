#include <iostream>
using namespace std;

class Card
{
protected:
    int balance = 0;

public:
    Card(int initialBalance)
    {
        balance = initialBalance;
    }
    virtual void purchase(int amount) = 0; // pure virtual function
    virtual void ToString() = 0;           // pure virtual function
};
class Creditcard : public Card
{
protected:
    int limit;

public:
    Creditcard(int initialBalance, int creditLimit) : Card(initialBalance)
    {
        limit = creditLimit;
    }
    void purchase(int amount) override
    {
        if (balance + amount > limit)
        {
            cout << "Purchase declined: credit limit exceeded. please pay your bill." << endl;
        }
        else
        {
            balance += amount;
            cout << "Purchase successful: " << amount << " added to balance." << endl;
        }
    }
    void pay(int amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Payment successful: " << amount << " deducted from balance." << endl;
        }
        else
        {
            cout << "Insufficient balance. Please pay your bill first." << endl;
        }
    }
    void ToString() override
    {
        cout << "Credit Card limit: " << limit << ", Balance: " << balance << endl;
    }
};

int main()
{
    Card **cards = new Card *[3];
    cards[0] = new Creditcard(1000, 1500);
    cards[1] = new Creditcard(5000, 6000);
    cards[2] = new Creditcard(10000, 11000);

    cards[0]->ToString();
    cards[1]->purchase(500);
    cards[1]->ToString();
    cards[2]->purchase(1000);
   ((Creditcard*)cards[2])->pay(300);
    cards[2]->ToString();

    return 0;
}