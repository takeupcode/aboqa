//
//  SplashWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "SplashWindow.h"

#include "Colors.h"
#include "Button.h"
#include "GameManager.h"
#include "LogManager.h"

SplashWindow::SplashWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, border)
{
    addControl(std::unique_ptr<Window>(new Button("okButton", "Ok", height - 1, width - 12, 1, 10, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_RED)));
}

void SplashWindow::onKeyPress (GameManager * gm, int key) const
{
    switch(key)
    {
    case KEY_DOWN:
        ABOQALOG(Info, "Down key pressed from splash window.");
        break;
    case KEY_UP:
        break;
    case 10: /* Enter */
        break;
    case KEY_F(1):
        gm->selectNextWindow("main");
        break;
    }
}

void SplashWindow::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const
{
    if (buttonState & BUTTON1_CLICKED)
    {
        ABOQALOG(Info, "Mouse button 1 clicked at y=" << y << " x=" << x);
    }
    else if (buttonState & BUTTON2_CLICKED)
    {
        ABOQALOG(Info, "Mouse button 2 clicked at y=" << y << " x=" << x);
    }
    else if (buttonState & BUTTON3_CLICKED)
    {
        ABOQALOG(Info, "Mouse button 3 clicked at y=" << y << " x=" << x);
    }
}

void SplashWindow::onDrawClient () const
{
    
}
