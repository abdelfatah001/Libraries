#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <ctime>
#include <string>
#include "clsString.h"

using namespace std;

class clsDate
{
    short _day = 1;
    short _month = 1;
    short _year = 1900;
    short _hour = 0;
    short _minute = 0;
    short _second = 0;

protected :

    short Read_year()
    {
        short year;
        cout << "Enter a year ? ";
        cin >> year;
        return year;
    }

    short Read_month()
    {
        short month;
        do{
            cout << "Enter a month ? ";
        cin >> month;
        if (month < 1 || month > 12)   {cout << "Invalid innput\n";}
        }while(month < 1 || month > 12);
        return month;
    }

    short Read_day()
    {
        short day;
        do
        {
            cout << "Enter a day ? ";
            cin >> day;
            if (day < 1 || day > 31)   {cout << "Invalid innput\n";}
        }while(day < 1 || day > 31);
        return day;
    }
    
    static string MonthShortName (int Month_Number)
    {
        string Months [12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Agu","Sep","Oct","Nov","Dec"};
        return Months [Month_Number - 1];
    }

public :

    // constructor
    clsDate ()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        _day    = now->tm_mday;
        _month  = now->tm_mon + 1;
        _year   = now->tm_year + 1900;
        _hour   = now->tm_hour;
        _minute = now->tm_min;
        _second = now->tm_sec;
    }

    clsDate (short day, short month, short year)
    {
        _day    = day;
        _month  = month;
        _year   = year;

    }

    // constructor
    clsDate (short day, short month, short year, short hour, short minute, short second)
    {
        _day    = day;
        _month  = month;
        _year   = year;
        _hour   = hour;
        _minute = minute;
        _second = second;
    }

    // constructor
    clsDate (string str_date)
    {
        vector<string>vDate = clsString::Split(str_date, "/");
        _day   = stoi(vDate[0]);
        _month = stoi(vDate[1]);
        _year  = stoi(vDate[2]);
    }

    // constructor
    clsDate (short day_order, short year)
    {
        clsDate date = GetDateFromDayOrder(day_order, year);
        _day = date._day;
        _month = date._month;
        _year = date._year;
    }



    void SetDay (short day)
    {
        _day = day;
    }

    short GetDay ()
    {
        return _day;
    }

    void SetMonth (short month)
    {
        _month = month;
    }

    short GetMonth ()
    {
        return _month;
    }
    
    void SetYear (short year)
    {
        _year = year;
    }

    short GetYear ()
    {
        return _year;
    }

    static clsDate SystemDate_Time ()
    { /// to get date from system
        time_t t = time(0);
        tm * now  = localtime(&t);
        short day , month , year , hour , minute , second;
        day    = now->tm_mday;
        month  = now->tm_mon + 1;
        year   = now->tm_year + 1900;
        hour   = now->tm_hour;
        minute = now->tm_min;
        second = now->tm_sec;
        return clsDate(day, month, year, hour, minute, second);
    }

    static string SystemDate_TimeString ()
    { /// to get date from system
        time_t t = time(0);
        tm * now  = localtime(&t);
        short day , month , year , hour , minute , second;
        day    = now->tm_mday;
        month  = now->tm_mon + 1;
        year   = now->tm_year + 1900;
        hour   = now->tm_hour;
        minute = now->tm_min;
        second = now->tm_sec;
        return to_string(day) + '/' + to_string(month) + '/' + to_string(year)
        + " - " + to_string(hour) + ":" + to_string(minute) + ":"  + to_string(second);
    }

// conversion between date and string 

    static clsDate StrToDate (string str_date)// to convert string to date
    {
        vector<string>vDate = clsString::Split(str_date, "/");
        short day , month , year;
        day   = stoi(vDate[0]);
        month = stoi(vDate[1]);
        year  = stoi(vDate[2]);
        return clsDate(day, month, year);
    }

    static string TimeToStr (const clsDate & date) // to get the string from time data type 
    {
        return to_string(date._hour) + ":" + to_string(date._minute) + to_string(date._second);
    }

    static string DateToStr (const clsDate & date) // to get the string from date data type 
    {
        return to_string(date._day) + '/' + to_string(date._month) + '/' + to_string(date._year);
    }

    string DateToStr () // to get the string from this date data type 
    {
        return DateToStr (*this);
    }


// Get date inut from user 


    void Read_date ()  // to get date from user in a date form
    {
        _day   = Read_day();
        _month = Read_month();
        _year  = Read_year();
    }

    void get_date(const string & prompt) // to get date from user in a str form
    {
        cout << prompt << endl;
        do
        {
            string str_date;
            getline(cin >> ws, str_date);
            *this = StrToDate(str_date);
            if (!IsValid())
                cout << "Please Enter a valid date?\n";
        } while (!IsValid());
        
    }

//Date validation

    static bool IsLeapYear (int year)
    {
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    }

    bool IsLeapYear ()
    {
        return IsLeapYear (_year);
    } 

    static short NumberOfDaysInYear (short year)
    { 
        return (IsLeapYear(year)) ? 366 : 365;
    }

    short NumberOfDaysInYear ()
    {
        return NumberOfDaysInYear(_year);
    }

    static short NumberOfDaysInMonth (int year, short month)
    {
        short NumOfDays [12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        return (month == 2) ? (IsLeapYear(year) ? 29 : 28 ) : NumOfDays[month - 1];
    }

    short NumberOfDaysInMonth ()
    {
        return NumberOfDaysInMonth(_year, _month);
    }

    

    static bool IsValid(const clsDate& Date) 
    { 
        if (Date._day < 1 || Date._day > 31) 
            return false; 
        
        if (Date._month < 1 || Date._month > 12) 
            return false; 
            
        short month_days = NumberOfDaysInMonth(Date._year, Date._month); 
        if (Date._day > month_days) 
            return false; 
            
        return true; 
        } 
        
    bool IsValid() const 
    { 
        return IsValid(*this); 
    }


//Day order 

    static short DayOrderInYear (clsDate date)
    {
        short order = 0;
        for (size_t i = 1; i < date._month; i++)
        {
            order +=  NumberOfDaysInMonth(date._year, i);
        }
        order += date._day;
        return order;
    }

    short DayOrderInYear ()
    {
        return DayOrderInYear(*this);
    }

    static clsDate GetDateFromDayOrder (short day_order, short year)
    {
        clsDate date;
        date._year = year;
        short remaining_days = day_order;
        date._month = 1;
        while(true)
        {
            short month_days = NumberOfDaysInMonth(year, date._month);
            
            if (remaining_days > month_days)
            {
                remaining_days -= month_days;
                date._month++;
            }
            else
            {
                date._day = remaining_days;
                break;
            }
        }
        return date;
    }

    static short DayOrderInWeek (clsDate date)
    {
        short a = (14 - date._month) / 12;
        short y = date._year - a;
        short m = date._month + (12*a) - 2;
        return (date._day + y + (y/4) - (y/100) + (y/400) + ((31*m) / 12)) % 7;
    }

    short DayOrderInWeek ()
    {
        return DayOrderInWeek(*this);
    }


// print  

    void Print ()  // to print the date in a string data type
    {
        cout << DateToStr();
    }


    static string Date () // To get the date of the day
    {
        return DateToStr(clsDate());
    }

    static string Time () // To get the time of now
    {
        return TimeToStr(clsDate());
    }
    
    static void Print_Month_Calender (short month, short year)
    {
        int Num_Of_Days = NumberOfDaysInMonth(year,month);

        clsDate date;
        date._day   = 1;
        date._month = month;
        date._year  = year;

        int current = DayOrderInWeek(date);

        printf("\n  _______________%s________________\n\n", MonthShortName(month).c_str());
    //The c_str() function is used to convert a C++ std::string to a C-style string
        printf ("  Sun  Mon  Tue  Wed  Thr  Fri  Sat\n");
        int i;
        for (i=0; i < current; i++)
            printf("     ");
        
        for (int j=1; j < Num_Of_Days; j++)
        {   
            printf("%5d", j);
            //The %5d in the printf statement is a format specifier that tells printf to print an integer (d) in a field that is at least 5 characters wide
            if (++i == 7)  //++i == 7: This increments the value of i by 1 and then checks if the result equals 7. This increment happens every time a day is printed.
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n  _________________________________\n");
    }

    static void calender_head (short year)
    {
        printf("\n  __________________________________\n\n");
        printf("             Calender %d            \n",year);
        printf("  __________________________________\n");
    }

    static void Print_Year_Calrnder (short year)
    {
        calender_head(year);
        for (int i=1; i<=12; i++)
        {
            Print_Month_Calender(i, year);
        }
    }


// Is that last 

    static bool IsLastDayOfMonth (clsDate date)
    {
        return (date._day == NumberOfDaysInMonth(date._year, date._month));
    }

    bool IsLastDayOfMonth ()
    {
        return IsLastDayOfMonth(*this);
    }

    static bool IsLastMonth (short month)
    {
        return (month == 12);
    }

    bool IsLastMonth ()
    {
        return IsLastMonth(_month);
    }


//Add to date

    static clsDate DateItAfterAdding (clsDate & date, short add_this)
    {

        short remaining_days = add_this + DayOrderInYear(date);
        date._month = 1;
        date._day   = 1;
        short month_days = 0;
        short year_days  = 0;
        while (true)
        {
            month_days = NumberOfDaysInMonth(date._year, date._month);
            year_days  = NumberOfDaysInYear (date._year);

            if (remaining_days > year_days)
            {
                remaining_days -= year_days;
                date._year++;
            }

            else if (remaining_days > month_days)
            {
                remaining_days -= month_days;
                date._month++;
            }

            else
            {
                date._day = remaining_days;
                if (remaining_days == 0)
                {
                    date._day = 1;
                }
                break;
            }
        }

        return date;
    }

    void DateItAfterAdding (short add_this)
    {
        DateItAfterAdding(*this, add_this);
    }

    static clsDate AddOneDay (clsDate & date)
    {

        if (IsLastDayOfMonth(date))
        {
            if (IsLastMonth(date._month))
            {
                date._day   = 1;
                date._month = 1;
                date._year += 1;
            }
            else
            {
                date._day = 1;
                date._month += 1;
            }
            
        } 
        else
        {
            date._day += 1;
        }

        return date;
    }

    void AddOneDay ()
    {
        AddOneDay(*this);
    }

    static clsDate AddXDays (clsDate & date, short days_to_add)
    {
        for (short i = 0; i < days_to_add; i++)
        {
            date = AddOneDay(date);
        }
        return date;
    }

    void AddXDays (short days_to_add)
    {
        AddXDays(*this, days_to_add);
    }

    static clsDate AddOneWeek (clsDate & date)
    {
        for(short i=0; i < 7; i++)
        {
            date = AddOneDay(date);
        }
        return date;
    }

    void AddOneWeek ()
    {
        AddOneWeek(*this);
    }

    static clsDate AddXWeeks (clsDate & date, short weeks)
    {
        for(short i=0; i < weeks; i++)
        {
            date = AddOneWeek(date);
        }
        return date;
    }

    void AddXWeeks (short weeks)
    {
        AddXWeeks(*this, weeks);
    }

    static clsDate AddOneMonth (clsDate & date)
    {
        if (date._month == 12)
        {
            date._month = 1;
            date._year++;
        }
        else
        {
            date._month++;
        }

        short month_days = NumberOfDaysInMonth(date._year, date._month);
        if(date._day > month_days)
            date._day = month_days;

        return date;
    }

    void AddOneMonth ()
    {
        AddOneMonth(*this);
    }

    static clsDate AddXMonth (clsDate & date, short months)
    {
        for(short i=0; i < months; i++)
        {
            date = AddOneMonth(date);
        }
        return date;
    }

    void AddXMonth (short months)
    {
        AddXMonth(*this, months);
    }

    static clsDate AddOneYear (clsDate & date)
    {
        date._year += 1;
        return date;
    }

    void AddOneYear ()
    {
        AddOneYear(*this);
    }

    static clsDate AddXYear (clsDate & date, short years)
    {
        for(short i=0; i < years; i++)
        {
            date = AddOneYear(date);
        }
        return date;
    }

    void AddXYear (short years)
    {
        AddXYear(*this, years);
    }


    //Substract from date

    static clsDate DecreaseOneDay (clsDate & date)
    {

        if (date._day == 1)
        {
            if (date._month == 1)
            {
                date._day   = 31;
                date._month = 12;
                date._year--;
            }
            else
            {
                date._day = NumberOfDaysInMonth(date._year, date._month - 1);
                date._month--;
            }
            
        } 
        else
        {
            date._day--;
        }

        return date;
    }

    void DecreaseOneDay ()
    {
        DecreaseOneDay(*this);
    }

    static clsDate DecreaseXDay (clsDate & date, short days_to_substract)
    {
        for (short i = 0; i < days_to_substract; i++)
        {
            date = DecreaseOneDay(date);
        }
        return date;
    }

    void DecreaseOneDay (short days_to_substract)
    {
        DecreaseOneDay(*this), days_to_substract;
    }

    static clsDate DecreaseOneWeek (clsDate & date)
    {
        for(short i=0; i < 7; i++)
        {
            date = DecreaseOneDay(date);
        }
        return date;
    }

    void DecreaseOneWeek ()
    {
        DecreaseOneWeek(*this);
    }

    static clsDate DecreaseXWeek (clsDate & date, short weeks)
    {
        for(short i=0; i < weeks; i++)
        {
            date = DecreaseOneWeek(date);
        }
        return date;
    }

    void DecreaseXWeek (short weeks)
    {
        DecreaseXWeek(*this, weeks);
    }

    static clsDate DecreaseOneMonth (clsDate & date)
    {
        if (date._month == 1)
        {
            date._month = 12;
            date._year--;
        }
        else
        {
            date._month--;
        }

        short month_days = NumberOfDaysInMonth(date._year, date._month);
        if(date._day > month_days)
            date._day = month_days;
            
        return date;
    }

    void DecreaseOneMonth ()
    {
        DecreaseOneMonth(*this);
    }

    static clsDate DecreaseXMonths (clsDate & date, short months)
    {
        for(short i=0; i < months; i++)
        {
            date = DecreaseOneMonth(date);
        }
        return date;
    }

    void DecreaseXMonths (short months)
    {
        DecreaseXMonths(*this, months);
    }

    static clsDate DecreaseOneYear (clsDate & date)
    {
        date._year -= 1;
        return date;
    }

    void DecreaseOneYear ()
    {
        DecreaseOneYear(*this);
    }

    static clsDate DecreaseXYear (clsDate & date, short years)
    {
        for(short i=0; i < years; i++)
        {
            date = DecreaseOneYear(date);
        }
        return date;
    }

    void DecreaseXYear (short years)
    {
        DecreaseXYear(*this, years);
    }


    // Date Compare 

    static bool IsDate1BeforeDate2 (clsDate date1, clsDate date2)
    {
        return (date1._year < date2._year) ? true : (date1._month < date2._month ? true : (date1._day < date2._day? true : false));
    }

    bool IsBeforeDate (clsDate date)
    {
        return IsDate1BeforeDate2(*this, date);
    }

    static bool IsTwoDatesEqual(clsDate date1, clsDate date2)
    {
        return  (date1._year == date2._year) ? ((date1._month == date2._month) ? ((date1._day == date2._day) ? true : false ) :false ) : false ;
    }
    
    bool IsEqualsTo (clsDate date)
    {
        return IsTwoDatesEqual(*this, date);
    }

    static bool IsDate1AfterDate2 (clsDate date1, clsDate date2)
    {
        return (IsDate1BeforeDate2(date1, date2)) ? 
            false : (IsTwoDatesEqual(date1, date2) ?
                false :true); true;
    }

    bool IsAfterDate (clsDate date)
    {
        return IsDate1AfterDate2(*this, date);
    }


// Swap dates 

    static void Swap  (clsDate &date1, clsDate &date2)
    {
        clsDate temp;

        temp._day    = date1._day;
        temp._month  = date1._month;
        temp._year   = date1._year;

        date1._day   = date2._day;
        date1._month = date2._month;
        date1._year  = date2._year;

        date2._day   = temp._day;
        date2._month = temp._month;
        date2._year  = temp._year;

    }

    void Swap(clsDate &date)
    {
        Swap(*this, date);
    }


    short Difference (clsDate date1, clsDate date2, bool include_end_day = false)
    {// to get difference between two dates in days
        int difference = 0;
        short swap_flag = 1;
        if(!IsDate1BeforeDate2(date1, date2))
        {
            Swap(date1, date2);
            swap_flag = -1;
        }
        if (IsDate1BeforeDate2(date1, date2))
        {
            while (IsDate1BeforeDate2(date1, date2))
            {
                difference++;
                date1 =  AddOneDay(date1);
            } 
            return difference;
        }
        return (include_end_day) ? ++difference * swap_flag : difference * swap_flag ;
    }

    short Difference (clsDate date, bool include_end_day = false)
    {
        return Difference(*this, date, include_end_day);
    }

    static string DayShortName(clsDate date)
    {
        string arrDayNames[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
        return arrDayNames[DayOrderInWeek(date)];
    }

    string DayShortName()
    {
        return DayShortName(*this);
    }

    static short IsEndOfWeek(clsDate date)
    {// is it sat
        return DayOrderInWeek(date) == 6;
    }

    short IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekend(clsDate date)
    {// is holiday of the weekend
        short DayIndex = DayOrderInWeek(date);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekend()
    {
        return IsWeekend(*this);
    }

    static bool IsBusinessDay(clsDate date)
    {
        return !IsWeekend(date);
    }

    bool IsBusinessDay()
    {
        return IsBusinessDay(*this);
    }

    static short CalculateVacation(clsDate start, clsDate end)
    {//to valculate the vaccation days only without the holidays 
        short counter = 0;
        while (IsDate1BeforeDate2(start, end))
        {
            if (IsBusinessDay(start))
                counter++;

            start = AddOneDay(start);
        }
        return counter;
    }

    short CalculateVacationfrom (clsDate date)
    {
        return CalculateVacation(date, *this);
    }

    short CalculateVacationTo (clsDate date)
    {
        return CalculateVacation(*this, date);
    }


};

// To get the time of now in a string data type      --> Time()
// To get the date of the day in a string data type  --> Date()
// To get the date and time in a clsDate data type   --> SystemDate_Time()
// To get the date and time in a string data type    --> SystemDate_Time()