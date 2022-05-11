#include<iostream>
#include<string>
#include<exception>
#include<vector>
#include<algorithm>
using namespace std;
class AgeException:public exception{
    public:
    virtual const char * what ()const throw(){
        return "Age Not Within Range Exception";
    }
};
class NameException:public exception{
    public:
    virtual const char * what ()const throw(){
        return "Name Not Valid Exception";
    }
};
class CourseException:public exception{
    public:
    virtual const char * what ()const throw(){
        return "Invalid Couse Exception";
    }
};
vector<string>courses={"CSE","IT","ECE","EEE","MECH","BIO","CHEM"};
class Student{
    public:
    static int count;
    int age,rollno;
    string name,course;
    bool valid;
    AgeException age_invalid;
    NameException name_invalid;
    CourseException course_invalid;
    Student(int rollno,string name,int age,string course){
        this->rollno=rollno;
        valid=true;
        bool check;
        check=agecheck(age);
        if(check)this->age=age;
        check=namecheck(name);
        if(check)this->name=name;
        check=coursecheck(course);
        if(check)this->course=course;
        count++;
    }
    bool agecheck(int age){
        try{
            if(age>=15 && age<=21){
                valid=false;
                throw age_invalid;
            }
            return true;
        }
        catch(const exception &e){
            cerr<<"\nError Occured! "<<e.what();
            return false;
        }
    }
    bool namecheck(string name){
        try{
        for(int i=0;i<name.size();i++){
            if(!isalpha(name[i])){
                valid=false;
                throw name_invalid;
            }
        }
        return true;
        }
        catch(const exception &e){
            cerr<<"\nError Occured! "<<e.what();
            return false;
        }
        
    }
    bool coursecheck(string course){
        try{
        bool check=false;
        transform(course.begin(),course.end(),course.begin(),::toupper);
        for(int i=0;i<courses.size();i++){
            if(courses[i]==course){
                check=true;break;
            }
        }
        if(!check){
        throw course_invalid;
        valid=false;
        }
        return true;
        }
        catch(const exception &e){
            cerr<<"\nError Occured! "<<e.what();
            return false;
        }
    }
    void print(){
        if(valid){
        cout<<"\nStudent Details:";
        cout<<"\nRollno :"<<rollno;
        cout<<"\nName   :"<<name;
        cout<<"\nAge    :"<<age;
        cout<<"\nCourse :"<<course;
        }
        else{
            cout<<"\nInput is invalid";
        }
    }
};
int Student::count=0;
int main(){
    int rollno,age,x;
    string name,course;
    do{
        if(Student::count>=1){
            cout<<"\n Only one object can be created";
            break;
        }
        cout<<"\nEnter Rollno:";
        cin>>rollno;
        cout<<"\nEnter Name:";
        cin>>name;
        cout<<"\nEnter Age:";
        cin>>age;
        cout<<"\nEnter Course:";
        cin>>course;
        Student s(rollno,name,age,course);
        s.print();
        cout<<"\n\nDo you want to continue(0/1)";
        cin>>x;
        if(x==0)break;
    }while(1);
}
