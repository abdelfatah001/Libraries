#pragma once
#include <iostream>
#include <limits>
#include <string>
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsInputValidate
{

public :

    template <typename t>

    static bool IsNumBetween (t num, t from, t to)
    {
        return ((num >= from && num <= to) || (num >= to && num <= from ));
    }


    template <typename t>

    static t Get (const string & prompt = "",const string & ValidationMessage = "Invalid value...\n")
    {
        t  Input;
        if (prompt != "")
            cout << prompt;
		// Usage of std::ws will extract all the whitespace character
        while (!(cin >> Input))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ValidationMessage;
        }
		return Input;
    }


    static string GetStr (const string & prompt = "" ,const string & ValidationMessage= "Invalid value...\n")
    {
        string Input;
        if (prompt != "")
            cout << prompt;
		// Usage of std::ws will extract all the whitespace character
        while (!getline(cin >> ws, Input))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ValidationMessage;
        }
		return Input;
    }

    
    template <typename t>

    static t GetBet (t from, t to, string prompt = "", string ValidationMessage = "Invalid value...\n")
    {
        t num = Get<t>(prompt, ValidationMessage);
        while (!IsNumBetween(num, from, to))
        {
            cout << ValidationMessage;
            num = Get<t>(prompt, ValidationMessage);
        }
        return num;
    }

    static bool IsDateBetween (clsDate date, clsDate from, clsDate to)
    {
        return ((date.IsAfterDate(from) || date.IsEqualsTo(from)) 
                &&
                (date.IsBeforeDate(to) || date.IsEqualsTo(to)));
    }


    static bool IsValidDate (clsDate date)
    {
        return clsDate::IsValid(date);
    }


};