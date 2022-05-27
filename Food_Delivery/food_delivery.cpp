#include<iostream>
#include<vector>
using namespace std;
int no_of_exec=0;
//to store executive members details
struct delivery_exec{
    int allowance,deliverycharge,pick_up_t,order;
};
//to store the history of orders
struct del_history{
    int trip,orders,del_charge,executive;
    int pick_up_time;
    char restaurant,dest;
};
class food_delivery{
    private:
    vector<delivery_exec>de;
    vector<del_history>dh;
    int id;
    public:
    //initalize all executive members value to 0
    food_delivery(){
        for(int i=0;i<no_of_exec;i++){
            struct delivery_exec d;
            d.deliverycharge=d.allowance=d.order=d.pick_up_t=0;
            de.push_back(d);
        }
    }
    //getting a new order
    void booking(){
        char r,d;
        string time;
        cout<<"\nEnter the Customer ID:";
        cin>>id;
        cout<<"\nEnter the Restaurant:";
        cin>>r;
        if(r<65 || r>70){
            cout<<"\nInvalid Restaurant\n";
            return;
        }
        cout<<"\nEnter the Destination Point:";
        cin>>d;
         if(d<65 || d>70){
            cout<<"\nInvalid Restaurant\n";
            return;
        }
        cout<<"\nEnter the time:";
        cin>>time; 
        cout<<"\n\nCustomer ID\t: "<<id;
        cout<<"\nRestaurant\t: "<<r;
        cout<<"\nDestination point: "<<d;
        cout<<"\nTime\t\t:"<<time;
        allotment(r,d,time);
    }
    //alloting the new order to the executive
    void allotment(char r,char d,string time){
        print_booking();
        string temp;
        bool allot=false;
        int pick_up,hour,min,t;
        struct del_history new_order;
        int ex=0,min_value=99999999;
        //converting the given time into mins
        t=time.find(".");
        hour=stoi(time.substr(0,t));
        min=stoi(time.substr(t+1,t+2));
        pick_up=hour*60+min;
        temp=time.substr(time.size()-2,time.size()-1);
        if(hour==12 && temp=="AM")
        pick_up=min;
        else if(temp=="PM" && hour!=12)
        pick_up+=720;
        //checking any prev order with difference 15 mins
        for(int i=0;i<dh.size();i++){
            if((pick_up-dh[i].pick_up_time)<=15 && dh[i].orders<5 && dh[i].restaurant==r && dh[i].dest==d){
                //updating the exec and order details
                ex=dh[i].executive;
                de[ex].deliverycharge+=5;
                dh[i].orders+=1;
                dh[i].del_charge+=5;
                allot=true;
            }
        }
        //if the order is not combined
        if(!allot){
            //checking which delivery executive has minimum delivery charge
            for(int i=0;i<no_of_exec;i++){
                if(de[i].deliverycharge<min_value){
                   if(!(pick_up>de[i].pick_up_t && pick_up<=(de[i].pick_up_t+30))){
                   ex=i;
                   min_value=de[i].deliverycharge;
                   }
                }
            }
            //updating details of exec
            de[ex].deliverycharge+=50;
            de[ex].allowance+=10;
            de[ex].order+=1;
            de[ex].pick_up_t=pick_up+15;
            //inserting the new order
            new_order.executive=ex;
            new_order.restaurant=r;
            new_order.dest=d;
            new_order.del_charge=50;
            new_order.orders=1;
            new_order.pick_up_time=pick_up;
            dh.push_back(new_order);
        }
        cout<<"\nAlloted Executive : DE"<<ex+1<<endl;
    }
    //to print the current order deatils
    void print_booking(){
        cout<<"\n\nBooking ID : "<<id;
        cout<<"\nAvailable Executives:";
        cout<<"\nExecutive    Delivery Charge Earned\n";
        for(int i=0;i<no_of_exec;i++){
            cout<<"DE"<<i+1<<"\t\t\t"<<de[i].deliverycharge;
            cout<<endl;
        }
    }
    //to print the details of executives
    void print_delivery(){
        cout<<"\nTotal Earned\n";
        cout<<"\nExecutive   Allowance  Delivery_Charges  Total\n";
        for(int i=0;i<de.size();i++)
            cout<<"DE"<<i+1<<"\t\t"<<de[i].allowance<<"\t\t"<<de[i].deliverycharge<<"\t "<<de[i].allowance+de[i].deliverycharge<<endl;
    }
    //to print the history details 
    void print_history(){
        string pick_up,del_time;
        print_delivery();
        cout<<"\nTrip  Executive  Restaurant  Destination  Orders  Pickup_Time  Delivery_Time   Delivery_Charge\n";
        for(int i=0;i<dh.size();i++){
            pick_up=conversion(dh[i].pick_up_time+15);
            del_time=conversion(dh[i].pick_up_time+45);
            cout<<i+1<<"\tDE"<<dh[i].executive+1<<"\t   "<<dh[i].restaurant<<"\t\t"<<dh[i].dest<<"\t   "<<dh[i].orders<<"\t  ";
            cout<<pick_up<<"\t"<<del_time<<"\t\t"<<dh[i].del_charge;
            cout<<endl;
        }
    }
    //a conversion method to convert mins to time format
    string conversion(int a){
        string time;
        int min,hour;
        if(a>=1440)
        a-=1440;
        if(a>=720){
        time="PM";
        a-=720;
        }
        else
        time="AM";
        min=a%60;
        a=a-min;
        if(min<10)
        time=".0"+to_string(min)+time;
        else
        time="."+to_string(min)+time;
        a=a/60;
        if(a==0)
        time=to_string(12)+time;
        else
        time=to_string(a)+time;
        return time;
    }
};
int main(){
    int choice;
    cout<<"\nEnter Number of Executives : ";
    cin>>no_of_exec;
    cout<<"\nThe Available restaurant are A,B,C,D,E\n";
    cout<<endl;
    food_delivery f;
    do{
        cout<<"\n1. Booking\n2. Display History\n3. Exit\n\nEnter your choice:";
        cin>>choice;
        switch(choice){
            case 1:f.booking();break;
            case 2:f.print_history();break;
            case 3:cout<<"\nExiting\n";break;
            default:cout<<"\nInvalid choice\n";
        }
    }while(choice!=3);
}
