//
//  SplashWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef SplashWindow_h
#define SplashWindow_h

#include "Window.h"

class SplashWindow : public Window
{
public:
    SplashWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    void processInput (GameManager * gm) override;
    
    void onDrawClient () const override;
};

#endif /* SplashWindow_h */
