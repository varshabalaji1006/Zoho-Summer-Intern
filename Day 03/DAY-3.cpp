#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class building
{
public:
    unique_ptr<unique_ptr<int[]>[]> building2D, visit;
    unique_ptr<int[]> building1D, temp, group,leader_group;
    int row, column, neighbours, leader, no_of_group,no_of_leaderGroup ,start,min_dist;
    void getInfo()
    {
        int x;
        cout << "Enter No of Rows:";
        cin >> row;
        cout << "Enter No of columns:";
        cin >> column;
        // intializing a 2D array
        building2D = make_unique<unique_ptr<int[]>[]>(row);
        // visit matrix to check whether the building is visited if visited it will have the value 1 else 0
        visit = make_unique<unique_ptr<int[]>[]>(row);
        // araray of count of the group members
        group = make_unique<int[]>(row * column);
        cout << "Enter the elemnts:\n";
        // intializing the visit and builiding  matrix
        for (int i = 0; i < row; i++)
        {
            building1D = make_unique<int[]>(column);
            temp = make_unique<int[]>(column);
            for (int j = 0; j < column; j++)
            {
                cin >> x;
                building1D[j] = x;
                temp[j] = 0;
            }
            building2D[i] = move(building1D);
            visit[i] = move(temp);
        }
    }
   
    void path(int Xcor, int Ycor, int num,bool control)
    {
        if (visit[Xcor][Ycor] == num)
        {
            return;
        }
        else
        {
            // to find the neighbours of a building num is to assign that particular value to visit
            if(control){
                neighbours += building2D[Xcor][Ycor];
                if(neighbours!=0)visit[Xcor][Ycor]=num;
            }
            else{
                for (int i = 0; i < no_of_leaderGroup; i++)
                {
                int x, y;
                x = leader_group[i] / 10;
                y = leader_group[i] % 10;
                if ((abs(Xcor - x) + abs(Ycor - y) - 1) < min_dist)
                    min_dist = abs(Xcor - x) + abs(Ycor - y) - 1;
                }
            }
           
            if (Xcor + 1 < row && building2D[Xcor + 1][Ycor] != 0)
            {
                visit[Xcor][Ycor] = num;
                path(Xcor + 1, Ycor, num,control);
            }
            if (Xcor - 1 >= 0 && building2D[Xcor - 1][Ycor] != 0)
            {
                visit[Xcor][Ycor] = num;
                path(Xcor - 1, Ycor, num,control);
            }
            if (Ycor + 1 < column && building2D[Xcor][Ycor + 1] != 0)
            {
                visit[Xcor][Ycor] = num;
                path(Xcor, Ycor + 1, num,control);
            }
            if (Ycor - 1 >= 0 && building2D[Xcor][Ycor - 1] != 0)
            {
                visit[Xcor][Ycor] = num;
                path(Xcor, Ycor - 1, num,control);
            }
            return ;
        }
    }
    // to find neighbours of each building
    void groups()
    {
        no_of_group = 0;
        neighbours = 0;
        leader=0;
        cout << "The No of groups are:";
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (building2D[i][j] != 0)
                {
                    path(i, j, 1,true);
                    if (neighbours != 0)
                    {
                        group[no_of_group] = neighbours;
                        no_of_group++;
                        if (neighbours > leader)
                        {
                            leader = neighbours;
                            start = i * 10 + j;
                        }
                    }
                    neighbours = 0;
                }
            }
        }
        cout << no_of_group << "\nthe groups are:";
        // to print eacg groupm members
        for (int i = 0; i < no_of_group; i++)
        {
            cout << group[i] << " ";
        }
    }
    // to get the leader among the group members
    void get_leader()
    {
        cout << "\nThe leader is " << leader;
    }
    void print()
    {
        cout << "The matrix :\n";
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
                cout << building2D[i][j] << " ";
            cout << endl;
        }
    }
    void find_distance()
    {
        int i, j;
        i = start / 10;
        j = start % 10;
        path(i, j, 3,true);
        //array of leader group indexes
        leader_group = make_unique<int[]>(row * column);
        no_of_leaderGroup=0;
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < column; j++)
                if (visit[i][j] == 3){
                    leader_group[no_of_leaderGroup]=i*10+j;
                    no_of_leaderGroup++;
                }
        }
        cout << "\nthe path for respective groups:\n";
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < column; j++)
            {
                if (visit[i][j] == 1)
                {
                    min_dist=9999; 
                    path(i, j, 2,false);
                    cout << min_dist << " ";
                }
            }
        }
    }
};

int main()
{
    building b;
    b.getInfo();
    b.print();
    b.groups();
    b.get_leader();
    b.find_distance();
    return 0;
}
