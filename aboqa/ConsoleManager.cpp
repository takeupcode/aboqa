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
#include <stdexcept>

#include "Colors.h"

using namespace std;

bool ConsoleManager::promptYesOrNo (WINDOW * win, const std::string & prompt, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace)
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
    
    return promptYesOrNo(win, currentY, currentX, width, errorY, errorX, width, prompt, foreColor, backColor, errorForeColor, errorBackColor, center, errorCenter, fillSpace);
}

bool ConsoleManager::promptYesOrNo (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    echo();
    nodelay(win, false);
    
    while (true)
    {
        printMessage(win, y, x, width, prompt, foreColor, backColor, center, fillSpace);
        wrefresh(win);
        
        char input = static_cast<char>(wgetch(win));
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
            printMessage(win, errorY, errorX, errorWidth, ss.str(), errorForeColor, errorBackColor, errorCenter, fillSpace);
        }
    }
}

int ConsoleManager::promptNumber (WINDOW * win, const std::string & prompt, int minimum, int maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace)
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
    
    return promptNumber(win, currentY, currentX, width, errorY, errorX, width, prompt, minimum, maximum, foreColor, backColor, errorForeColor, errorBackColor, center, errorCenter, fillSpace);
}

int ConsoleManager::promptNumber (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int minimum, int maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace)
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
        printMessage(win, y, x, width, prompt, foreColor, backColor, center);
        wrefresh(win);
        
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
        printMessage(win, errorY, errorX, errorWidth, ss.str(), errorForeColor, errorBackColor, errorCenter, fillSpace);
    }
}

char ConsoleManager::promptLetter (WINDOW * win, const std::string & prompt, char minimum, char maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace, bool enforceUpperCase)
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
    
    return promptLetter(win, currentY, currentX, width, errorY, errorX, width, prompt, minimum, maximum, foreColor, backColor, errorForeColor, errorBackColor, center, errorCenter, fillSpace, enforceUpperCase);
}

char ConsoleManager::promptLetter (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, char minimum, char maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace, bool enforceUpperCase)
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
        printMessage(win, y, x, width, prompt, foreColor, backColor, center, fillSpace);
        wrefresh(win);
        
        char input = static_cast<char>(wgetch(win));
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
        printMessage(win, errorY, errorX, errorWidth, ss.str(), errorForeColor, errorBackColor, errorCenter, fillSpace);
    }
}

void ConsoleManager::promptPause (WINDOW * win, const std::string & prompt, int foreColor, int backColor, bool center, bool fillSpace)
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
    
    promptPause(win, currentY, currentX, width, prompt, foreColor, backColor, center, fillSpace);
}

void ConsoleManager::promptPause (WINDOW * win, int y, int x, int width, const std::string & prompt, int foreColor, int backColor, bool center, bool fillSpace)
{
    if (!win)
    {
        win = stdscr;
    }
    
    printMessage(win, y, x, width, prompt, foreColor, backColor, center, fillSpace);
    wrefresh(win);
    
    wgetch(win);
}

void ConsoleManager::printMessage (WINDOW * win, const std::string & msg, int foreColor, int backColor, bool center, bool fillSpace)
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
    
    printMessage(win, currentY, currentX, width, msg, foreColor, backColor, center, fillSpace);
}

void ConsoleManager::printMessage (WINDOW * win, int y, int x, int width, const std::string & msg, int foreColor, int backColor, bool center, bool fillSpace)
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
    
    int i = Colors::colorPairIndex(foreColor, backColor);
    wattrset(win, COLOR_PAIR(i));
    
    if (fillSpace)
    {
        wmove(win, y, x);
        for (int i = x; i < messageX; ++i)
        {
            waddch(win, ' ');
        }
    }
    
    printMessage(win, y, messageX, msg);
    
    if (fillSpace)
    {
        int currentX = getcurx(win);
        for (int i = currentX; i < x + width; ++i)
        {
            waddch(win, ' ');
        }
    }
}

void ConsoleManager::printMessage (WINDOW * win, int y, int x, const std::string & msg)
{
    if (!win)
    {
        win = stdscr;
    }
    
    wmove(win, y, x);
    
    PrintState state = PrintState::normal;
    int foreColor = 0;
    int backColor = 0;
    char firstChar = ' ';
    char secondChar = ' ';
    for (const char c : msg)
    {
        switch (state)
        {
        case PrintState::normal:
            if (c == '&')
            {
                state = PrintState::needForeColor;
            }
            else
            {
                waddch(win, c);
            }
            break;
            
        case PrintState::needForeColor:
            if (charToColor(c, foreColor))
            {
                firstChar = c;
                state = PrintState::needBackColor;
            }
            else
            {
                waddch(win, '&');
                waddch(win, c);
                state = PrintState::normal;
            }
            break;
            
        case PrintState::needBackColor:
            if (charToColor(c, backColor))
            {
                secondChar = c;
                state = PrintState::needEnd;
            }
            else
            {
                waddch(win, '&');
                waddch(win, firstChar);
                waddch(win, c);
                state = PrintState::normal;
            }
            break;
            
        case PrintState::needEnd:
            if (c == ';')
            {
                int i = Colors::colorPairIndex(foreColor, backColor);
                wattrset(win, COLOR_PAIR(i));
            }
            else
            {
                waddch(win, '&');
                waddch(win, firstChar);
                waddch(win, secondChar);
                waddch(win, c);
            }
            state = PrintState::normal;
            break;
        }
    }

    // Look at the state one more time to see if there was an incomplete color.
    switch (state)
    {
    case PrintState::normal:
        break;
        
    case PrintState::needForeColor:
        waddch(win, '&');
        break;
    case PrintState::needBackColor:
        waddch(win, '&');
        waddch(win, firstChar);
        break;
        
    case PrintState::needEnd:
        waddch(win, '&');
        waddch(win, firstChar);
        waddch(win, secondChar);
        break;
    }
}

void ConsoleManager::drawBox (WINDOW * win, int y, int x, int height, int width, int foreColor, int backColor)
{
    if (!win)
    {
        win = stdscr;
    }
    
    int i = Colors::colorPairIndex(foreColor, backColor);
    wattrset(win, COLOR_PAIR(i));
    
    mvwaddch(win, y, x, ACS_ULCORNER);
    mvwaddch(win, y, x + width - 1, ACS_URCORNER);
    mvwaddch(win, y + height - 1, x, ACS_LLCORNER);
    mvwaddch(win, y + height - 1, x + width - 1, ACS_LRCORNER);
    mvwhline(win, y, x + 1, ACS_HLINE, width - 2);
    mvwhline(win, y + height - 1, x + 1, ACS_HLINE, width - 2);
    mvwvline(win, y + 1, x, ACS_VLINE, height - 2);
    mvwvline(win, y + 1, x + width - 1, ACS_VLINE, height - 2);
}

void ConsoleManager::fillRect (WINDOW * win, int y, int x, int height, int width, int foreColor, int backColor)
{
    if (!win)
    {
        win = stdscr;
    }
    
    int i = Colors::colorPairIndex(foreColor, backColor);
    wattrset(win, COLOR_PAIR(i));
    
    for (int i = 0; i < height - 1; ++i)
    {
        mvwhline(win, y + i, x, ' ', width - 1);
    }
}

bool ConsoleManager::charToColor (char c, int & color)
{
    switch (c)
    {
    case 'k':
        color = COLOR_BLACK;
        break;
    case 'r':
        color = COLOR_RED;
        break;
    case 'g':
        color = COLOR_GREEN;
        break;
    case 'y':
        color = COLOR_YELLOW;
        break;
    case 'b':
        color = COLOR_BLUE;
        break;
    case 'm':
        color = COLOR_MAGENTA;
        break;
    case 'c':
        color = COLOR_CYAN;
        break;
    case 'w':
        color = COLOR_WHITE;
        break;
    default:
        if (!Colors::useBrightColors)
        {
            return false;
        }
            
        switch (c)
        {
        case 'K':
            color = COLOR_BLACK + Colors::basicColorCount;
            break;
        case 'R':
            color = COLOR_RED + Colors::basicColorCount;
            break;
        case 'G':
            color = COLOR_GREEN + Colors::basicColorCount;
            break;
        case 'Y':
            color = COLOR_YELLOW + Colors::basicColorCount;
            break;
        case 'B':
            color = COLOR_BLUE + Colors::basicColorCount;
            break;
        case 'M':
            color = COLOR_MAGENTA + Colors::basicColorCount;
            break;
        case 'C':
            color = COLOR_CYAN + Colors::basicColorCount;
            break;
        case 'W':
            color = COLOR_WHITE + Colors::basicColorCount;
            break;
        default:
            return false;
        }
    }

    return true;
}
