#include "project_portal.h"
#include "user_portal.h"
int main(){
    User_Portal up;
    Project_Portal pp;
    int id,choice;
    //calling signin function
    id=up.sign_in();
    if(id==0){
       cout<<"\nSign in Failed!\n";
       return 0;
    }
    //only if sign in success it takes to project portal
    else if(id!=-1)
    cout<<"\nSign in Success!\n";
    do{
    //doing operation until user wants to exit
    cout<<"\nThe File Options\n\n1. Create New file\n2. List Projects\n3. Exit\n\nEnter your choice : ";
    cin>>choice;
    string user_id=to_string(id);
    //setting the user_id for the project 
    pp.user_id=user_id;
    switch (choice)
    {
    case 1:
        pp.create_file();
        break;
    case 2:
        pp.list_operations();
        break;
    case 3:
        cout<<"\nExiting\n";
        break;
    default:
        cout<<"\nInvalid choice\n";
        break;
    }
    }while(choice!=3);
    
    
}
