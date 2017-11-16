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

bool ConsoleManager::getMaxWinBounds (const Window & win, int & y, int & x)
{
    // Figure out if the screen or the window has the smallest max y and x.
    // Whichever is smallest is the max y and x that will be visible.
    // Translate the max y and x back into window client coordinates.
    // And return false if the window is off the screen.
    int maxScreenY;
    int maxScreenX;
    CursesUtil::getScreenMaxYX(maxScreenY, maxScreenX);
    
    if (win.clientY() > maxScreenY || win.clientX() > maxScreenX)
    {
        return false;
    }
    
    int maxWinY = win.clientY() + win.clientHeight() - 1;
    int maxWinX = win.clientX() + win.clientWidth() - 1;
    
    int resultY = (maxWinY <= maxScreenY) ? maxWinY : maxScreenY;
    int resultX = (maxWinX <= maxScreenX) ? maxWinX : maxScreenX;
    
    y = resultY - win.clientY();
    x = resultX - win.clientX();
    
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
    int maxWinY;
    int maxWinX;
    if (!getMaxWinBounds(win, maxWinY, maxWinX))
    {
        return;
    }
    if (y > maxWinY || x > maxWinX)
    {
        return;
    }
    
    WINDOW * cursesWin = win.cursesWindow();
    
    int messageX = x;
    if (center)
    {
        int margin = static_cast<int>(width - msg.length()) / 2;
        if (margin > 0)
        {
            messageX += margin;
        }
    }
    
    int i = Colors::colorPairIndex(foreColor, backColor);
    wattrset(cursesWin, COLOR_PAIR(i));
    
    if (fillSpace)
    {
        wmove(cursesWin, y, x);
        for (int i = x; i < messageX; ++i)
        {
            if (i > maxWinX)
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
            if (i > maxWinX)
            {
                return;
            }
            waddch(cursesWin, ' ');
        }
    }
}

void ConsoleManager::printMessage (const Window & win, int y, int x, const std::string & msg)
{
    int maxWinY;
    int maxWinX;
    if (!getMaxWinBounds(win, maxWinY, maxWinX))
    {
        return;
    }
    if (y > maxWinY || x > maxWinX)
    {
        return;
    }
    
    WINDOW * cursesWin = win.cursesWindow();
    
    if (wmove(cursesWin, y, x) == ERR)
    {
        return;
    }
    
    PrintState state = PrintState::normal;
    
    bool skipColorCheck = false;
    int foreColor = 0;
    int backColor = 0;
    
    int lastIndex = static_cast<int>(msg.length()) - 1;
    for (int index = 0; index <= lastIndex; ++index)
    {
        char c = msg[index];
        
        if (c == '\t')
        {
            c = ' ';
        }
        else if (c == '\n')
        {
            // This method prints at most a single line.
            break;
        }
        
        switch (state)
        {
        case PrintState::normal:
            if (index != lastIndex && !skipColorCheck && c == '&')
            {
                state = PrintState::needForeColor;
            }
            else
            {
                if (x > maxWinX)
                {
                    return;
                }
                mvwaddch(cursesWin, y, x, c);
                ++x;
            }
            skipColorCheck = false;
            break;
            
        case PrintState::needForeColor:
            if (index != lastIndex && charToColor(c, foreColor))
            {
                state = PrintState::needBackColor;
            }
            else
            {
                index -= 2;
                skipColorCheck = true;
                state = PrintState::normal;
            }
            break;
            
        case PrintState::needBackColor:
            if (index != lastIndex && charToColor(c, backColor))
            {
                state = PrintState::needEndOfColor;
            }
            else
            {
                index -= 3;
                skipColorCheck = true;
                state = PrintState::normal;
            }
            break;
            
        case PrintState::needEndOfColor:
            if (c == ';')
            {
                int i = Colors::colorPairIndex(foreColor, backColor);
                wattrset(cursesWin, COLOR_PAIR(i));
            }
            else
            {
                index -= 4;
                skipColorCheck = true;
                state = PrintState::normal;
            }
            state = PrintState::normal;
            break;
        }
    }
}

void ConsoleManager::drawBox (const Window & win, int y, int x, int height, int width, int foreColor, int backColor)
{
    int maxWinY;
    int maxWinX;
    if (!getMaxWinBounds(win, maxWinY, maxWinX))
    {
        return;
    }
    if (y > maxWinY || x > maxWinX)
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
    int maxWinY;
    int maxWinX;
    if (!getMaxWinBounds(win, maxWinY, maxWinX))
    {
        return;
    }
    if (y > maxWinY || x > maxWinX)
    {
        return;
    }
    
    WINDOW * cursesWin = win.cursesWindow();
    
    int i = Colors::colorPairIndex(foreColor, backColor);
    wattrset(cursesWin, COLOR_PAIR(i));
    
    for (int i = 0; i < height; ++i)
    {
        if (y + i > maxWinY)
        {
            return;
        }
        mvwhline(cursesWin, y + i, x, ' ', width);
    }
}

void ConsoleManager::LineBreakpoint::setDefaultValues ()
{
    beginIndex = 0;
    endIndex = 0;
}

std::vector<ConsoleManager::LineBreakpoint> ConsoleManager::calculateLineBreakpoints (const std::string & text, int width)
{
    std::vector<ConsoleManager::LineBreakpoint> result;

    PrintState state = PrintState::normal;
    
    int x = 0;
    const int maxX = width - 1;
    
    int lastSpaceIndex = 0;
    
    LineBreakpoint lineBreakpoint;
    lineBreakpoint.setDefaultValues();
    
    bool skipColorCheck = false;
    int foreColor = 0;
    int backColor = 0;
    
    auto setLineBreakpoint = [&lineBreakpoint, &result] (int index)
    {
        lineBreakpoint.endIndex = index;
        
        result.push_back(lineBreakpoint);
        
        lineBreakpoint.setDefaultValues();
        
        lineBreakpoint.beginIndex = index + 1;
    };
    
    int lastIndex = static_cast<int>(text.length()) - 1;
    for (int index = 0; index <= lastIndex; ++index)
    {
        char c = text[index];
        switch (state)
        {
        case PrintState::normal:
            if (index != lastIndex && !skipColorCheck && c == '&')
            {
                state = PrintState::needForeColor;
            }
            else if (c == '\n')
            {
                setLineBreakpoint(index);
                x = 0;
            }
            else
            {
                if (c == ' ' || c == '\t')
                {
                    lastSpaceIndex = index;
                }
                if (x > maxX)
                {
                    lineBreakpoint.endIndex = index - 1;
                    
                    if (lastSpaceIndex > lineBreakpoint.beginIndex)
                    {
                        // If we found a space since beginning this
                        // line, then go back to that space.
                        index = lastSpaceIndex;
                    }
                    else
                    {
                        // Go back one position.
                        --index;
                    }
                    setLineBreakpoint(index);
                    x = 0;
                }
                else
                {
                    ++x;
                }
            }
            skipColorCheck = false;
            break;
            
        case PrintState::needForeColor:
            if (index != lastIndex && charToColor(c, foreColor))
            {
                state = PrintState::needBackColor;
            }
            else
            {
                index -= 2;
                skipColorCheck = true;
                state = PrintState::normal;
            }
            break;
            
        case PrintState::needBackColor:
            if (index != lastIndex && charToColor(c, backColor))
            {
                state = PrintState::needEndOfColor;
            }
            else
            {
                index -= 3;
                skipColorCheck = true;
                state = PrintState::normal;
            }
            break;
            
        case PrintState::needEndOfColor:
            if (c != ';')
            {
                index -= 4;
                skipColorCheck = true;
            }
            state = PrintState::normal;
            break;
        }
    }
    
    return result;
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
