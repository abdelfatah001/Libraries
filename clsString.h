#pragma once
#include <iostream>
#include <vector>

using namespace std;

class clsString
{
    string _value;


protected :

    static char invert_case (char c)
    {
        return (isupper(c))? tolower(c) : toupper(c);
    }

    static bool IsVowel (char c)
    {
        char vowels [5] = {'a','e','i','o','u'};
        for (char i : vowels)
        {
            if (c == i || c == toupper(i))  {return true;}
        }
        return false;
    } 

public :

    clsString (string value)
    {
        _value = value;
    }

    clsString ()
    {
        _value = "";
    }

    clsString operator= (const string & str_name)
    {
        _value = str_name;
        return *this;
    }

    string get_it ()
    {
        return _value;
    }




    static void Get_String(string & str, const string  & prompt)  // Clear the buffer before reading the input
    {
        cout << prompt << endl;
        getline(cin >> ws, str);
    }

    void Get_String (const string  & prompt)
    {
        Get_String(_value, prompt);
    }

    static void get_string (string & str, const string  & prompt)
    {
        cout << prompt << endl;
        getline(cin, str);
    }

    void get_string (const string  & prompt)
    {
        get_string(_value, prompt);
    }




    static string ToLower(string s)
    {
        for (short i = 0; i < s.length(); i++)
        {
            s[i] = tolower(s[i]);
        }
        return s;
    }

    void ToLower ()
    {
        ToLower(_value);
    }

    static string ToUpper(string s)
    {
        for (short i = 0; i < s.length(); i++)
        {
            s[i] = toupper(s[i]);
        }
        return s;
    }

    void ToUpper ()
    {
        ToUpper(_value);
    }





    static string Trim_left (string str)
    {
        for(short i = 0; i < str.length(); i++)
        {
            // the loop still iterate untill found a character
            if(str[i] != ' ')   
            { 
                // Extract the string from the non-space character to the end of string 
                // by removing the spaces in the left that in i count it.

                return str.substr(i, str.length()-i);
            }
        }  
        return "";
    }

    void Trim_left ()
    {
        Trim_left(_value);
    }

    static string Trim_right (string str)
    {
        for(short i = str.length(); i >= 0; i--)
        {
            if(str[i] != ' ')
            {
                return str.substr(0, i+1);
            }
        }
        return "";
    }

    void Trim_right ()
    {
        Trim_right(_value);
    }

    static string Trim (string str)
    {
        return Trim_left(Trim_right(str));
    }

    void Trim ()
    {
        Trim(_value);
    }





    static int Length (string s)
    {
        return s.length();
    }

    int Length ()
    {
        return Length(_value);
    }





    static int CountWords (string str)
    {
        int no_of_words = 1;
        string delim = " ";
        int pos = 0;
        string word;
        while((pos = str.find(delim)) != string::npos)
        {
            word = str.substr(0, pos);
            if (word != "")
            {
                no_of_words++;
            }
            str.erase(0, pos + delim.length());
        }
        return no_of_words;
    }

    int CountWords ()
    {
        return CountWords(_value);
    }

    static void SplitEachWord (string str)
    {// this function take a str and split it to words and prit each word in a line
        string delim = " ";
        short pos = 0;
        string word;
        while((pos = str.find(delim)) != string::npos)
        {
            word = str.substr(0,pos);
            if(word != "") {cout << word << endl;}
            str.erase(0, pos + delim.length());
        }

        if (str != ""){ cout << str << endl; }
    }

    void SplitEachWord ()
    {
        SplitEachWord (_value);
    }

    static vector<string> Split (string str, string seperator = " ")
    {
        vector<string> tokens;
        int pos = 0;
        string word;
        while ((pos = str.find(seperator)) != string::npos)
        {
            word = str.substr(0,pos);
            if(word != "")  {tokens.push_back(word);}
            str.erase(0, pos + seperator.length());
        }
        if (str != "")   {tokens.push_back(str);}
        return tokens;
    }

    vector<string> Split (string seperator = " ")
    {
        return Split(_value, seperator);
    }

    static string Replace (string str, string replace_this, string by_this, bool match_case = true)
    {
    // this function to replace a word in a string by another word 
    // Match case if false it will compare them in the same case
        vector<string> vec = Split (str, " ");
        string str2;
        for (string s : vec) 
        {
            if(match_case)
            {
                if (s == replace_this) { s = by_this;}
            }
            
            else  
            { 
                if (ToLower(s) == ToLower(replace_this))
                {
                    s = by_this;
                } 
            }
            str2 += s + " "; 

        }
        return str2;
    }

    void Replace (string replace_this, string by_this, bool match_case = true)
    {
        Replace(_value, replace_this, by_this, match_case);
    }

    static string Reverse_Words (string str)
    {
        vector <string> vec_str;
        string r_str = ""; 
        vec_str = Split (str, " ");
        vector <string> ::iterator it = vec_str.end();
        while (it != vec_str.begin())
        {
            --it;
            r_str += *it + " ";
        }
        r_str = r_str.substr(0, r_str.length()-1);
        return r_str;
    }

    void Reverse_Words ()
    {
        Reverse_Words(_value);
    }

    static string JoinString(vector<string> vString, string Delim)
    {

        string S1 = "";

        for (string& s : vString)
        {
            S1 = S1 + s + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());


    }

    static string JoinString(string arrString[], short Length, string Delim)
    {

        string S1 = "";

        for (short i = 0; i < Length; i++)
        {
            S1 = S1 + arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());

    }



    static string RemovePunctuation (string str)
    {
        string str2;
        for (char c : str)
        {
            if (!ispunct(c))
            {
                str2 += c;
            }
        }
        return str2;
    }

    void RemovePunctuation ()
    {
        RemovePunctuation (_value);
    }
    
    static string InvertStrCase (string s)
    {
        for(int i=0; i<s.length(); i++)
        {
            s[i] = invert_case(s[i]);
        }
        return s;
    }

    void InvertStrCase ()
    {
        InvertStrCase(_value);
    }

    static int CountUpperLetters (string s)
    {
        int c=0;
        for(int i=0; i<s.length(); i++)
        {
            if(isupper(s[i])) {c++;}
        }
        return c;
    }

    int CountUpperLetters ()
    {
        return CountUpperLetters (_value);
    }

    static int CountLowerLetters (string s)
    {
        int c=0;
        for(int i=0; i<s.length(); i++)
        {
            if(islower(s[i])) {c++;}
        }
        return c;
    }

    int CountLowerLetters ()
    {
        return CountLowerLetters (_value);
    }

    static int CharFrequency (string str, char c, bool match_case = true)
    {  // if matchcase false this means to count each upper and lower case
        int counter = 0;
        for (char i : str)
        {
            if (match_case)
                if (i == c)  {counter++;} 
            
            else
                if (toupper(i) == toupper(c)) {counter++;}
        }
        return counter;
    }

    int CharFrequency (char c, bool match_case = true)
    {
        return CharFrequency(_value, c, match_case);
    }

    static int CountVowels (string str)
    {
        int counter;
        for(char i : str)
        {
            if(IsVowel(i)) {counter++;}
        }
        return counter;
    }

    int CountVowels ()
    {
        return CountVowels(_value);
    }

    static void PrintVowels (string str)
    {
        for (char i : str)
        {
            if(IsVowel(i))  {cout << i << "    ";}
        } 
    }

    void PrintVowels ()
    {
        PrintVowels(_value);
    }




    static string  UpperFirstLetterOfEachWord(string S1)
    {

        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);

        }

        return S1;
    }

    void  UpperFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value  
        _value = UpperFirstLetterOfEachWord(_value);
    }

    static string  LowerFirstLetterOfEachWord(string S1)
    {

        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = tolower(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);

        }

        return S1;
    }

    void  LowerFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value  
        _value = LowerFirstLetterOfEachWord(_value);
    }

    static string  UpperAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }

    void  UpperAllString()
    {
        _value = UpperAllString(_value);
    }

    static string  LowerAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = tolower(S1[i]);
        }
        return S1;
    }

    void  LowerAllString()
    {
        _value = LowerAllString(_value);
    }

};


