#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
using namespace std;
// a class to handle all exception
class MyException : public exception
{
public:
    string ex;
    // constructor to get my own exception
    MyException(string s)
    {
        this->ex = s;
    }
    // creating own exception
    virtual const char *what() const throw()
    {
        string except = "My Exception (" + ex + ")";
        cout << endl
             << endl
             << except;
        return "";
    }
    // function to handle division error
    void division()
    {
        int dividend, divisor;
        cout << "\nEnter the Dividend and Divisor :";
        cin >> dividend >> divisor;
        try
        {
            if (divisor == 0)
                throw runtime_error("Invalid division");
            cout << "\nDivision is " << dividend / divisor;
        }
        catch (runtime_error &e)
        {
            cerr << "\nException occurred" << endl
                 << e.what();
        }
    }
    // function to handle mismatch error
    void type_mismatch()
    {
        int n;
        cout << "\n\nEnter a number:";
        try
        {
            cin >> n;
            if (cin.fail())
            {
                throw "Format mismatch";
            }
            cout << "\nThe number is:" << n;
        }
        catch (const char *e)
        {
            cerr << "\nException occurred" << endl
                 << e;
        }
    }
    // function to handle an invalid index in string
    void string_except()
    {
        string s;
        cout << "\n\nEnter the String:";
        cin >> s;
        int index;
        cout << "Enter the index:";
        cin >> index;
        try
        {
            char c = s.at(index);
            cout << "\nThe element at " << index << " is " << c;
        }
        catch (out_of_range &e)
        {
            cerr << "\nException occured " << endl
                 << "Index is invalid";
        }
    }
    // function to handle an invalid index in array
    void array_exception()
    {
        int n, index, temp;
        cout << "\n\nEnter No of Elements:";
        cin >> n;
        vector<int> a;
        cout << "Enter the array:";
        for (int i = 0; i < n; i++)
        {
            cin >> temp;
            a.push_back(temp);
        }
        cout << "Enter the index:";
        cin >> index;
        try
        {
            int c = a.at(index);
            cout << "\nThe element at " << index << " is " << c;
        }
        catch (out_of_range &e)
        {
            cerr << "\nException occured " << endl
                 << "Index is invalid";
        }
    }
    // function to hadle memroy alloaction
    void heap_memory()
    {
        long memory_size = 0x7fffffff;
        try
        {
            char *ptr = new char[memory_size];
            cout << "\n\nMemory is allocated Successfully!";
            delete[] ptr;
        }
        catch (const bad_alloc &e)
        {
            cerr << "\nMemory is compromised!";
        }
    }
};
int main()
{
    // creating an object
    MyException e("My error");
    try
    {
        e.division();
        e.heap_memory();
        e.string_except();
        e.array_exception();
        e.type_mismatch();
        e.what();
    }
    // to catch Any other exception
    catch (...)
    {
        cerr << "\nException encountered";
    }
    cout << "\n\nException Handling Accomplished!";
    return 0;
}
