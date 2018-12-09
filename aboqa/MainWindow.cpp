//
//  MainWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "MainWindow.h"
#include "CharacterSystem.h"

#include <sstream>

#include "../submodules/TUCUT/Curses/Colors.h"
#include "../submodules/TUCUT/Curses/WindowSystem.h"
#include "../submodules/TUCUT/Game/PositionComponent.h"
#include "../submodules/TUCUT/Log/LogManager.h"

const std::string MainWindow::windowName = "MainWindow";
const std::string MainWindow::displayBoxName = "displayBox";
const std::string MainWindow::statusName = "status";
const std::string MainWindow::status2Name = "status2";
const std::string MainWindow::exitButtonName = "exitButton";
const std::string MainWindow::inventoryButtonName = "inventoryButton";

MainWindow::MainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, clientForeColor, clientBackColor, border)
{
    setIsDirectFocusPossible(false);
}

void MainWindow::initialize ()
{
    Window::initialize();
    
    mMapHeight = 30;
    mMapWidth = 30;
    mMap = {
        "     .                        ",
        "     .                        ",
        "     .                        ",
        ".. ...                        ",
        " . .                          ",
        " . .........                  ",
        " .                            ",
        " . ...........................",
        " . .                          ",
        " . .                          ",
        "                              ",
        " . ................   ........",
        " . .                         .",
        " . .              .   .      .",
        " . .              .   .      .",
        " . ................   ........",
        " . .                          ",
        " . .                          ",
        " . .                          ",
        " . .                          ",
        " . .                          ",
        " . .  . .                     ",
        " . .  . .                     ",
        " . .... ..................    ",
        " .                       .    ",
        " .                       .    ",
        " .                       .    ",
        " .                       .    ",
        " .........................    ",
        "                              "
    };

    mDisplayBox = TUCUT::Curses::DisplayBox::createSharedDisplayBox(displayBoxName, '*', 0, 0, 20, 20, mMapHeight, mMapWidth, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_CYAN, true, true, 4, 4, 4, 4);
    mDisplayBox->setAnchorTop(0);
    mDisplayBox->setAnchorBottom(0);
    mDisplayBox->setAnchorLeft(0);
    mDisplayBox->clicked()->connect(windowName, getSharedMainWindow());
    mDisplayBox->scrollChanged()->connect(windowName, getSharedMainWindow());
    mDisplayBox->beforeCenterChanged()->connect(windowName, getSharedMainWindow());
    mDisplayBox->afterCenterChanged()->connect(windowName, getSharedMainWindow());
    addControl(mDisplayBox);
    
    int y = 12;
    int x = 21;

    TUCUT::Game::GameManager * pGameMgr = TUCUT::Game::GameManager::instance();

    auto cs = pGameMgr->getOrCreateGameSystem<CharacterSystem>();

    mHero = cs->getOrCreateCharacter("hero");
    auto positionComp = mHero->getGameComponentFromAbility("GamePosition");
    positionComp->setFloating(mHero, TUCUT::Game::PositionComponent::y, y);
    positionComp->setFloating(mHero, TUCUT::Game::PositionComponent::x, x);

    mDisplayBox->setCenter(y, x);
    mDisplayBox->ensureCenterIsVisible();

    mStatus = TUCUT::Curses::Label::createSharedLabel(statusName, "", 0, 0, 3, 20, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_CYAN, TUCUT::Curses::Justification::Horizontal::left, TUCUT::Curses::Justification::Vertical::top, true);
    mStatus->setAnchorBottom(0);
    mStatus->setAnchorLeft(20);
    mStatus->setAnchorRight(10);
    addControl(mStatus);

    mStatus2 = TUCUT::Curses::Label::createSharedLabel(status2Name, "", 0, 0, 3, 20, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_CYAN, TUCUT::Curses::Justification::Horizontal::left, TUCUT::Curses::Justification::Vertical::top, true);
    mStatus2->setAnchorBottom(4);
    mStatus2->setAnchorLeft(20);
    mStatus2->setAnchorRight(10);
    addControl(mStatus2);
    
    mVisibleRange = 5;
    updateVisibleDisplay();

    mExitButton = TUCUT::Curses::Button::createSharedButton(exitButtonName, "Exit", 0, 0, 1, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    mExitButton->setAnchorBottom(0);
    mExitButton->setAnchorRight(0);
    mExitButton->clicked()->connect(windowName, getSharedMainWindow());
    addControl(mExitButton);

    mInventoryButton = TUCUT::Curses::Button::createSharedButton(inventoryButtonName, "Items", 0, 0, 1, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    mInventoryButton->setAnchorBottom(1);
    mInventoryButton->setAnchorRight(0);
    mInventoryButton->clicked()->connect(windowName, getSharedMainWindow());
    addControl(mInventoryButton);
}

std::shared_ptr<MainWindow> MainWindow::createSharedMainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
{
    auto result = std::shared_ptr<MainWindow>(new MainWindow(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, border));
    
    result->initialize();
    
    return result;
}

std::shared_ptr<MainWindow> MainWindow::getSharedMainWindow ()
{
    return std::static_pointer_cast<MainWindow>(shared_from_this());
}

bool MainWindow::onKeyPress (TUCUT::Curses::WindowSystem * ws, int key)
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

void MainWindow::onMouseEvent (TUCUT::Curses::WindowSystem * ws, short id, int y, int x, mmask_t buttonState)
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

void MainWindow::notify (int id, TUCUT::Curses::WindowSystem * ws, TUCUT::Curses::Button * button)
{
    if (id != TUCUT::Curses::Button::ClickedEventId)
    {
        return;
    }
    
    if (button->name() == exitButtonName)
    {
        ws->selectNextWindow("exit");
    }
    else if (button->name() == inventoryButtonName)
    {
        ws->selectNextWindow("inventory");
    }
}

void MainWindow::notify (int id, TUCUT::Curses::WindowSystem * ws, TUCUT::Curses::DisplayBox * display, int y, int x, bool & cancel)
{
    if (id == TUCUT::Curses::DisplayBox::BeforeCenterChangedEventId)
    {
        if (mMap[y][x] == '.')
        {
            cancel = true;
        }
    }
}

void MainWindow::notify (int id, TUCUT::Curses::WindowSystem * ws, TUCUT::Curses::DisplayBox * display, int y, int x)
{
    if (id == TUCUT::Curses::DisplayBox::ClickedEventId)
    {
        if (display->name() == displayBoxName)
        {
            display->showClickLocation(true);
            
            std::stringstream ss;
            ss << "Clicked location (x=" << x << ", y=" << y << ")";
            
            mStatus->setText(ss.str());
        }
    }
    else if (id == TUCUT::Curses::DisplayBox::ScrollChangedEventId)
    {
        if (display->name() == displayBoxName)
        {
            std::stringstream ss;
            ss << "Scroll location (x=" << x << ", y=" << y << ")";
            
            mStatus->setText(ss.str());
        }
    }
    else if (id == TUCUT::Curses::DisplayBox::AfterCenterChangedEventId)
    {
        if (display->name() == displayBoxName)
        {
            auto positionComp = mHero->getGameComponentFromAbility("GamePosition");
            positionComp->setFloating(mHero, TUCUT::Game::PositionComponent::y, y);
            positionComp->setFloating(mHero, TUCUT::Game::PositionComponent::x, x);
            updateVisibleDisplay();
            
            std::stringstream ss;
            ss << "Center location (x=" << x << ", y=" << y << ")";
            
            mStatus->setText(ss.str());
        }
    }
}

void MainWindow::updateVisibleDisplay ()
{
    auto positionComp = mHero->getGameComponentFromAbility("GamePosition");
    int heroYOld = static_cast<int>(positionComp->getFloating(mHero, TUCUT::Game::PositionComponent::yOld));
    int heroXOld = static_cast<int>(positionComp->getFloating(mHero, TUCUT::Game::PositionComponent::xOld));
    
    updateVisibleDisplayImpl(heroYOld, heroXOld, true);
    
    int heroY = static_cast<int>(positionComp->getFloating(mHero, TUCUT::Game::PositionComponent::y));
    int heroX = static_cast<int>(positionComp->getFloating(mHero, TUCUT::Game::PositionComponent::x));
    
    updateVisibleDisplayImpl(heroY, heroX, false);

    std::stringstream ss;
    ss << "Hero location (x=" << heroX << ", y=" << heroY << ")";
    
    mStatus2->setText(ss.str());
}

void MainWindow::updateVisibleDisplayImpl (int heroY, int heroX, bool clear)
{
    // xx*xx
    // x***x
    // **0**
    // x***x
    // xx*xx
    for (int y = -mVisibleRange; y <= mVisibleRange; y++)
    {
        int offset = 0;
        if (y < 0)
        {
            offset = -y;
            if (heroY < offset)
            {
                continue;
            }
        }
        else
        {
            offset = y;
            if (heroY >= mMapHeight - offset)
            {
                break;
            }
        }
        for (int x = -mVisibleRange + offset; x <= mVisibleRange - offset; x++)
        {
            if (x < 0)
            {
                if (heroX < -x)
                {
                    continue;
                }
            }
            else
            {
                if (heroX >= mMapWidth - x)
                {
                    break;
                }
            }
            
            mDisplayBox->setSymbol(clear ? ' ' : mMap[heroY + y][heroX + x], heroY + y, heroX + x);
        }
    }
}
