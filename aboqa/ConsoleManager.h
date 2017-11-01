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
public:
    static bool promptYesOrNo (WINDOW * win, const std::string & prompt, chtype color, chtype errorColor, bool center = false, bool errorCenter = false, bool fillSpace = true);
    
    static bool promptYesOrNo (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, chtype color, chtype errorColor, bool center = false, bool errorCenter = false, bool fillSpace = true);
    
    static int promptNumber (WINDOW * win, const std::string & prompt, int minimum, int maximum, chtype color, chtype errorColor, bool center = false, bool errorCenter = false, bool fillSpace = true);
    
    static int promptNumber (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, int minimum, int maximum, chtype color, chtype errorColor, bool center = false, bool errorCenter = false, bool fillSpace = true);
    
    static char promptLetter (WINDOW * win, const std::string & prompt, char minimum, char maximum, chtype color, chtype errorColor, bool center = false, bool errorCenter = false, bool fillSpace = true, bool enforceUpperCase = false);
    
    static char promptLetter (WINDOW * win, int y, int x, int width, int errorY, int errorX, int errorWidth, const std::string & prompt, char minimum, char maximum, chtype color, chtype errorColor, bool center = false, bool errorCenter = false, bool fillSpace = true, bool enforceUpperCase = false);
    
    static void promptPause (WINDOW * win, const std::string & prompt, chtype color, bool center = false, bool fillSpace = false);
    
    static void promptPause (WINDOW * win, int y, int x, int width, const std::string & prompt, chtype color, bool center = false, bool fillSpace = false);
    
    static void printMessage (WINDOW * win, const std::string & msg, chtype color, bool center = false, bool fillSpace = false);
    
    static void printMessage (WINDOW * win, int y, int x, int width, const std::string & msg, chtype color, bool center = false, bool fillSpace = false);
    
    static void drawBox (WINDOW * win, int y, int x, int width, int height, chtype color);
};

#endif /* ConsoleManager_h */
