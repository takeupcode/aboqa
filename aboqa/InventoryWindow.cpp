//
//  InventoryWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 8/12/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#include "InventoryWindow.h"
#include "CharacterSystem.h"

#include "../submodules/TUCUT/Curses/Colors.h"
#include "../submodules/TUCUT/Curses/WindowSystem.h"
#include "../submodules/TUCUT/Curses/Label.h"
#include "../submodules/TUCUT/Log/LogManager.h"

const std::string InventoryWindow::windowName = "ExitWindow";
const std::string InventoryWindow::exitButtonName = "exitButton";

InventoryWindow::InventoryWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, clientForeColor, clientBackColor, border)
{
    setIsDirectFocusPossible(false);
}

void InventoryWindow::initialize ()
{
    Window::initialize();
    
    auto exitButton = TUCUT::Curses::Button::createSharedButton(exitButtonName, "Exit", 0, 0, 1, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    exitButton->setAnchorBottom(0);
    exitButton->setAnchorRight(0);
    exitButton->clicked()->connect(windowName, getSharedInventoryWindow());
    addControl(exitButton);
    
    TUCUT::Game::GameManager * pGameMgr = TUCUT::Game::GameManager::instance();
    
    std::string systemToken = "CharacterSystem";
    auto cs = pGameMgr->getOrCreateGameSystem<CharacterSystem>(systemToken);
    
    mHero = cs->getOrCreateCharacter("hero");
}

std::shared_ptr<InventoryWindow> InventoryWindow::createSharedInventoryWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
{
    auto result = std::shared_ptr<InventoryWindow>(new InventoryWindow(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, border));
    
    result->initialize();
    
    return result;
}

std::shared_ptr<InventoryWindow> InventoryWindow::getSharedInventoryWindow ()
{
    return std::static_pointer_cast<InventoryWindow>(shared_from_this());
}

bool InventoryWindow::onKeyPress (TUCUT::Curses::WindowSystem * ws, int key)
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

void InventoryWindow::notify (int id, TUCUT::Curses::WindowSystem * ws, TUCUT::Curses::Button * button)
{
    if (id != TUCUT::Curses::Button::ClickedEventId)
    {
        return;
    }
    
    if (button->name() == exitButtonName)
    {
        ws->selectNextWindow("main");
    }
}
