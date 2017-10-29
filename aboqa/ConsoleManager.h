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

class ConsoleManager
{
public:
    static bool promptYesOrNo (const std::string & prompt);
    
    static int promptNumber (const std::string & prompt, int minimum, int maximum);
    
    static char promptLetter (const std::string & prompt, char minimum, char maximum, bool enforceUpperCase = false);
    
    static void promptPause ();
};

#endif /* ConsoleManager_h */
