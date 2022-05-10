//Parent namespace
namespace mathFunctions{
    //using an inline namespace
    inline namespace calc{
        int a,b,res;
    }
    //nested namespace having a class inside it
    namespace m{
    class result{
        public:
        //you can access a,b,res since it is inline 
        //Add of two numbers
        void add() {
            res=a+b;
            std::cout<<"\nSum is : "<<res;
        }
        //difference of two numbers
        void sub() {
            res=a-b;
            std::cout<<"\nDifference is : "<<res; 
        }
        //multiplication of two numbers
        void mul() {
            res=a*b;
            std::cout<<"\nMultiply is : "<<res;
        }
        //Division of two numbers
        void div() {
            res=a/b;
            std::cout<<"\nDivision is : "<<res;
        }
        //modulus of two numbers
        void mod() {
            res=a%b;
            std::cout<<"\nModulus is : "<<res;
        }

       };
    }
}