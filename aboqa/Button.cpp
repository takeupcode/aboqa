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

Button::Button (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor)
: Window(name, y, x, height, width, foreColor, backColor, foreColor, backColor, false), mText(text)
{ }

void Button::onKeyPress (GameManager * gm, int key) const
{
    switch(key)
    {
    case 32: // Space
    case 10: // Enter
        handleClick();
        break;
    }
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
    ConsoleManager::printMessage(cursesWindow(), vertCenter, 0, width(), mText, clientForeColor(), clientBackColor(), true, false);
}

void Button::handleClick () const
{
    ABOQALOG(Info, "Button " << name() << " clicked");
}
