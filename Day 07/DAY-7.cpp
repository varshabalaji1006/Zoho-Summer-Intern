#include <iostream>
#include <regex>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;
// lambda function
auto check_limit = [](float value, float limit, string op)
{
    if (op == ">" && value > limit)
        return true;
    if (op == ">=" && value >= limit)
        return true;
    if (op == "==" && value == limit)
        return true;
    if (op == "<" && value < limit)
        return true;
    if (op == "<=" && value <= limit)
        return true;
    return false;
};
class Sensor
{
public:
    string device, op, func;
};
class Devices
{
public:
    bool status;
    int batteryLevel;
    virtual void onConnect() = 0;
    virtual void onDisConnect() = 0;
};
class TemparatureSensor : public Sensor
{
public:
    float temparature = 0, temparature_limit;
    void onTemparatureChange(string msg)
    {
        if (msg == "ti")
            temparature += 1;
        else
            temparature -= 1;
        cout << "\nNew Temperature : " << temparature;
    }
};
class MotionSensor : public Sensor
{
public:
    float distance = 0, distance_limit;
    void onMotionChange(string msg)
    {
        if (msg == "mi")
            distance += 1;
        else
            distance -= 1;
        cout << "\nNew Distance : " << distance;
    }
};
class WaterLevelSensor : public Sensor
{
public:
    float level = 0, level_limit;
    void onLevelChange(string msg)
    {
        if (msg == "wi")
            level += 1;
        else
            level -= 1;
        cout << "\nNew Water Level : " << level;
    }
};
class LuminositySensor : public Sensor
{
public:
    float brightness = 0, brightness_limit;
    void onLumionosityChange(string msg)
    {
        if (msg == "li")
            brightness += 1;
        else
            brightness -= 1;
        cout << "\nNew Brightness : " << brightness;
    }
};
class GasDetectionSensor : public Sensor
{
public:
    float level = 0, level_limit;
    void onLevelChange(string msg)
    {
        if (msg == "gi")
            level += 1;
        else
            level -= 1;
        cout << "\nNew Gas level : " << level;
    }
};
class Smartfan : public Devices
{
public:
    void onConnect()
    {
        status = true;
        cout << "\nThe Fan is on!";
    }
    void onDisConnect()
    {
        status = false;
        cout << "\nThe Fan is off!";
    }
};
class Smartlight : public Devices
{
public:
    void onConnect()
    {
        status = true;
        cout << "\nThe Light is on!";
    }
    void onDisConnect()
    {
        status = false;
        cout << "\nThe Light is off!";
    }
};
class Smartdoor : public Devices
{
public:
    void onConnect()
    {
        status = true;
        cout << "\nThe Door is open!";
    }
    void onDisConnect()
    {
        status = false;
        cout << "\nThe door is close!";
    }
};
class Manager
{
private:
    string command_one, command_two;
    vector<string> token_one, token_two;
    TemparatureSensor t;
    MotionSensor m;
    WaterLevelSensor w;
    LuminositySensor l;
    GasDetectionSensor g;
    Smartfan sf;
    Smartlight sl;
    Smartdoor sd;

public:
    void get_input()
    {
        regex re(R"([\s|:,]+)");
        cout << "\n Enter the if command : ";
        getline(cin >> ws, command_one);
        token_one = tokenize(command_one, re);
        cout << "\n Enter the then command : ";
        getline(cin >> ws, command_two);
        token_two = tokenize(command_two, re);
    }
    vector<string> tokenize(string str, regex re)
    {
        sregex_token_iterator it(str.begin(), str.end(), re, -1);
        vector<string> tokenized{it, {}};
        tokenized.erase(remove_if(tokenized.begin(), tokenized.end(), [](string const &s)
                                  { return s.size() == 0; }),
                        tokenized.end());
        return tokenized;
    }
    void manage()
    {
        transform(token_one[1].begin(), token_one[1].end(), token_one[1].begin(), ::tolower);
        transform(token_two[1].begin(), token_two[1].end(), token_two[1].begin(), ::tolower);
        transform(token_two[2].begin(), token_two[2].end(), token_two[2].begin(), ::tolower);
        if (token_one[1] == "temperature")
        {
            t.temparature_limit = stof(token_one[3]);
            t.op = token_one[2];
            t.device = token_two[1];
            t.func = token_two[2];
            return;
        }
        if (token_one[1] == "luminous")
        {
            l.brightness_limit = stof(token_one[3]);
            l.op = token_one[2];
            l.device = token_two[1];
            l.func = token_two[2];
            return;
        }
        if (token_one[1] == "motion")
        {
            m.distance_limit = stof(token_one[3]);
            m.op = token_one[2];
            m.device = token_two[1];
            m.func = token_two[2];
            return;
        }
        if (token_one[1] == "waterlevel")
        {
            w.level_limit = stof(token_one[3]);
            w.op = token_one[2];
            w.device = token_two[1];
            w.func = token_two[2];
            return;
        }
        if (token_one[1] == "gaslevel")
        {
            g.level_limit = stof(token_one[3]);
            g.op = token_one[2];
            g.device = token_two[1];
            g.func = token_two[2];
            return;
        }
        cout << "\nNo Sensor found!";
    }

    void call(string ip)
    {
        string device, func;
        device = "";
        bool status = false;
        if (ip == "ti" || ip == "td")
        {
            t.onTemparatureChange(ip);
            device = t.device;
            func = t.func;
            status = check_limit(t.temparature, t.temparature_limit, t.op);
        }
        if (ip == "li" || ip == "ld")
        {
            l.onLumionosityChange(ip);
            device = l.device;
            func = l.func;
            status = check_limit(l.brightness, l.brightness_limit, l.op);
        }
        if (ip == "wi" || ip == "wd")
        {
            w.onLevelChange(ip);
            device = w.device;
            func = w.func;
            status = check_limit(w.level, w.level_limit, w.op);
        }
        if (ip == "gi" || ip == "gd")
        {
            g.onLevelChange(ip);
            device = g.device;
            func = g.func;
            status = check_limit(g.level, g.level_limit, g.op);
        }
        if (ip == "mi" || ip == "md")
        {
            m.onMotionChange(ip);
            device = m.device;
            func = m.func;
            status = check_limit(m.distance, m.distance_limit, m.op);
        }
        if (device == "fan")
        {
            if (func == "turnon" && status == true)
                sf.onConnect();
            else if (func == "turnoff" && status == true)
                sf.onDisConnect();
            else if (func == "turnon")
                sf.onDisConnect();
            else
                sf.onConnect();
        }
        if (device == "light")
        {
            if (func == "turnon" && status == true)
                sl.onConnect();
            else if (func == "turnoff" && status == true)
                sl.onDisConnect();
            else if (func == "turnon")
                sl.onDisConnect();
            else
                sl.onConnect();
        }
        if (device == "door")
        {
            if (func == "open" && status == true)
                sd.onConnect();
            else if (func == "close" && status == true)
                sd.onDisConnect();
            else if (func == "open")
                sd.onDisConnect();
            else
                sd.onConnect();
        }
    }
};
int main()
{
    string ip;
    Manager m;
    do
    {
        m.get_input();
        m.manage();
        cout << "\nDo you want to move to keypress commands(1/0):";
        cin >> ip;

    } while (ip != "0");
    cout << "\n\nKeypressed Events:\nti-temperature increase\ntd-temperature decrease";
    cout << "\nli-luminous increase\nld-luminous decrease";
    cout << "\nwi-WaterLevel increase\nwd-WaterLevel decrease";
    cout << "\ngi-GasLevel increase\ngd-Gaslevel decrease";
    cout << "\nmi-motion increase\nmd-motion decrease";
    do
    {
        cout << "\nEnter Command:";
        cin >> ip;
        m.call(ip);
        cout << "\nDo you want to continue(1/0):";
        cin >> ip;
    } while (ip != "0");
    return 0;
}
