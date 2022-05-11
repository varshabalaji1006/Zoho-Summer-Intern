#include<iostream>
#include<exception>
#include<stdexcept>
using namespace std;
// a function to demonstrate rethrow error
void rethrow(){
    cout<<"\nDivinding a number by zero";
    try{
        int dividend=40,divisor=0;
        if(divisor==0)
        throw runtime_error("Invalid division");
        cout<<"\nDivision is "<< dividend/divisor;
    } 
    catch(runtime_error& e) {
        cerr << "\nException occurred in function\n" << endl << e.what();
        cout<<"\nRethrowing the error to main\n";
        //rethrow the already catched
        throw;
    }
}
int main(){
    int dividend,divisor,var=0;
    try {
      // Inside outer try block
      // Nested inner Block
      try {
          throw runtime_error("Error!");
      }      
      // Nested catch block
      catch (runtime_error& e) {
         // Code executed when exception Catch : for nested exception
         cerr << "\nInner Exception Catch :" << e.what()<<endl;
      }
      throw var;
      
    }
    //outer exception class
    catch(int a){
        cout<<"\nOuter Exception Catch"<<endl;
    } 
    try{
        //calling rethrow function
        rethrow();
    }
    catch(const exception& ex)
    {
         // speciffic handling for all exceptions extending std::exception, except
         cerr << "\nError occurred in main: " << ex.what() << endl;
    }
    // speciffic handling for runtime_error
    catch(const std::runtime_error& re)
    {
       cerr << "Runtime error: " << re.what() << std::endl;
    }
    //to handle no such notable exceptions
    catch (...) {
      // Code executed when exception Catch : for default
      cout << "\nUnknown failure occurred";
    }
    return 0;
}