//
//  Button.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "Button.h"

#include "ConsoleManager.h"
#include "GameManager.h"
#include "LogManager.h"

Button::Button (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int focusForeColor, int focusBackColor)
: Window(name, y, x, height, width, foreColor, backColor, foreColor, backColor, false, focusForeColor, focusBackColor), mText(text)
{
    setFillClientArea(false);
}

bool Button::onKeyPress (GameManager * gm, int key) const
{
    switch (key)
    {
    case 32: // Space
    case 10: // Enter
        handleClick();
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

void Button::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const
{
    if (buttonState & BUTTON1_CLICKED)
    {
        handleClick();
    }
}

void Button::onDrawClient () const
{
    int vertCenter = height() / 2;
    if (hasDirectFocus())
    {
        ConsoleManager::printMessage(*this, vertCenter, 0, width(), mText, focusForeColor(), focusBackColor(), true, true);
        mvwaddch(cursesWindow(), vertCenter, 0, '|');
        if (wantEnter())
        {
            waddch(cursesWindow(), '>');
        }
        mvwaddch(cursesWindow(), vertCenter, width() - 1, '|');
    }
    else
    {
        ConsoleManager::printMessage(*this, vertCenter, 0, width(), mText, clientForeColor(), clientBackColor(), true, true);
    }
}

void Button::handleClick () const
{
    ABOQALOG(Info, name() << " clicked");
}
