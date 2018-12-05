//
//  ExitWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "ExitWindow.h"

#include "../submodules/TUCUT/Curses/Colors.h"
#include "../submodules/TUCUT/Curses/WindowSystem.h"
#include "../submodules/TUCUT/Curses/Label.h"
#include "../submodules/TUCUT/Log/LogManager.h"

const std::string ExitWindow::windowName = "ExitWindow";
const std::string ExitWindow::exitButtonName = "exitButton";
const std::string ExitWindow::thanksLabelName = "thanksLabel";

ExitWindow::ExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, clientForeColor, clientBackColor, border)
{
    setIsDirectFocusPossible(false);
}

void ExitWindow::initialize ()
{
    Window::initialize();
    
    auto exitButton = TUCUT::Curses::Button::createSharedButton(exitButtonName, "Exit", 0, 0, 1, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    exitButton->setAnchorBottom(0);
    exitButton->setAnchorRight(0);
    exitButton->clicked()->connect(windowName, getSharedExitWindow());
    addControl(exitButton);
    
    auto thanksLabel = TUCUT::Curses::Label::createSharedLabel(thanksLabelName, "Thanks for playing!", 0, 0, 1, 25, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_CYAN, TUCUT::Curses::Justification::Horizontal::right, TUCUT::Curses::Justification::Vertical::center, true);
    thanksLabel->setAnchorTop(3);
    thanksLabel->setAnchorLeft(10);
    thanksLabel->setAnchorRight(10);
    addControl(thanksLabel);
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

bool ExitWindow::onKeyPress (TUCUT::Curses::WindowSystem * ws, int key)
{
    switch (key)
    {
        case 10: // Enter
            for (auto & control: mControls)
            {
                if (control->wantEnter())
                {
                    setFocus(control->y(), control->x());
                    return control->onKeyPress(ws, key);
                }
            }
            break;
        default:
            if (parent())
            {
                return parent()->onKeyPress(ws, key);
            }
            return false;
    }
    
    return true;
}

void ExitWindow::notify (int id, TUCUT::Curses::WindowSystem * ws, TUCUT::Curses::Button * button)
{
    if (id != TUCUT::Curses::Button::ClickedEventId)
    {
        return;
    }
    
    if (button->name() == exitButtonName)
    {
        TUCUT::Game::GameManager * pGameMgr = TUCUT::Game::GameManager::instance();
        pGameMgr->exit();
    }
}
