//
//  ConsoleManager.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/25/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "ConsoleManager.h"

#include <stdexcept>
#include <sstream>

using namespace std;

bool ConsoleManager::promptYesOrNo (WINDOW * win, const std::string & prompt, chtype color, chtype errorColor, bool center, bool errorCenter, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    int currentY;
    int currentX;
    getyx(win, currentY, currentX);
    
    int maxX;
    maxX = getmaxx(win);
    
    int width = maxX - currentX;
    
    int errorY = currentY + 1;
    int errorX = currentX;
    
    return promptYesOrNo(win, currentY, currentX, width, errorY, errorX, width, prompt, color, errorColor, center, errorCenter, fillSpace);
}

bool ConsoleManager::promptYesOrNo (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, chtype color, chtype errorColor, bool center, bool errorCenter, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    echo();
    nodelay(win, false);
    
    while (true)
    {
        printMessage(win, y, x, width, prompt, color, center, fillSpace);
        
        char input = static_cast<char>(getch());
        clrtoeol();
        
        if (input == 'y' || input == 'Y')
        {
            noecho();
            nodelay(win, true);
            
            return true;
        }
        else if (input == 'n' || input == 'N')
        {
            noecho();
            nodelay(win, true);
            
            return false;
        }
        else
        {
            stringstream ss;
            ss << "Please enter y or n.";
            printMessage(win, errorY, errorX, errorWidth, ss.str(), errorColor, errorCenter, fillSpace);
        }
    }
}

int ConsoleManager::promptNumber (WINDOW * win, const std::string & prompt, int minimum, int maximum, chtype color, chtype errorColor, bool center, bool errorCenter, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    int currentY;
    int currentX;
    getyx(win, currentY, currentX);
    
    int maxX;
    maxX = getmaxx(win);
    
    int width = maxX - currentX;
    
    int errorY = currentY + 1;
    int errorX = currentX;
    
    return promptNumber(win, currentY, currentX, width, errorY, errorX, width, prompt, minimum, maximum, color, errorColor, center, errorCenter, fillSpace);
}

int ConsoleManager::promptNumber (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int minimum, int maximum, chtype color, chtype errorColor, bool center, bool errorCenter, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    echo();
    nodelay(win, false);
    
    const int BUFFER_CHAR_COUNT = 10;
    while (true)
    {
        printMessage(win, y, x, width, prompt, color, center);
        
        char buffer[BUFFER_CHAR_COUNT + 1];
        if (wgetnstr(win, buffer, BUFFER_CHAR_COUNT) == OK)
        {
            int input = stoi(buffer);
            
            if (input >= minimum && input <= maximum)
            {
                noecho();
                nodelay(win, true);
                
                return input;
            }
        }

        stringstream ss;
        ss << "Please enter a number between " << minimum << " and " << maximum << ".";
        printMessage(win, errorY, errorX, errorWidth, ss.str(), errorColor, errorCenter, fillSpace);
    }
}

char ConsoleManager::promptLetter (WINDOW * win, const std::string & prompt, char minimum, char maximum, chtype color, chtype errorColor, bool center, bool errorCenter, bool fillSpace, bool enforceUpperCase)
{
    if (!win)
    {
        win = stdscr;
    }
    
    int currentY;
    int currentX;
    getyx(win, currentY, currentX);
    
    int maxX;
    maxX = getmaxx(win);
    
    int width = maxX - currentX;
    
    int errorY = currentY + 1;
    int errorX = currentX;
    
    return promptLetter(win, currentY, currentX, width, errorY, errorX, width, prompt, minimum, maximum, color, errorColor, center, errorCenter, fillSpace, enforceUpperCase);
}

char ConsoleManager::promptLetter (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, char minimum, char maximum, chtype color, chtype errorColor, bool center, bool errorCenter, bool fillSpace, bool enforceUpperCase)
{
    if (!win)
    {
        win = stdscr;
    }
    
    char minimumLower;
    char minimumUpper;
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
    
    char maximumLower;
    char maximumUpper;
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
    
    echo();
    nodelay(win, false);
    
    while (true)
    {
        printMessage(win, y, x, width, prompt, color, center, fillSpace);
        
        char input = static_cast<char>(getch());
        clrtoeol();
        
        if ((input >= minimumLower && input <= maximumLower) || (input >= minimumUpper && input <= maximumUpper))
        {
            if (enforceUpperCase && (input >= minimumLower && input <= maximumLower))
            {
                // Convert the lower case input to upper case before returning.
                // xx0x xxxx = 1101 1111 = 0xdf
                char mask = 0xdf;
                input &= mask;
            }
            
            noecho();
            nodelay(win, true);
            
            return input;
        }
        
        stringstream ss;
        ss << "Please enter a letter between " << minimumLower << " and " << maximumLower << ".";
        printMessage(win, errorY, errorX, errorWidth, ss.str(), errorColor, errorCenter, fillSpace);
    }
}

void ConsoleManager::promptPause (WINDOW * win, const std::string & prompt, chtype color, bool center, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    int currentY;
    int currentX;
    getyx(win, currentY, currentX);
    
    int maxX;
    maxX = getmaxx(win);
    
    int width = maxX - currentX;
    
    promptPause(win, currentY, currentX, width, prompt, color, center, fillSpace);
}

void ConsoleManager::promptPause (WINDOW * win, int y, int x, int width, const std::string & prompt, chtype color, bool center, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    printMessage(win, y, x, width, prompt, color, center, fillSpace);
    
    getch();
}

void ConsoleManager::printMessage (WINDOW * win, const std::string & msg, chtype color, bool center, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }

    int currentY;
    int currentX;
    getyx(win, currentY, currentX);
    
    int maxX = getmaxx(win);
    
    int width = maxX - currentX;
    
    printMessage(win, currentY, currentX, width, msg, color, center, fillSpace);
}

void ConsoleManager::printMessage (WINDOW * win, int y, int x, int width, const std::string & msg, chtype color, bool center, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    int messageX = x;
    if (center)
    {
        messageX += (width - msg.length())/ 2;
    }
    
    wattron(win, color);
    
    if (fillSpace)
    {
        wmove(win, y, x);
        for (int i = x; i < messageX; ++i)
        {
            waddch(win, ' ');
        }
    }
    
    mvwprintw(win, y, messageX, "%s", msg.c_str());
    
    if (fillSpace)
    {
        int currentX = getcurx(win);
        for (int i = currentX; i < x + width; ++i)
        {
            waddch(win, ' ');
        }
    }
    
    wattroff(win, color);
}

void ConsoleManager::drawBox (WINDOW * win, int y, int x, int width, int height, chtype color)
{
    if (!win)
    {
        win = stdscr;
    }
    
    wattron(win, color);
    
    mvhline(y, x, ' ', width);
    mvhline(y + height - 1, x, ' ', width);
    mvvline(y + 1, x, ' ', height - 2);
    mvvline(y + 1, x + width - 1, ' ', height - 2);
    
    wattroff(win, color);
}
