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
    static bool promptYesOrNo (WINDOW * win, const std::string & prompt, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false);
    
    static bool promptYesOrNo (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false);
    
    static int promptNumber (WINDOW * win, const std::string & prompt, int minimum, int maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false);
    
    static int promptNumber (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int minimum, int maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false);
    
    static char promptLetter (WINDOW * win, const std::string & prompt, char minimum, char maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false, bool enforceUpperCase = false);
    
    static char promptLetter (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, char minimum, char maximum, int foreColor, int backColor, int errorForeColor, int errorBackColor, bool center = false, bool errorCenter = false, bool fillSpace = false, bool enforceUpperCase = false);
    
    static void promptPause (WINDOW * win, const std::string & prompt, int foreColor, int backColor, bool center = false, bool fillSpace = false);
    
    static void promptPause (WINDOW * win, int y, int x, int width, const std::string & prompt, int foreColor, int backColor, bool center = false, bool fillSpace = false);
    
    static void printMessage (WINDOW * win, const std::string & msg, int foreColor, int backColor, bool center = false, bool fillSpace = false);
    
    static void printMessage (WINDOW * win, int y, int x, int width, const std::string & msg, int foreColor, int backColor, bool center = false, bool fillSpace = false);
    
    static void printMessage (WINDOW * win, int y, int x, const std::string & msg);
    
    static void drawBox (WINDOW * win, int y, int x, int width, int height, int foreColor, int backColor);
    
    static void fillRect (WINDOW * win, int y, int x, int width, int height, int foreColor, int backColor);
    
private:
    static bool charToColor (char c, int & color);

};

#endif /* ConsoleManager_h */
