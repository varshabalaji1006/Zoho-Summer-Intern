#include <iostream>
//importing the namespace from another file
#include "DAY-5.h"
//using alias for namespace
namespace maths=mathFunctions;
using namespace maths;
//class to acces namespace 
class outer_class{
    public:
    //calling respective functions based on choice
    void func(int choice){
        //creating an object for result class present inside namespace m 
        m::result r;
        switch (choice)
        {
        case 1:
            r.add(); 
            break;
        case 2:
            r.sub(); 
            break;
        case 3:
            r.mul(); 
            break;
        case 4:
            r.div(); 
            break;    
        case 5:
            r.mod();
            break;
        }
    }
};
int main(){
    //creating an object for outer_class
   outer_class c;
    int choice;
    do{
      std::cout<<"\n\n1.Add\n2.Subtraction\n3.Multiplication\n4.Division\n5.Modulus\n6.Exit\nEnter your Choice : ";
      std::cin>>choice;
      //getting two numbers from the user
      if(choice<6){
          std::cout<<"Enter two numbers : ";
          std::cin>>a>>b;
          c.func(choice);
      }
      else if(choice==6){
          std::cout<<"\nExiting...";
      }
      else std::cout<<"\nInvalid Choice";
    }while(choice!=6);
    return 0;
}
