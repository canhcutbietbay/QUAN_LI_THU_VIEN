#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

struct DateTime
{
    // char Year[3], Month[3], Day[3];
    int Year, Month, Day;
    char res[15];
    DateTime(){};
    DateTime(int year, int month, int day)
    {
        Year = year;
        Month = month;
        Day = day;
    }
    // DateTime(char year[3], char month[3], char day[3])
    // {
    //     strcpy(Year, year);
    //     strcpy(Month, month);
    //     strcpy(Day, day);
    // }
    void GetRes()
    {
        char temp[10];
        itoa(Day, temp, 10);
        if (Day < 10)
            strcat(this->res, "0");
        strcat(this->res, temp);
        strcat(this->res, "/");
        if (Month < 10)
            strcat(this->res, "0");
        itoa(Month, temp, 10);
        strcat(this->res, temp);
        strcat(this->res, "/");
        itoa(Year, temp, 10);
        strcat(this->res, temp);
    }
    void GetTimeNow()
    {
        time_t CurrentTime = time(0);
        tm *Time = localtime(&CurrentTime);
        Year = Time->tm_year + 1900;
        Month = Time->tm_mon + 1;
        Day = Time->tm_mday;
        GetRes();
    }

    void GetSoNgayMuon()
    {
        time_t CurrentTime;
        DateTime Now;
        time(&CurrentTime);
        tm *End, *Start;
        Start = localtime(&CurrentTime);
        Start->tm_year = Year - 1900;
        Start->tm_mon = Month - 1;
        Start->tm_mday = Day;
        unsigned long long Seconds = difftime(CurrentTime, mktime(Start));
        int SoNgayMuon = Seconds / 86400;
        cout << SoNgayMuon << endl;
    }
};

int main()
{
    DateTime Time(2021, 5, 23);
    Time.GetSoNgayMuon();
    DateTime Now;
    Now.GetTimeNow();
    cout << Now.res << endl;
    return 0;
}