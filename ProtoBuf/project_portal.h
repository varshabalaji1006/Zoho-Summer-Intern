#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <filesystem>
#include "project.pb.h"
namespace fs = std::filesystem;
using namespace std;
using namespace google::protobuf;
class Project_Portal
{
private:
    string path;
    int n;
    Project project;

public:
    string user_id;
    // if the current user directory not present,it creates the directory
    void check_directory()
    {
        struct stat buffer;
        if (stat(user_id.c_str(), &buffer) != 0)
        {
            mkdir(user_id.c_str(), 0777);
            cout << "\nDirectory Not Found!\nDirectory Created!\n";
        }
    }
    // function to create new file
    void create_file()
    {
        path = "./" + user_id + "/";
        string filename;
        check_directory();
        cout << "\nEnter the New FileName : ";
        cin >> filename;
        if (fs::exists(path + filename))
        {
            cout << "\nFile Already Exist!\n";
            return;
        }
        // insertion the new project details in version
        project.set_latest_version(1);
        Version *version=project.add_version();
        // setting the values for new project
        time_t t = time(0);
        string dt = string(ctime(&t));
        version->set_id(1);
        version->set_user_id(user_id);
        version->set_name(filename);
        version->set_operations(0);
        version->set_time(dt);
        // writing the version details of new project
        ofstream output;
        output.open(path + filename + ".txt", ios::out | ios::binary);
        if (!project.SerializeToOstream(&output))
        {
            cerr << "\nFailed to write address book." << endl;
            exit(0);
        }
        
        cout << "\nFile Created Successfully!\n";
    }
    // a function to diplay the available projects
    void list_projects()
    {
        n = 0;
        cout << "\nThe Available Projects \n\n";
        for (const auto &entry : fs::directory_iterator(path))
        {
            // to display only the file name,logic is used
            string temp = entry.path();
            int size=temp.find_last_of('.')-temp.find_last_of('/')-1;
            temp = temp.substr(temp.find_last_of('/') + 1,size);
            cout << temp << endl;
            n++;
            
        }
    }
    // function to append at last line of file
    void add(Version *version)
    {
        string line;
        // creating a new msg obj at end of project
        Msg *m = version->add_msg();
        cout << "\nEnter the message to append :";
        getline(cin >> ws, line);
        m->set_line(line);
        cout << "\nContent Added Succesfully\n";
        display(version);
        // updating number of operations
        version->set_operations(version->operations() + 1);
    }
    // a function to overwrite
    void update(Version *version)
    {
        int choice, line_no;
        string line;
        cout << "\n1. Overwrite a Line\n2. Overwrite a File\n\nEnter your choice :";
        cin >> choice;
        // for single line overwrite
        if (choice == 1)
        {
            display(version);
            cout << "\nEnter which line to overwrite :";
            cin >> line_no;
            if (line_no < 0 || line_no > version->msg_size())
            {
                cout << "\nInvalid Line Number\n";
                return;
            }
            cout << "\nEnter the new msg :";
            getline(cin >> ws, line);
            // getting the old msg and setting new msg
            Msg *m = version->mutable_msg(line_no - 1);
            m->set_line(line);
        }
        // overwrite a entire file
        else if (choice == 2)
        {
            // deleting the file first
            delete_file(version);
            // ading the new contents
            cout << "\nEnter number of lines to insert :";
            cin >> line_no;
            cout << "\nEnter the Content :\n";
            for (int i = 0; i < line_no; i++)
            {
                Msg *m = version->add_msg();
                getline(cin >> ws, line);
                m->set_line(line);
            }
        }
        else
        {
            cout << "\nInvalid Choice!\n";
            return;
        }
        cout << "\nOverwrite Successful!\n";
        display(version);
        // updating number of operations
        version->set_operations(version->operations() + 1);
    }
    // function to delete single line
    void delete_line(Version *version)
    {
        int line_no;
        display(version);
        cout << "\nEnter the line no to delete :";
        cin >> line_no;
        if (line_no < 0 || line_no > version->msg_size())
        {
            cout << "\nInvalid Line Number\n";
            return;
        }
        RepeatedPtrField<Msg> *rem = version->mutable_msg();
        // this will delete from line_no-1 1 object
        rem->DeleteSubrange(line_no - 1, 1);
    }
    void delete_file(Version *version)
    {
        RepeatedPtrField<Msg> *rem = version->mutable_msg();
        // this will delete from 0(first line) to size object
        rem->DeleteSubrange(0, version->msg_size());
    }
    void display(Version *version)
    {
        if (version->msg_size() == 0)
        {
            cout << "\nThe File is Empty!\n";
            return;
        }
        cout << "\nThe File Cotents Are : \n";
        for (int i = 0; i < version->msg_size(); i++)
        {
            const Msg &m = version->msg(i);
            cout << i + 1 << ". " << m.line() << endl;
        }
    }
    void display_version(){
        int v;
        cout<<"\nThe latest Version is : "<<project.latest_version();
        cout<<"\n\nEnter which version to Display : ";
        cin>>v;
        Version *version=project.mutable_version(v-1);
        if (version->msg_size() == 0)
        {
            cout << "\nThe File is Empty!\n";
            return;
        }
        cout << "\nThe File Cotents Are : \n";
        for (int i = 0; i < version->msg_size(); i++)
        {
            const Msg &m = version->msg(i);
            cout << i + 1 << ". " << m.line() << endl;
        }
    }
    void revert(string filename,Version *version)
    {
        int v;
        int status;
        if (project.latest_version() == 1)
        {
            cout << "\nCannot Revert since only one version Available\n";
            return;
        }
        cout << "\nThe Latest Version is : " << project.latest_version();
        cout << "\n\nEnter the version to revert :";
        cin >> v;
        if (v > project.latest_version() || v <= 0)
        {
            cout << "\nInvalid Version Number\n";
            return;
        }
        delete_file(version);
        Version old=project.version(v-1);
        //copying content from the old version
        for (int i = 0; i < old.msg_size(); i++)
        {
            const Msg &m1 = old.msg(i);
            Msg *m2 = version->add_msg();
            m2->set_line(m1.line());
        }
        cout<<"\nReverting to the version created on : "<<old.time();
        cout << "\nRevert is Successful!\n";
    }
    // creating new version function
    void new_v(string filename,Version *version)
    {
        Version *new_version=project.add_version();
        project.set_latest_version(project.latest_version() + 1);
        cout << "\nCreating a new version!\n";
        // setting the new project with upgraded version
        new_version->set_id(version->id());
        new_version->set_user_id(user_id);
        new_version->set_name(filename);
        new_version->set_operations(0);
        time_t t = time(0);
        string dt = string(ctime(&t));
        new_version->set_time(dt);
        for (int i = 0; i < version->msg_size(); i++)
        {
            const Msg &m1 = version->msg(i);
            Msg *m2 = new_version->add_msg();
            m2->set_line(m1.line());
        }
        // updating version details
        ofstream output;
        output.open(path + filename + ".txt", ios::out | ios::binary);
        if (!project.SerializeToOstream(&output))
        {
            cerr << "\nFailed to write address book." << endl;
            exit(0);
        }
    }
    void list_operations()
    {
        // checking whether the directory is available
        check_directory();
        path = "./" + user_id + "/";
        string filename, temp;
        int choice, x;
        list_projects();
        if (n == 0)
        {
            cout << "\nNo Projects Found!\n";
            return;
        }
        cout << "\nEnter the project name to Open : ";
        cin >> temp;
        filename = temp + ".txt";
        if (!fs::exists(path + filename))
        {
            cout << "\nFile Not Found!\n";
            return;
        }
        // getting the version details
        fstream input(path + filename, ios::in | ios::binary);
        
        if (!project.ParseFromIstream(&input))
        {
            cerr << "\nFailed to parse address book." << endl;
            exit(0);
        }
        // getting the latest version project
        
        Version *version=project.mutable_version(project.latest_version()-1);
       // cout<<"version msg"<<version.msg()
        // doing the requirerd operations
        cout << "\nOperations Available\n\n1. Add\n2. Update\n3. Delete\n4. Display\n5. Revert\n\nEnter your choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            add(version);
            break;
        case 2:
            update(version);
            break;
        case 3:
        {
            cout << "\n1. Delete a Line\n2. Delete a File\n\nEnter your choice :";
            cin >> x;
            if (x == 1)
                delete_line(version);
            else if (x == 2)
                delete_file(version);
            else
            {
                cout << "\nInvalid Choice!";
                break;
            }
            cout << "\nDelete Successful!\n";
            display(version);
            // updating number of operations
            version->set_operations(version->operations() + 1);
            break;
        }
        case 4:
            display_version();
            break;
        case 5:
            revert(temp,version);
            break;
        default:
            cout << "\nInvalid Choice\n";
            break;
        }
        // creating a new version when the no_of_operation reaches 5
        if (version->operations() >= 5)
            new_v(temp,version);
        // updating the project details in a file after doing operations
        ofstream output;
        output.open(path + filename, ios::out | ios::binary);
        if (!project.SerializeToOstream(&output))
        {
            cerr << "\nFailed to write address book." << endl;
            exit(0);
        }
    }
};
