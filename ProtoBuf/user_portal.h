#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include "project.pb.h"
using namespace std;
bool valid_email(string email)
{
    int pos1, pos2;
    bool check = true;
    pos1 = email.find('@');
    pos2 = email.find_last_of('.');
    for (int i = 0; i < email.size(); i++)
    {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '@' && email[i] != '_')
        {
            check = false;
            return check;
        }
    }
    if (pos1 == -1 || pos2 == -1 || pos1 > pos2)
        check = false;

    return check;
}
string encryption(string pw)
{
    for (int i = 0; i < pw.size(); i++)
    {
        pw[i] = (pw[i] + 12) % 128;
    }
    return pw;
}

class User_Portal
{
private:
    UserBook user_book;

public:
    void signup(string email)
    {
        // creating a new user
        User *u = user_book.add_user();
        string name, passwd, place;
        cout << "\nUser not Found!!\n\nTaking into Sign Up\n";
        cout << "\nEnter the password : ";
        cin >> passwd;
        passwd = encryption(passwd);
        cout << "\nEnter the name : ";
        cin >> name;
        cout << "\nEnter the Loaction : ";
        cin >> place;
        // setting the values of new user
        u->set_id(user_book.user_size());
        u->set_email(email);
        u->set_password(passwd);
        u->set_name(name);
        u->set_location(place);
        // writing the user to output file
        fstream output("User_Data", ios::out | ios::trunc | ios::binary);
        if (!user_book.SerializeToOstream(&output))
        {
            cerr << "\nFailed to write address book." << endl;
            exit(0);
        }
        cout << "\nSign Up Success!\n";
    }
    int sign_in()
    {
        string email, passwd;
        // opening user details file
        fstream input("User_Data", ios::in | ios::binary);
        // creating a user details objects using stream
        if (!user_book.ParseFromIstream(&input))
        {
            cerr << "\nFailed to parse address book." << endl;
            return 0;
        }
        cout << "\nEnter the emailId : ";
        cin >> email;
        if (!valid_email(email))
        {
            cout << "\nThe email ID is invalid\n";
            return 0;
        }
        // checking if the user already exits
        int i = check_user(email);
        if (i != -1)
        {
            cout << "\nEnter the password : ";
            cin >> passwd;
            passwd = encryption(passwd);
            if (passwd == user_book.user(i).password())
                return user_book.user(i).id();
            return 0;
        }
        // else taking to sign up
        signup(email);
        return user_book.user_size();
    }
    // function to check if user is present or not
    int check_user(string email)
    {
        for (int i = 0; i < user_book.user_size(); i++)
        {
            const User &u = user_book.user(i);
            if (u.email() == email)
                return i;
        }
        return -1;
    }
};