//
//  ConsoleManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/25/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef ConsoleManager_h
#define ConsoleManager_h

#include <string>
#include <curses.h>

class Window;

class ConsoleManager
{
    enum class PrintState
    {
        normal,
        needForeColor,
        needBackColor,
        needEnd
    };
    
public:
    static bool promptYesOrNo (const Window & win, const std::string & prompt, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false);
    
    static bool promptYesOrNo (const Window & win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false);
    
    static int promptNumber (const Window & win, const std::string & prompt, int minimum, int maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false);
    
    static int promptNumber (const Window & win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int minimum, int maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false);
    
    static char promptLetter (const Window & win, const std::string & prompt, char minimum, char maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false, bool enforceUpperCase = false);
    
    static char promptLetter (const Window & win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, char minimum, char maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false, bool enforceUpperCase = false);
    
    static void promptPause (const Window & win, const std::string & prompt, int foreColor, int backColor, bool center = false, bool fillSpace = false);
    
    static void promptPause (const Window & win, int y, int x, int width, const std::string & prompt, int foreColor, int backColor, bool center = false, bool fillSpace = false);
    
    static void printMessage (const Window & win, const std::string & msg, int foreColor, int backColor, bool center = false, bool fillSpace = false);
    
    static void printMessage (const Window & win, int y, int x, int width, const std::string & msg, int foreColor, int backColor, bool center = false, bool fillSpace = false);
    
    static void printMessage (const Window & win, int y, int x, const std::string & msg);
    
    static void drawBox (const Window & win, int y, int x, int height, int width, int foreColor, int backColor);
    
    static void fillRect (const Window & win, int y, int x, int height, int width, int foreColor, int backColor);
    
private:
    static bool charToColor (char c, int & color);
    
    static bool checkBounds (const Window & win, int y, int x);
};

#endif /* ConsoleManager_h */
