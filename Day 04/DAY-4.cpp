#include<iostream>
#include <cmath>
using namespace std;
class Rectangle{
       int *left,*width,*height,*top,*area=NULL;
    public:
    //Default Constructor
       Rectangle(){;
           left=new int(0);
           width=new int(0);
           top=new int(0);
           height=new int(0);

       }   
       //Paramter constructor with two values
       Rectangle(int w,int h){
           left=new int(0);
           top=new int(0);
           width=new int(w);
           height=new int(h);
       }
       //Paramterized Constructor with all values
       Rectangle(int l,int t,int w,int h){
           left=new int(l);
           width=new int(w);
           height=new int(h);
           top=new int(t);
       }
       //Paramterized Constructor with float values
       Rectangle(float l,float t,float w,float h){
           left=new int(round(l));
           width=new int(round(w));
           height=new int(round(h));
           top=new int(round(t));
       }
       //Copy Constructor
       Rectangle(Rectangle &r){
           left=r.left;
           width=r.width;
           height=r.height;
           top=r.top;
           r.area=new int(*width * *height);
           area=r.area;
       }
       void print(){
           cout<<"\nLeft   : "<<*left;
           cout<<"\nTop    : "<<*top;
           cout<<"\nWidth  : "<<*width;
           cout<<"\nHeight : "<<*height;
           if(area)cout<<"\nArea   : "<<*area;
           cout<<endl;
       }
       //Destructor
       ~Rectangle(){
            cout<<"\nMemory Freed\n";
           delete(left);
           delete(top);
           delete(width);
           delete(height);
           delete(area);
       }
};
int main(){
    
    Rectangle r1(1,2,3,4);
    Rectangle r2(4,5);
    Rectangle r3;
    Rectangle r4(4.2f,5.6f,6.5f,7.3f);
    Rectangle r5(r1);
    cout<<"\nDefault Constructor";
    r3.print();
    cout<<"\nParameterized Constructor with two values";
    r2.print();
    cout<<"\nParamterized Constructor";
    r1.print();
    cout<<"\nParamterized Constructor with float values";
    r4.print();
    cout<<"\nCopy Constructor";
    r5.print();
    return 0;
}
