#include<iostream>
#include<vector>
using namespace std;
class bank{
    public:
       //baseclass info
        void getInfo(){
            cout<<"BANK DETAILS:"<<endl<<endl;
            getName();
            getEstablisedDate();
            getBankType();
        }
        void getName();
        void getEstablisedDate();
        void getBankType();
        string name,establishedDate,bankType;
};
class loan{
    public:
       void getAvailableLoans();
       void getInterestRate();
       void getDocuments();
};
class BankwithLoan:public bank,loan{
    public:
        vector<string>availLoans;
        vector<string>documents;
        float rate;
        friend class compare_rate;
        
        void getName(){
            cout<<"Bank Name\t  :"<<name<<endl;
        }
        void getEstablisedDate(){
            cout<<"Bank Establised in:"<<establishedDate<<endl;
        }
        void getBankType(){
            cout<<"Bank Type\t  :"<<bankType<<endl;
        }
        void getAvailableLoans(){
            cout<<"Available Loans:";
            for(int i=0;i<availLoans.size();i++)
              cout<<availLoans[i]<<endl;
        }
        void getInterestRate(){
            cout<<"Rate:"<<rate<<endl;
        }
        void getDocuments(){
            cout<<"Required Documents:"<<endl;
            for(int i=0;i<documents.size();i++)
              cout<<documents[i]<<"\n";
            cout<<endl;
        }
        //printing the bank details
        void getInfo(){
            cout<<"\nBANK DETAILS:"<<endl<<endl;
            getName();
            getEstablisedDate();
            getBankType();
            getAvailableLoans();
            getInterestRate();
            getDocuments();
        }
        //setting the details of the bank
        void setInfo(){
            int n; string str;
            cout<<"\nEnter the Bank Name        :";
            cin>>name;
            cin.ignore (1, '\n');
            cout<<"\nEnter the Established Date :";
            getline(cin, establishedDate);
            cout<<"\nEnter the Bank Type        :";
            cin>>bankType;
           cout <<"\nEnter no of Available loan :"; cin >> n; cin.ignore(1, '\n');
           for (int i=0; i<n; i++)
            {
                getline(cin, str);
                availLoans.push_back(str);
            }
           cout<<"\nEnter the Loan rate        :";
            cin>>bankType;
            rate=10.6;
            cout <<"\nEnter no of documents     :"; cin >> n; cin.ignore(1, '\n');
           for (int i=0; i<n; i++)
            {
                getline(cin, str);
                documents.push_back(str);
            }
        }
        
        bool operator<(BankwithLoan &b2){
        return this->rate<b2.rate;
    }
};
class broker{
    public:
    //comapring n objects which may be two or three 
    void compare(BankwithLoan b[],int n){
    float minrate=999999,maxrate=0;
    string min,max;
    for(int i=0;i<n;i++)
       for(int j=i+1;j<=n-i-1;j++){
            if(b[i]<b[j]){
                if( b[i].rate<minrate){
                  min=b[i].name;
                  minrate=b[i].rate;
                }
                if(b[j].rate>maxrate){
                  max=b[j].name;
                  maxrate=b[j].rate;
                }
            }
            else{
                if(b[j].rate<minrate){
                  min=b[j].name;
                  minrate=b[i].rate;
                }
                if(b[i].rate>maxrate){
                  max=b[i].name;
                  maxrate=b[j].rate;
                }
            }
        }
    cout<<"Among the given Banks\n";
    cout<<"the bank with high rate:"<<max;
    cout<<"\nthe bank with low rate:"<<min;
    }
    //To print all bank details
    void print(BankwithLoan b){
        b.getInfo();
    }
    // to print a particular class
    void print(BankwithLoan b,string name){
        if(b.name==name)b.getInfo();
    }
};

int main(){
    BankwithLoan b[10];
    int n;
    cout<<"Enter no of banks:";
    cin>>n;
    for(int i=0;i<n;i++){
        b[i].setInfo();
    }
    broker r;
    for(int i=0;i<n;i++){
       r.print(b[i]); 
    }
    string name;
    cout<<"Enter which bank to display:";
    cin>>name;
    for(int i=0;i<n;i++){
       r.print(b[i],name); 
    }
    cout<<"Enter the  number of objects to compare:";
    cin>>n;
    r.compare(b,n);
    
    return 0;
}