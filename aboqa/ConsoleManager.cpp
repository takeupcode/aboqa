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
#include "CursesUtil.h"
#include "Window.h"

using namespace std;

bool ConsoleManager::checkBounds (const Window & win, int y, int x)
{
    int maxY;
    int maxX;
    CursesUtil::getScreenMaxYX(maxY, maxX);
    
    // Check if the entire request falls outside the screen bounds.
    if (y + win.clientY() > maxY || x + win.clientX() > maxX)
    {
        return false;
    }
    
    // Check if the entire request falls outside the window bounds.
    if (y >= win.clientHeight() || x >= win.clientWidth())
    {
        return false;
    }
    
    return true;
}

bool ConsoleManager::promptYesOrNo (const Window & win, const std::string & prompt, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace)
{
    WINDOW * cursesWin = win.cursesWindow();
    
    int currentY;
    int currentX;
    getyx(cursesWin, currentY, currentX);
    
    int width = win.clientWidth() - currentX;
    
    int errorY = currentY + 1;
    int errorX = currentX;
    
    return promptYesOrNo(win, currentY, currentX, width, errorY, errorX, width, prompt, foreColor, backColor, errorForeColor, errorBackColor, center, errorCenter, fillSpace);
}

bool ConsoleManager::promptYesOrNo (const Window & win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace)
{
    WINDOW * cursesWin = win.cursesWindow();
    
    echo();
    nodelay(cursesWin, false);
    
    while (true)
    {
        printMessage(win, y, x, width, prompt, foreColor, backColor, center, fillSpace);
        wrefresh(cursesWin);
        
        char input = static_cast<char>(wgetch(cursesWin));
        clrtoeol();
        
        if (input == 'y' || input == 'Y')
        {
            noecho();
            nodelay(cursesWin, true);
            
            return true;
        }
        else if (input == 'n' || input == 'N')
        {
            noecho();
            nodelay(cursesWin, true);
            
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

int ConsoleManager::promptNumber (const Window & win, const std::string & prompt, int minimum, int maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace)
{
    WINDOW * cursesWin = win.cursesWindow();
    
    int currentY;
    int currentX;
    getyx(cursesWin, currentY, currentX);
    
    int width = win.clientWidth() - currentX;
    
    int errorY = currentY + 1;
    int errorX = currentX;
    
    return promptNumber(win, currentY, currentX, width, errorY, errorX, width, prompt, minimum, maximum, foreColor, backColor, errorForeColor, errorBackColor, center, errorCenter, fillSpace);
}

int ConsoleManager::promptNumber (const Window & win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int minimum, int maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace)
{
    WINDOW * cursesWin = win.cursesWindow();
    
    echo();
    nodelay(cursesWin, false);
    
    const int BUFFER_CHAR_COUNT = 10;
    while (true)
    {
        printMessage(win, y, x, width, prompt, foreColor, backColor, center);
        wrefresh(cursesWin);
        
        char buffer[BUFFER_CHAR_COUNT + 1];
        if (wgetnstr(cursesWin, buffer, BUFFER_CHAR_COUNT) == OK)
        {
            int input = stoi(buffer);
            
            if (input >= minimum && input <= maximum)
            {
                noecho();
                nodelay(cursesWin, true);
                
                return input;
            }
        }

        stringstream ss;
        ss << "Please enter a number between " << minimum << " and " << maximum << ".";
        printMessage(win, errorY, errorX, errorWidth, ss.str(), errorForeColor, errorBackColor, errorCenter, fillSpace);
    }
}

char ConsoleManager::promptLetter (const Window & win, const std::string & prompt, char minimum, char maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace, bool enforceUpperCase)
{
    WINDOW * cursesWin = win.cursesWindow();
    
    int currentY;
    int currentX;
    getyx(cursesWin, currentY, currentX);
    
    int width = win.clientWidth() - currentX;
    
    int errorY = currentY + 1;
    int errorX = currentX;
    
    return promptLetter(win, currentY, currentX, width, errorY, errorX, width, prompt, minimum, maximum, foreColor, backColor, errorForeColor, errorBackColor, center, errorCenter, fillSpace, enforceUpperCase);
}

char ConsoleManager::promptLetter (const Window & win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, char minimum, char maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center, bool errorCenter, bool fillSpace, bool enforceUpperCase)
{
    WINDOW * cursesWin = win.cursesWindow();
    
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
    nodelay(cursesWin, false);
    
    while (true)
    {
        printMessage(win, y, x, width, prompt, foreColor, backColor, center, fillSpace);
        wrefresh(cursesWin);
        
        char input = static_cast<char>(wgetch(cursesWin));
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
            nodelay(cursesWin, true);
            
            return input;
        }
        
        stringstream ss;
        ss << "Please enter a letter between " << minimumLower << " and " << maximumLower << ".";
        printMessage(win, errorY, errorX, errorWidth, ss.str(), errorForeColor, errorBackColor, errorCenter, fillSpace);
    }
}

void ConsoleManager::promptPause (const Window & win, const std::string & prompt, int foreColor, int backColor, bool center, bool fillSpace)
{
    WINDOW * cursesWin = win.cursesWindow();
    
    int currentY;
    int currentX;
    getyx(cursesWin, currentY, currentX);
    
    int width = win.clientWidth() - currentX;
    
    promptPause(win, currentY, currentX, width, prompt, foreColor, backColor, center, fillSpace);
}

void ConsoleManager::promptPause (const Window & win, int y, int x, int width, const std::string & prompt, int foreColor, int backColor, bool center, bool fillSpace)
{
    WINDOW * cursesWin = win.cursesWindow();
    
    printMessage(win, y, x, width, prompt, foreColor, backColor, center, fillSpace);
    wrefresh(cursesWin);
    
    wgetch(cursesWin);
}

void ConsoleManager::printMessage (const Window & win, const std::string & msg, int foreColor, int backColor, bool center, bool fillSpace)
{
    WINDOW * cursesWin = win.cursesWindow();
    
    int currentY;
    int currentX;
    getyx(cursesWin, currentY, currentX);
    
    int width = win.clientWidth() - currentX;
    
    printMessage(win, currentY, currentX, width, msg, foreColor, backColor, center, fillSpace);
}

void ConsoleManager::printMessage (const Window & win, int y, int x, int width, const std::string & msg, int foreColor, int backColor, bool center, bool fillSpace)
{
    if (!checkBounds(win, y, x))
    {
        return;
    }
    
    WINDOW * cursesWin = win.cursesWindow();
    
    int messageX = x;
    if (center)
    {
        int delta = static_cast<int>(width - msg.length()) / 2;
        if (delta > 0)
        {
            messageX += delta;
        }
    }
    
    int i = Colors::colorPairIndex(foreColor, backColor);
    wattrset(cursesWin, COLOR_PAIR(i));
    
    if (fillSpace)
    {
        wmove(cursesWin, y, x);
        for (int i = x; i < messageX; ++i)
        {
            if (!checkBounds(win, y, i))
            {
                return;
            }
            waddch(cursesWin, ' ');
        }
    }
    
    printMessage(win, y, messageX, msg);
    
    if (fillSpace)
    {
        int currentY = getcury(cursesWin);
        if (currentY != y)
        {
            return;
        }
        int currentX = getcurx(cursesWin);
        for (int i = currentX; i < x + width; ++i)
        {
            if (!checkBounds(win, y, i))
            {
                return;
            }
            waddch(cursesWin, ' ');
        }
    }
}

void ConsoleManager::printMessage (const Window & win, int y, int x, const std::string & msg)
{
    if (!checkBounds(win, y, x))
    {
        return;
    }
    
    WINDOW * cursesWin = win.cursesWindow();
    
    if (wmove(cursesWin, y, x) == ERR)
    {
        return;
    }
    
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
                if (!checkBounds(win, y, x))
                {
                    return;
                }
                mvwaddch(cursesWin, y, x, c);
                ++x;
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
                if (!checkBounds(win, y, x))
                {
                    return;
                }
                mvwaddch(cursesWin, y, x, '&');
                ++x;

                if (!checkBounds(win, y, x))
                {
                    return;
                }
                waddch(cursesWin, c);
                ++x;
                
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
                if (!checkBounds(win, y, x))
                {
                    return;
                }
                mvwaddch(cursesWin, y, x, '&');
                ++x;

                if (!checkBounds(win, y, x))
                {
                    return;
                }
                waddch(cursesWin, firstChar);
                ++x;

                if (!checkBounds(win, y, x))
                {
                    return;
                }
                waddch(cursesWin, c);
                ++x;
                
                state = PrintState::normal;
            }
            break;
            
        case PrintState::needEnd:
            if (c == ';')
            {
                int i = Colors::colorPairIndex(foreColor, backColor);
                wattrset(cursesWin, COLOR_PAIR(i));
            }
            else
            {
                if (!checkBounds(win, y, x))
                {
                    return;
                }
                mvwaddch(cursesWin, y, x, '&');
                ++x;

                if (!checkBounds(win, y, x))
                {
                    return;
                }
                waddch(cursesWin, firstChar);
                ++x;

                if (!checkBounds(win, y, x))
                {
                    return;
                }
                waddch(cursesWin, secondChar);
                ++x;

                if (!checkBounds(win, y, x))
                {
                    return;
                }
                waddch(cursesWin, c);
                ++x;
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
        if (!checkBounds(win, y, x))
        {
            return;
        }
        mvwaddch(cursesWin, y, x, '&');
        ++x;
        break;
            
    case PrintState::needBackColor:
        if (!checkBounds(win, y, x))
        {
            return;
        }
        mvwaddch(cursesWin, y, x, '&');
        ++x;

        if (!checkBounds(win, y, x))
        {
            return;
        }
        waddch(cursesWin, firstChar);
        ++x;
        break;
        
    case PrintState::needEnd:
        if (!checkBounds(win, y, x))
        {
            return;
        }
        mvwaddch(cursesWin, y, x, '&');
        ++x;

        if (!checkBounds(win, y, x))
        {
            return;
        }
        waddch(cursesWin, firstChar);
        ++x;

        if (!checkBounds(win, y, x))
        {
            return;
        }
        waddch(cursesWin, secondChar);
        ++x;
        break;
    }
}

void ConsoleManager::drawBox (const Window & win, int y, int x, int height, int width, int foreColor, int backColor)
{
    if (!checkBounds(win, y, x))
    {
        return;
    }
    
    WINDOW * cursesWin = win.cursesWindow();
    
    int i = Colors::colorPairIndex(foreColor, backColor);
    wattrset(cursesWin, COLOR_PAIR(i));
    
    mvwaddch(cursesWin, y, x, ACS_ULCORNER);
    mvwaddch(cursesWin, y, x + width - 1, ACS_URCORNER);
    mvwaddch(cursesWin, y + height - 1, x, ACS_LLCORNER);
    mvwaddch(cursesWin, y + height - 1, x + width - 1, ACS_LRCORNER);
    mvwhline(cursesWin, y, x + 1, ACS_HLINE, width - 2);
    mvwhline(cursesWin, y + height - 1, x + 1, ACS_HLINE, width - 2);
    mvwvline(cursesWin, y + 1, x, ACS_VLINE, height - 2);
    mvwvline(cursesWin, y + 1, x + width - 1, ACS_VLINE, height - 2);
}

void ConsoleManager::fillRect (const Window & win, int y, int x, int height, int width, int foreColor, int backColor)
{
    if (!checkBounds(win, y, x))
    {
        return;
    }
    
    WINDOW * cursesWin = win.cursesWindow();
    
    int i = Colors::colorPairIndex(foreColor, backColor);
    wattrset(cursesWin, COLOR_PAIR(i));
    
    for (int i = 0; i < height; ++i)
    {
        if (!checkBounds(win, y + i, x))
        {
            return;
        }
        mvwhline(cursesWin, y + i, x, ' ', width);
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
