#include<bits/stdc++.h>
using namespace std;
struct Customer{
    string name;
    int acc_no,pin;
    long balance;
     Customer(int a,int b,string c,long d){
        acc_no=a;
        pin=b;
        name=c;
        balance=d;
    }
};
vector<Customer>cust;
class Customer_Process{
    public:
    void print_customer(){
        ifstream fin;
        string line;
        fin.open("customers.txt");
        cout<<"\n\nAccNo    Account Holder    Pin Number    Account Balance\n\n";
        for(int i=1;i<=5;i++){
            getline(fin,line);
            cout<<line<<endl;
        }
        fin.close();
    }
    void read_customer(){
       cust.clear();
        int a,b;
        string c;long d;
        string ch;
        ifstream fin;
        fin.open("customers.txt");
        for(int i=1;i<=5;i++){
            
            fin >> a;//  a = stoi(ch);
            fin >> c;
            fin >> b;//  b = stoi(ch);
            fin >> d; // d = stol(ch);
            struct Customer cu(a,b,c,d);
            cust.push_back(cu);
        }
    }
    void write_customer(){
        ofstream fout;
        fout.open("customers.txt");
        for(int i=0;i<5;i++){
            fout<<cust[i].acc_no<<"\t\t";
            fout<<cust[i].name<<"\t\t";
            fout<<cust[i].pin<<"\t";
            fout<<cust[i].balance<<"\n";
        }
    }
};
class ATM:public Customer_Process
{
public:
    int count_100, count_500, count_2000;
    long total;

    void reset()
    {
        count_100 = count_500 = count_2000 = total = 0;
    }

    void load_cash()
    {
        read_cash();
        int a, b, c;
        cout<<"Available cash :"<<endl;
        print_atm();
        cout << "\nAdding the cash: " << endl;
        cout << "\n Enter the 100 denominations:  ";
        cin >> a;
        count_100 += a;
        cout << "\n Enter the 500 denominations:  ";
        cin >> a;
        count_500 += a;
        cout << "\n Enter the 2000 denominations:  ";
        cin >> a;
        count_2000 += a;
        total = (count_100 * 100) + (count_500 * 500) + (count_2000 * 2000);
        write_cash();
        print_atm();
    }

    void write_cash()
    {
        ofstream file;
        file.open("atm.txt");
        file << "100 \t\t\t\t" << count_100 << "\t\t\t" << count_100 * 100 << endl;
        file << "500 \t\t\t\t" << count_500 << "\t\t\t" << count_500 * 500 << endl;
        file << "2000 \t\t\t\t" << count_2000 << "\t\t\t" << count_2000 * 2000 << endl;
        file.close();
    }

    void print_atm()
    {
        cout << "\nATM BALANCE: " << endl;
        cout << "DENOMINATION \t NUMBER \t VALUES" << endl;
        cout << "100 \t\t" << count_100 << "\t\t" << count_100 * 100 << endl;
        cout << "500 \t\t" << count_500 << "\t\t" << count_500 * 500 << endl;
        cout << "2000 \t\t" << count_2000 << "\t\t" << count_2000 * 2000 << endl;
        cout << "Total: \t\t" << total<<endl;
    }

    bool is_empty(ifstream &p)
    {
        return p.peek() == ifstream::traits_type::eof();
    }

    void read_cash()
    {
        ifstream file;
        file.open("atm.txt");

        if (is_empty(file))
        {
            reset();
        }

        else
        {
            string ch;
            file >> ch>>ch;
            count_100 = stoi(ch);
            file >> ch >> ch>>ch;
            count_500 = stoi(ch);
            file >> ch;
             file >> ch >> ch;
            count_2000 = stoi(ch);
            file >> ch;
        }
        file.close();
        total = (count_100 * 100) + (count_500 * 500) + (count_2000 * 2000);
    }
};
class atm_process:public ATM{
    private:
    int user=0,receiver=0,transaction_number=1001;
    public:
    bool validate(){
        bool check;
        int a,b;
        cout<<"\nEnter the Account No : ";
        cin>>a;
        cout<<"\nEnter the Pin : ";
        cin>>b;
        read_customer();
        for(int i=0;i<5;i++){
            if(a==cust[i].acc_no && b==cust[i].pin){
                user=i;
                return true;
            }
        }
        return false;
    }
    void withdraw(){
        int a=0,b=0,c=0,p,amount;
        int temp_amount,temp;
        bool check;
        read_cash();
        cout<<"\nEnter the Pin : ";
        cin>>p;
        if(p!=cust[user].pin){
            cout<<"\nThe Pin is Invalid\n";
            return ;
        }
        cout<<"\nEnter the Amount to Withdrawal : ";
        cin>>amount;
        //to store the initial amount
        temp_amount=amount;
        if(amount>10000 || amount<100)
            cout<<"\nMax Withdrawal limit-10,000\nMin Withdrawal limit-100\n";
        else if(amount>total)
            cout<<"\nATM does not have sufficient money to vend\n";
        else if(amount>cust[user].balance)
            cout<<"\nAccount balance is lower than entered withdrawal amount\n";
        else if(amount<=5000){
            if(amount>=3000){
                if(count_2000==0){
                    cout<<"\n2000 is not sufficient\nMinimun condition not Satisified\n";
                    return;
                }
                amount-=2000;
                a++;
            }
            if(amount>=1000 && count_500==0){
                cout<<"\n500 is not sufficient\nMinimun Condtion not satisifed\n";
                return;
            }
            if(amount>=1000){
                temp=(amount>=1500)?amount-1000:amount;
                if(temp>=(count_500*500)){
                    amount-=count_500*500;
                    b=count_500;
                }
                else{
                    b=temp/500;
                    amount-=b*500;
                }
            }
            if(amount>1000 && count_100<10){
                cout<<"\n100 is not sufficient\nMinimun Condtion not satisifed\n";
                return;
            }
            if(amount>0){
                c=amount/100;
                if(c>15){
                    cout<<"\nmaximum Condtion satisifed\nWithdrawal Cancelled\n";
                    return;
                }
                if(c<=count_100)
                    amount-=c*100;
            }
        }
        else if(amount>5000){
            if(count_2000<2){
                cout<<"\n2000 is not sufficient\nMinimun condition not Satisified\n";
                return;
            }
            if(count_500<2){
                cout<<"\n500 is not sufficient\nMinimun Condtion not satisifed\n";
                return;
            }
            //calculating the remaining 2000 amount available 
            temp=count_2000*2000;
            if(amount>=temp){
                amount-=count_2000*2000;
                a=count_2000;
            }
            else if(amount>=2000){
                a=amount/2000;
                amount-=a*2000;
            }
            //calculating the remaining 2000 amount available
            temp=count_500*500;
            if(amount>=temp){
                amount-=count_500*500;
                b=count_500;
            }
            else if(amount>=500){
                b=amount/500;
                amount-=b*500;
            }
            if(amount>1000){
                cout<<"\nMaximum Condtion of 100 satisifed\nWithdrawal Cancelled\n";
                return;
            }
            if(amount>0){
                c=amount/100;
                if(c<=count_100)
                    amount-=c*100;
            }
        }
        if(amount>0){
            cout<<"\nDenomination not available\n";
        }
        else{
            cout<<"\nWithdrawal Succesful!\n\nDenominations are:\n";
            cout<<"\n2000 - "<<a;
            cout<<"\n500 - "<<b;
            cout<<"\n100 - "<<c<<endl;
            count_2000-=a;
            count_500-=b;
            count_100-=c;
            write_cash();
            cust[user].balance-=temp_amount;
            write_customer();
            fstream transaction;
            string val=to_string(cust[user].acc_no)+"_transaction.txt";
            transaction.open(val,ios::app);
            future<void>thread_w=async(launch::async,[&](){
                transaction<<transaction_number<<"\t\tCash Withdrawal\t"<<"\tDebit\t\t"<<temp_amount<<"\t"<<cust[user].balance<<endl;
                this_thread::sleep_for(5000ms);
            });
        }

    }
    void transfer(){
        int receiver,r,amount;
        string temp;
        bool check=false;
        cout<<"\nEnter Receiver : ";
        cin>>r;
        for(int i=0;i<5;i++){
            if(r==cust[i].acc_no && i!=user){
                receiver=i;
                check=true;
                break;
            }
        }
        if(!check){
            cout<<"\nThe Receiver not found\n";
            return;
        }
        cout<<"\nEnter the amount:";
        cin>>amount;
        if(amount>10000 || amount<1000)
            cout<<"\nThe Maximum limit-10,000\nThe Minimum limit-1,000\n";
        else if(amount>cust[user].balance)
            cout<<"\nThe amount is greater than balance\n";
        else{
            cust[user].balance-=amount;
            cust[receiver].balance+=amount;
            write_customer();
            fstream fsender;
            string val = to_string(cust[user].acc_no) + "_transaction.txt";
            fsender.open(val,ios::app);
            future<void>thread_s=async(launch::async,[&](){
                fsender<<transaction_number<<"\t\tTransfer to "<<r<<"\t\tDebit\t\t"<<amount<<"\t"<<cust[user].balance<<endl;
                this_thread::sleep_for(5000ms);
            });
            val = to_string(cust[receiver].acc_no) + "_transaction.txt";
            fstream freceiver;
            freceiver.open(val,ios::app);
            future<void>thread_r=async(launch::async,[&](){
                freceiver<<transaction_number<<"\t\tTransfer from "<<cust[user].acc_no<<"\tCredit\t\t"<<amount<<"\t"<<cust[receiver].balance<<endl;
                this_thread::sleep_for(5000ms);
            });
            
            cout<<"\nThe Money Transfered\n";
            print_customer();
        }


    }
    void ministatement(){
        string val = to_string(cust[user].acc_no) + "_transaction.txt";
        string line;
        ifstream userfile(val);
        userfile.unsetf(std::ios_base::skipws);
        unsigned line_count = std::count(istream_iterator<char>(userfile),istream_iterator<char>(),'\n');
        int start=(line_count<10)?1:line_count-10+1;
        userfile.clear();
        userfile.seekg(0,ios::beg);
        for(int i=1;i<start;i++)
            getline(userfile,line);
        cout<<"\nTransaction_N0   Description\t\tCredit / Debit   Amount   Closing Balance\n";
        for(int i=start;i<=line_count;i++){
            getline(userfile,line);
            cout<<line<<endl;
        }
        cout<<endl;
    }
    void process(){
        int choice;
        do{
            cout<<"\n1. Check Balance\n2. Withdraw Money\n3. Transfer Money\n4. Check ATM Balance\n5. Mini Statement\n6. Exit";
            cout<<"\n\nEnter your choice : ";
            cin>>choice;
            switch(choice){
                case 1:cout<<"\nThe Balance is : "<<cust[user].balance<<endl;break;
                case 2:withdraw();transaction_number++;break;
                case 3:transfer();transaction_number++;break;
                case 4:read_cash();cout<<"\nThe ATM Balance is : "<<total;;break;
                case 5:ministatement();break;
                case 6:cout<<"\nExiting ATM Operation\n";break;
                default:cout<<"\nInvalid choice\n";
            }

        }while(choice!=6);
    }
};
int main(){
    ATM a;
    atm_process ap;
    int choice;
    bool check;
    do{
        cout<<"\n1. Load Cash to ATM\n2. Show Customer Details\n3. Show ATM Operations\n4. Exit\n\nEnter your choice : ";
        cin>>choice;
        switch(choice){
            case 1:a.load_cash();break;
            case 2:a.print_customer();break;
            case 3:{
                check=ap.validate();
                if(check){
                   ap.process();
                }
                else
                 cout<<"\nThe Acc no or pin is invalid or mismatch\n";
                break;
            }
            case 4:cout<<"\nExiting...";break;
            default:cout<<"\nInvalid Choice\n";
        }
    }while(choice!=4);
    return 0;
}
