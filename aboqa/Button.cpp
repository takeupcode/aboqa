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
#include "Justification.h"
#include "LogManager.h"

Button::Button (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int focusForeColor, int focusBackColor)
: Window(name, y, x, height, width, foreColor, backColor, foreColor, backColor, focusForeColor, focusBackColor, false),
  mText(text), mClicked(new ClickedEvent())
{
    setFillClientArea(false);
}

bool Button::onKeyPress (GameManager * gm, int key)
{
    if (enableState() != Window::EnableState::enabled)
    {
        return false;
    }
    
    switch (key)
    {
    case 32: // Space
    case 10: // Enter
        handleClick(gm);
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

void Button::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState)
{
    if (enableState() != Window::EnableState::enabled)
    {
        return;
    }
    
    if (buttonState & BUTTON1_CLICKED)
    {
        handleClick(gm);
    }
}

void Button::onDrawClient () const
{
    if (visibleState() != Window::VisibleState::shown)
    {
        return;
    }
    
    int vertCenter = height() / 2;
    if (hasDirectFocus())
    {
        ConsoleManager::printMessage(*this, vertCenter, 0, width(), mText, focusForeColor(), focusBackColor(), Justification::Horizontal::center, true);
        if (clientWidth() > 5)
        {
            // If we have room for at least 2 special chars on either side plus one more for the content,
            // then show focus bars and default button marker.
            mvwaddch(cursesWindow(), vertCenter, 0, '|');
            if (wantEnter())
            {
                waddch(cursesWindow(), '>');
            }
            mvwaddch(cursesWindow(), vertCenter, width() - 1, '|');
        }
    }
    else
    {
        ConsoleManager::printMessage(*this, vertCenter, 0, width(), mText, clientForeColor(), clientBackColor(), Justification::Horizontal::center, true);
    }
}

void Button::handleClick (GameManager * gm) const
{
    ABOQALOG(Info, name() << " clicked");
    
    mClicked->signal(gm, this);
}

Button::ClickedEvent * Button::clicked ()
{
    return mClicked.get();
}
