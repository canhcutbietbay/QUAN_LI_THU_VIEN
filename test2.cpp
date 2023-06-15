#include <iostream>
#include <string>
#include <ctime>
struct DateTime
{
    char value[10];

};
DateTime GetTimeNow()
{
    time_t CurrentTime = time(0);
    tm *Time = localtime(&CurrentTime);
    DateTime res;
    strcpy(res.value,"");
    char Day[2], Month[2], Year[4];
    itoa(Time->tm_year + 1900, Year, 10);
    itoa(Time->tm_mon + 1, Month, 10);
    itoa(Time->tm_mday, Day, 10);
    strcat(res.value,Day);
    strcat(res.value,"/");
    strcat(res.value,Month);
    strcat(res.value,"/");
    strcat(res.value,Year);
    return res;
}
using namespace std;

int main()
{
    string str = "23/05/2021";
    DateTime Time;
    strcpy(Time.value, str.c_str());
    cout << Time.value << endl;
    Time = GetTimeNow();
    cout << Time.value;
    return 0;
}