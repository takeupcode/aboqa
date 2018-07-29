//
//  SplashWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "SplashWindow.h"

#include "../submodules/TUCUT/Curses/Colors.h"
#include "../submodules/TUCUT/Curses/GameManager.h"
#include "../submodules/TUCUT/Curses/Label.h"
#include "../submodules/TUCUT/Log/LogManager.h"

const std::string SplashWindow::windowName = "SplashWindow";
const std::string SplashWindow::playButtonName = "playButton";
const std::string SplashWindow::exitButtonName = "exitButton";
const std::string SplashWindow::introLabelName = "introLabel";

SplashWindow::SplashWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, clientForeColor, clientBackColor, border)
{
    setIsDirectFocusPossible(false);
}

void SplashWindow::initialize ()
{
    Window::initialize();
    
    auto playButton = TUCUT::Curses::Button::createSharedButton(playButtonName, "Play", 0, 0, 1, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    playButton->setAnchorBottom(0);
    playButton->setAnchorRight(0);
    playButton->setWantEnter(true);
    playButton->clicked()->connect(windowName, getSharedSplashWindow());
    addControl(playButton);
    
    auto exitButton = TUCUT::Curses::Button::createSharedButton(exitButtonName, "Exit", 0, 0, 1, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    exitButton->setAnchorBottom(0);
    exitButton->setAnchorRight(12);
    exitButton->clicked()->connect(windowName, getSharedSplashWindow());
    addControl(exitButton);
    
    auto introLabel = TUCUT::Curses::Label::createSharedLabel(introLabelName, "Play game?\nThis is a long multi-string that goes beyond 20 characters.", 0, 0, 7, 20, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_CYAN, TUCUT::Curses::Justification::Horizontal::right, TUCUT::Curses::Justification::Vertical::center, true);
    introLabel->setAnchorLeft(20);
    introLabel->setAnchorRight(15);
    addControl(introLabel);
}

std::shared_ptr<SplashWindow> SplashWindow::createSharedSplashWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
{
    auto result = std::shared_ptr<SplashWindow>(new SplashWindow(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, border));
    
    result->initialize();
    
    return result;
}

std::shared_ptr<SplashWindow> SplashWindow::getSharedSplashWindow ()
{
    return std::static_pointer_cast<SplashWindow>(shared_from_this());
}

bool SplashWindow::onKeyPress (TUCUT::Curses::GameManager * gm, int key)
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

void SplashWindow::onMouseEvent (TUCUT::Curses::GameManager * gm, short id, int y, int x, mmask_t buttonState)
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

void SplashWindow::onDrawClient () const
{
    
}

void SplashWindow::notify (TUCUT::Curses::GameManager * gm, const TUCUT::Curses::Button * button)
{
    if (button->name() == playButtonName)
    {
        gm->selectNextWindow("main");
    }
    else if (button->name() == exitButtonName)
    {
        gm->selectNextWindow("exit");
    }
}
