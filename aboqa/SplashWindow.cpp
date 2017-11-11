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
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, border, clientForeColor, clientBackColor)
{
    auto playButton = std::unique_ptr<Button>(new Button("playButton", "Play", 0, 0, 1, 10, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_RED, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_RED));
    playButton->setAnchorBottom(0);
    playButton->setAnchorRight(0);
    playButton->setWantEnter(true);
    playButton->clicked()->connect("SplashWindow", this);
    addControl(std::move(playButton));

    auto exitButton = std::unique_ptr<Button>(new Button("exitButton", "Exit", 0, 0, 1, 10, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_RED, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_RED));
    exitButton->setAnchorBottom(0);
    exitButton->setAnchorRight(12);
    exitButton->clicked()->connect("SplashWindow", this);
    addControl(std::move(exitButton));
}

bool SplashWindow::onKeyPress (GameManager * gm, int key) const
{
    switch (key)
    {
    case 10: // Enter
        for (auto & control: mControls)
        {
            if (control->wantEnter())
            {
                setFocus(control->y(), control->x());
                return control->onKeyPress(gm, key);
            }
        }
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

bool SplashWindow::canHaveDirectFocus () const
{
    return false;
}

void SplashWindow::notify (GameManager * gm, const Button * button)
{
    if (button->name() == "playButton")
    {
        gm->selectNextWindow("main");
    }
    else if (button->name() == "exitButton")
    {
        gm->selectNextWindow("exit");
    }
}
