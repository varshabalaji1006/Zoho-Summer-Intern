#include <iostream>
using namespace std;
class vehicle
{
public:
    string type, brand, model, color;
    float mileage, price;
    //initialising using constructor
    vehicle(string type, string brand, string model, string color, float mileage, float price)
    {
        this->type = type;
        this->brand = brand;
        this->model = model;
        this->color = color;
        this->mileage = mileage;
        this->price = price;
    }
    friend bool operator<(const vehicle &v1, const vehicle &v2);
    friend ostream &operator<<(ostream &os, const vehicle &c);
    virtual  int get_no_of_wheels() { return 0; };
};
//car inherited from vehicle
class car : public vehicle
{
private:
    int no_of_person;
    string cartype;

public:
    //intializing using constructor
    car(string type, string brand, string model, string color, float mileage, float price, int no_of_person, string cartype) : vehicle(type, brand, model, color, mileage, price)
    {
        this->no_of_person = no_of_person;
        this->cartype = cartype;
    }
    int get_no_of_wheels()
    {
        return 4;
    }
};
//bike inherited from vehicle
class bike : public vehicle
{
private:
    float weight;
    string biketype;
public:
    bike(string type, string brand, string model, string color, float mileage, float price, float weight, string biketype) : vehicle(type, brand, model, color, mileage, price)
    {
        this->weight = weight;
        this->biketype = biketype;
    }
     int get_no_of_wheels()
    {
        return 2;
    }
};
//overloading less than operator to compare two vehicles
bool operator<(const vehicle &v1, const vehicle &v2)
{
    return v1.price < v2.price;
}
//overloading stream insertion operator
ostream &operator<<(ostream &os, const vehicle &c)
{
    os << "Brand:  " << c.brand << endl
       << "Model: " << c.model << endl
       << "Type: " << c.type << endl
       << "Color: "
       << c.color << endl
       << "Price: " << c.price<<endl;
    return os;
}

int main()
{
    //creating objects for car
    car c1("diesel", "Hyundai", "i-9", "blue", 70, 500000, 4, "SUV");
    car c2("diesel", "Toyato", "i20", "grey", 100, 600000, 6, "SEDAN");
    //creating objects for bike
    bike b1("petrol", "Yamaha", "fascino", "red", 50, 100000, 75.00, "scooty");
    bike b2("petrol", "yamaha", "RX15", "blue", 60, 200000, 90.00, "Motor Bike");
    //printing car members
    cout <<"Car details:\n" <<c1<<endl<<endl<<c2<<endl;
    //printing bike members
    cout <<"Bike details:" <<b2<<endl<<endl<<b2<<endl;
    //comparing car and bike
    if(c1<b1)cout << "car is cheaper than bike"<<endl;
    else cout << "bike is cheaper than car"<<endl;
    //comparing two bike
    if(b1<b2)cout << b1.model<<" is cheaper than "<<b2.model<<endl;
    else cout << b2.model<<" is cheaper than "<<b1.model<<endl;
    //comparing two car
    if(c1<c2)cout << c1.model<<" is cheaper than "<<c2.model<<endl;
    else cout << c2.model<<" is cheaper than "<<c1.model<<endl;
    cout << "No of wheels in car " << c1.get_no_of_wheels() << endl;
    cout << "NO of wheels in bike " << b1.get_no_of_wheels();
}