//
//  ExitWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "ExitWindow.h"

#include "../submodules/TUCUT/Curses/GameManager.h"
#include "../submodules/TUCUT/Log/LogManager.h"

ExitWindow::ExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, clientForeColor, clientBackColor, border)
{ }

void ExitWindow::initialize ()
{
    Window::initialize();
}

std::shared_ptr<ExitWindow> ExitWindow::createSharedExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
{
    auto result = std::shared_ptr<ExitWindow>(new ExitWindow(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, border));
    
    result->initialize();
    
    return result;
}

std::shared_ptr<ExitWindow> ExitWindow::getSharedExitWindow ()
{
    return std::static_pointer_cast<ExitWindow>(shared_from_this());
}

bool ExitWindow::onKeyPress (TUCUT::Curses::GameManager * gm, int key)
{
    switch (key)
    {
    case KEY_DOWN:
        TUCUTLOG(Info, "Down key pressed from exit window.");
        break;
    case KEY_UP:
        break;
    case 10: // Enter
        break;
    case KEY_F(1):
        gm->exit();
        break;
    default:
        if (parent())
        {
            return parent()->onKeyPress(gm, key);
        }
        return false;
    }
    
    return true;
}

void ExitWindow::onMouseEvent (TUCUT::Curses::GameManager * gm, short id, int y, int x, mmask_t buttonState)
{
    if (buttonState & BUTTON1_CLICKED)
    {
        TUCUTLOG(Info, "Mouse button 1 clicked at y=" << y << " x=" << x);
    }
    else if (buttonState & BUTTON2_CLICKED)
    {
        TUCUTLOG(Info, "Mouse button 2 clicked at y=" << y << " x=" << x);
    }
    else if (buttonState & BUTTON3_CLICKED)
    {
        TUCUTLOG(Info, "Mouse button 3 clicked at y=" << y << " x=" << x);
    }
}

void ExitWindow::onDrawClient () const
{
    
}
