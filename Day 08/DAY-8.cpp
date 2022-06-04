#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
bool is_digits(const string &str)
{
    return str.find_first_not_of("0123456789") == string::npos;
}
class Mobile
{
private:
    vector<string> number;
    vector<float> bill;

public:
    void add_connection()
    {
        string num;
        cout << "\nEnter the number:";
        cin >> num;
        while (!is_digits(num) || num.size() != 10)
        {
            cout << "\nInvalid Number.please Enter again:";
            cin >> num;
        }
        number.push_back(num);
        bill.push_back(0);
        print_details(number.size() - 1);
    }
    void print_details(int index)
    {
        cout << "\nThe Number :" << number[index];
        cout << "\nThe Bill :" << bill[index];
    }
    void pay_bill(string num, float amount)
    {
        bool check = false;
        for (int i = 0; i < number.size(); i++)
        {
            if (number[i] == num)
            {

                if (amount > bill[i])
                {
                    bill[i] = 0;
                    cout << "\nthe bill amount " << bill[i] << " paid";
                    cout << "\nexcess amount provided " << amount - bill[i] << endl;
                }
                else
                {
                    bill[i] -= amount;
                    cout << "\nthe bill amount " << amount << " paid";
                    cout << "\nThe remaining Bill " << bill[i] << endl;
                }
                check = true;
                print_details(i);
                break;
            }
        }
        if (!check)
            cout << "\nNumber not found!";
    }
    void update_bill(string num, float amount)
    {
        bool check = false;
        for (int i = 0; i < number.size(); i++)
        {
            if (number[i] == num)
            {

                bill[i] += amount;
                cout << "\nthe bill amount added.\nthe New bill amount " << bill[i] << endl;
                check = true;
                print_details(i);
                break;
            }
        }
        if (!check)
            cout << "\nNumber not found!";
    }
};
class Landline
{
private:
    vector<string> number, std;
    vector<float> bill;

public:
    void add_connection()
    {
        string temp;
        cout << "\nEnter the STD";
        cin >> temp;
        while (!is_digits(temp) || temp.size() != 3)
        {
            cout << "\nInvalid STD.please Enter again:";
            cin >> temp;
        }
        std.push_back(temp);
        cout << "\nEnter the number:";
        cin >> temp;
        while (!is_digits(temp) || temp.size() != 6)
        {
            cout << "\nInvalid Number.please Enter again:";
            cin >> temp;
        }
        number.push_back(temp);
        bill.push_back(0);
        print_details(number.size() - 1);
    }
    void print_details(int index)
    {
        cout << "\nThe STD :" << std[index];
        cout << "\nThe Number :" << number[index];
        cout << "\nThe Bill :" << bill[index];
    }
    void pay_bill(string n, float amount)
    {
        bool check = false;
        string std_check, num;
        std_check = n.substr(0, 2);
        num = n.substr(2, n.size() - 1);
        for (int i = 0; i < number.size(); i++)
        {
            if (number[i] == num && std[i] == std_check)
            {

                if (amount > bill[i])
                {
                    bill[i] = 0;
                    cout << "\nthe bill amount " << bill[i] << " paid";
                    cout << "\nexcess amount provided " << amount - bill[i] << endl;
                }
                else
                {
                    bill[i] -= amount;
                    cout << "\nthe bill amount " << amount << " paid";
                    cout << "\nThe remaining Bill " << bill[i] << endl;
                }
                print_details(i);
                check = true;
                break;
            }
        }
        if (!check)
            cout << "\nNumber or STD not found or not matched!";
    }
    void update_bill(string n, float amount)
    {
        bool check = false;
        string std_check, num;
        std_check = n.substr(0, 2);
        num = n.substr(2, n.size() - 1);
        for (int i = 0; i < number.size(); i++)
        {
            if (number[i] == num && std[i] == std_check)
            {

                bill[i] += amount;
                cout << "\nthe bill amount added.\nthe New bill amount " << bill[i] << endl;
                check = true;
                print_details(i);
                break;
            }
        }
        if (!check)
            cout << "\nNumber or STD not found or not matched!";
    }
};
template <class T>
class BillPayment
{
private:
    T t;

public:
    void add()
    {
        t.add_connection();
    }
    void pay(string number, float amount)
    {
        t.pay_bill(number, amount);
    }
    void update(string number, float amount)
    {
        t.update_bill(number, amount);
    }
};
int main()
{
    BillPayment<Mobile> bp;
    BillPayment<Landline> bp2;
    int choice;
    string number;
    float amount;
    do
    {
        cout << "\n\n1.add mobile connection\n2.add landline connection";
        cout << "\n3.pay mobile connection\n4.pay landline connection";
        cout << "\n5.update mobile connection\n6.update landline connection";
        cout << "\n7.exit\nEnter your choice:";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bp.add();
            break;
        case 2:
            bp2.add();
            break;
        case 3:
        {
            cout << "\nEnter the number to pay";
            cin >> number;
            cout << "\nEnter the amount";
            cin >> amount;
            bp.pay(number, amount);
            break;
        }
        case 4:
        {
            cout << "\nEnter the number to pay";
            cin >> number;
            cout << "\nEnter the amount";
            cin >> amount;
            bp2.pay(number, amount);
            break;
        }
        case 5:
        {
            cout << "\nEnter the number to update";
            cin >> number;
            cout << "\nEnter the amount";
            cin >> amount;
            bp.update(number, amount);
            break;
        }
        case 6:
        {
            cout << "\nEnter the number to update";
            cin >> number;
            cout << "\nEnter the amount";
            cin >> amount;
            bp2.update(number, amount);
            break;
        }
        case 7:
            cout << "\nExiting...";
            break;
        default:
            cout << "\nInvalid option";
        }
    } while (choice != 7);
    return 0;
}
