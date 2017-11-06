//
//  ExitWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "ExitWindow.h"

#include "GameManager.h"
#include "LogManager.h"

ExitWindow::ExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, border)
{ }

void ExitWindow::onKeyPress (GameManager * gm, int key) const
{
    switch(key)
    {
    case KEY_DOWN:
        ABOQALOG(Info, "Down key pressed from exit window.");
        break;
    case KEY_UP:
        break;
    case 10: /* Enter */
        break;
    case KEY_F(1):
        gm->exit();
        break;
    }
}

void ExitWindow::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const
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

void ExitWindow::onDrawClient () const
{
    
}
