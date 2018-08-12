//
//  MainWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "MainWindow.h"

#include <sstream>

#include "../submodules/TUCUT/Curses/Colors.h"
#include "../submodules/TUCUT/Curses/GameManager.h"
#include "../submodules/TUCUT/Log/LogManager.h"

const std::string MainWindow::windowName = "MainWindow";
const std::string MainWindow::exitButtonName = "exitButton";
const std::string MainWindow::displayBoxName = "displayBox";
const std::string MainWindow::statusName = "status";

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

    mDisplayBox = TUCUT::Curses::DisplayBox::createSharedDisplayBox(displayBoxName, '*', 0, 0, 20, 20, mMapHeight, mMapWidth, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_CYAN, true, true, 2, 2, 2, 2);
    mDisplayBox->setAnchorTop(0);
    mDisplayBox->setAnchorBottom(0);
    mDisplayBox->setAnchorLeft(0);
    mDisplayBox->clicked()->connect(windowName, getSharedMainWindow());
    mDisplayBox->scrollChanged()->connect(windowName, getSharedMainWindow());
    mDisplayBox->beforeCenterChanged()->connect(windowName, getSharedMainWindow());
    mDisplayBox->afterCenterChanged()->connect(windowName, getSharedMainWindow());
    addControl(mDisplayBox);
    
    mY = 12;
    mX = 21;
    mDisplayBox->setCenter(mY, mX);
    mDisplayBox->ensureCenterIsVisible();
    
    updateDisplay();

    mStatus = TUCUT::Curses::Label::createSharedLabel(statusName, "", 0, 0, 3, 20, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_CYAN, TUCUT::Curses::Justification::Horizontal::left, TUCUT::Curses::Justification::Vertical::top, true);
    mStatus->setAnchorBottom(0);
    mStatus->setAnchorLeft(20);
    mStatus->setAnchorRight(10);
    addControl(mStatus);

    mExitButton = TUCUT::Curses::Button::createSharedButton(exitButtonName, "Exit", 0, 0, 1, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    mExitButton->setAnchorBottom(0);
    mExitButton->setAnchorRight(0);
    mExitButton->clicked()->connect(windowName, getSharedMainWindow());
    addControl(mExitButton);
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

bool MainWindow::onKeyPress (TUCUT::Curses::GameManager * gm, int key)
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

void MainWindow::onMouseEvent (TUCUT::Curses::GameManager * gm, short id, int y, int x, mmask_t buttonState)
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

void MainWindow::notify (int id, TUCUT::Curses::GameManager * gm, TUCUT::Curses::Button * button)
{
    if (id != TUCUT::Curses::Button::ClickedEventId)
    {
        return;
    }
    
    if (button->name() == exitButtonName)
    {
        gm->selectNextWindow("exit");
    }
}

void MainWindow::notify (int id, TUCUT::Curses::GameManager * gm, TUCUT::Curses::DisplayBox * display, int y, int x, bool & cancel)
{
    if (id == TUCUT::Curses::DisplayBox::BeforeCenterChangedEventId)
    {
        if (display->symbol(y, x) == '.')
        {
            cancel = true;
        }
    }
}

void MainWindow::notify (int id, TUCUT::Curses::GameManager * gm, TUCUT::Curses::DisplayBox * display, int y, int x)
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
            mY = y;
            mX = x;
            updateDisplay();
            
            std::stringstream ss;
            ss << "Center location (x=" << x << ", y=" << y << ")";
            
            mStatus->setText(ss.str());
        }
    }
}

void MainWindow::updateDisplay ()
{
    // xx*xx
    // x***x
    // **0**
    // x***x
    // xx*xx
    if (mY >= 2)
    {
        mDisplayBox->setSymbol(mMap[mY - 2][mX], mY - 2, mX);
    }
    if (mY >= 1)
    {
        if (mX >= 1)
        {
            mDisplayBox->setSymbol(mMap[mY - 1][mX - 1], mY - 1, mX - 1);
        }
        mDisplayBox->setSymbol(mMap[mY - 1][mX], mY - 1, mX);
        if (mX < mMapWidth - 1)
        {
            mDisplayBox->setSymbol(mMap[mY - 1][mX + 1], mY - 1, mX + 1);
        }
    }
    if (mX >= 2)
    {
        mDisplayBox->setSymbol(mMap[mY][mX - 2], mY, mX - 2);
    }
    if (mX >= 1)
    {
        mDisplayBox->setSymbol(mMap[mY][mX - 1], mY, mX - 1);
    }
    mDisplayBox->setSymbol(mMap[mY][mX], mY, mX);
    if (mX < mMapWidth - 1)
    {
        mDisplayBox->setSymbol(mMap[mY][mX + 1], mY, mX + 1);
    }
    if (mX < mMapWidth - 2)
    {
        mDisplayBox->setSymbol(mMap[mY][mX + 2], mY, mX + 2);
    }
    if (mY < mMapHeight - 1)
    {
        if (mX >= 1)
        {
            mDisplayBox->setSymbol(mMap[mY + 1][mX - 1], mY + 1, mX - 1);
        }
        mDisplayBox->setSymbol(mMap[mY + 1][mX], mY + 1, mX);
        if (mX < mMapWidth - 1)
        {
            mDisplayBox->setSymbol(mMap[mY + 1][mX + 1], mY + 1, mX + 1);
        }
    }
    if (mY < mMapHeight - 2)
    {
        mDisplayBox->setSymbol(mMap[mY + 2][mX], mY + 2, mX);
    }
}
