//
//  ConsoleManager.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/25/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "ConsoleManager.h"

#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

bool ConsoleManager::promptYesOrNo (const string & prompt)
{
    cout << prompt << " y/n: ";
    
    char input;
    
    while (true)
    {
        cin >> input;
        
        if (input == 'y' || input == 'Y')
        {
            return true;
        }
        else if (input == 'n' || input == 'N')
        {
            return false;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Please enter y or n: ";
        }
    }
}

int ConsoleManager::promptNumber (const string & prompt, int minimum, int maximum)
{
    cout << prompt;
    
    int input;
    
    while (true)
    {
        while (!(cin >> input))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Please enter a valid number: ";
        }
        
        if (input >= minimum && input <= maximum)
        {
            return input;
        }
        cout << "Please enter a number between " << minimum << " and " << maximum << ": ";
    }
}

char ConsoleManager::promptLetter (const string & prompt, char minimum, char maximum, bool enforceUpperCase)
{
    cout << prompt;
    
    char input;
    char minimumLower;
    char maximumLower;
    char minimumUpper;
    char maximumUpper;
    
    if (minimum >= 'a' && minimum <= 'z')
    {
        minimumLower = minimum;
        minimumUpper = toupper(minimum);
    }
    else if (minimum >= 'A' && minimum <= 'Z')
    {
        minimumLower = tolower(minimum);
        minimumUpper = minimum;
    }
    else
    {
        throw logic_error("minimum must be a valid letter between a-z or A-Z.");
    }
    
    if (maximum >= 'a' && maximum <= 'z')
    {
        maximumLower = maximum;
        maximumUpper = toupper(maximum);
    }
    else if (maximum >= 'A' && maximum <= 'Z')
    {
        maximumLower = tolower(maximum);
        maximumUpper = maximum;
    }
    else
    {
        throw logic_error("maximum must be a valid letter between a-z or A-Z.");
    }
    
    while (true)
    {
        cin >> input;
        
        if ((input >= minimumLower && input <= maximumLower) || (input >= minimumUpper && input <= maximumUpper))
        {
            if (enforceUpperCase && (input >= minimumLower && input <= maximumLower))
            {
                // Convert the lower case input to upper case before returning.
                // xx0x xxxx = 1101 1111 = 0xdf
                char mask = 0xdf;
                input &= mask;
            }
            return input;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Please enter a letter between " << minimumLower << " and " << maximumLower << ": ";
    }
}

void ConsoleManager::promptPause ()
{
    cout << "Press Enter to continue...";
    
    string temp;
    getline(cin, temp);
}
