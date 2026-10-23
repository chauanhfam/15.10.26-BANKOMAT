#include <iostream>
#include <string>
using namespace std;
class Bankomat
{
private:
    int id;
    int money100;
    int money200;
    int money500;
    int money1000;

    int minSum;
    int maxSum;

public:
    Bankomat(int id, int minSum, int maxSum)
    {
        this->id = id;
        this->minSum = minSum;
        this->maxSum = maxSum;

        money100 = 0;
        money200 = 0;
        money500 = 0;
        money1000 = 0;
    }

    void Init(int id, int minSum, int maxSum)
    {
        this->id = id;
        this->minSum = minSum;
        this->maxSum = maxSum;
    }

    void Load(int n100, int n200, int n500, int n1000)
    {
        if (n100 >= 0 && n200 >= 0 && n500 >= 0 && n1000 >= 0)
        {
            money100 += n100;
            money200 += n200;
            money500 += n500;
            money1000 += n1000;
        }
        else
        {
            cout << "Incorrect number of banknotes!" << endl;
        }
    }

    // Общая сумма денег в банкомате
    int GetMoney()
    {
        return money100 * 100 + money200 * 200 + money500 * 500 + money1000 * 1000;
    }

    // Снятие денег
    bool Withdraw(int sum)
    {
        if (sum < minSum || sum > maxSum)
        {
            cout << "Incorrect withdrawal amount!" << endl;
            return false;
        }

        if (sum > GetMoney())
        {
            cout << "Not enough money in ATM!" << endl;
            return false;
        }

        int n100 = money100;
        int n200 = money200;
        int n500 = money500;
        int n1000 = money1000;

        int rest = sum;

        // крупные купюры
        int take1000 = rest / 1000;
        if (take1000 > n1000)
        {
            take1000 = n1000;
        }
        rest -= take1000 * 1000;

        int take500 = rest / 500;
        if (take500 > n500)
        {
            take500 = n500;
        }
        rest -= take500 * 500;

        int take200 = rest / 200;
        if (take200 > n200)
        {
            take200 = n200;
        }
        rest -= take200 * 200;

        int take100 = rest / 100;
        if (take100 > n100)
        {
            take100 = n100;
        }
        rest -= take100 * 100;

        if (rest != 0)
        {
            cout << "Cannot give this amount with available banknotes!"<< endl;
            return false;
        }

        money1000 -= take1000;
        money500 -= take500;
        money200 -= take200;
        money100 -= take100;

        cout << "Money withdrawn: " << sum << " UAH" << endl;
        return true;
    }

    string toString()
    {
        return "ATM ID: " + to_string(id) + ", remaining money: " + to_string(GetMoney()) + " UAH";
    }
};

int main()
{
    Bankomat atm(101, 100, 5000);

    atm.Load(10, 10, 10, 5);

    cout << atm.toString() << endl;

    atm.Withdraw(1800);

    cout << atm.toString() << endl;

    atm.Withdraw(50);

    return 0;
}
