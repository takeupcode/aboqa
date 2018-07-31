//
//  MainWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "MainWindow.h"

#include "../submodules/TUCUT/Curses/Colors.h"
#include "../submodules/TUCUT/Curses/GameManager.h"
#include "../submodules/TUCUT/Log/LogManager.h"

const std::string MainWindow::windowName = "MainWindow";
const std::string MainWindow::exitButtonName = "exitButton";
const std::string MainWindow::textBoxName = "textBox";
const std::string MainWindow::checkBoxName = "checkBox";
const std::string MainWindow::numberBoxName = "numberBox";
const std::string MainWindow::listBoxName = "listBox";

MainWindow::MainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, clientForeColor, clientBackColor, border)
{
    setIsDirectFocusPossible(false);
}

void MainWindow::initialize ()
{
    Window::initialize();
    
    mTextBox = TUCUT::Curses::TextBox::createSharedTextBox(textBoxName, "line 1\nline 2 is longer\nline 3\nline 4 is also long\nline 5\nline 6", 0, 0, 7, 20, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_CYAN, true);
    mTextBox->setAnchorTop(2);
    mTextBox->setAnchorBottom(5);
    mTextBox->setAnchorLeft(20);
    mTextBox->setAnchorRight(15);
    addControl(mTextBox);
    
    mCheckBox = TUCUT::Curses::CheckBox::createSharedCheckBox(checkBoxName, "check box", 0, 0, 1, 15, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    mCheckBox->setAnchorBottom(2);
    mCheckBox->setAnchorRight(1);
    addControl(mCheckBox);
    
    mNumberBox = TUCUT::Curses::NumberBox::createSharedNumberBox(numberBoxName, 0, 0, 0, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_WHITE);
    mNumberBox->setAnchorBottom(2);
    mNumberBox->setAnchorLeft(1);
    addControl(mNumberBox);
    
    std::vector<std::string> items;
    items.push_back("zero");
    items.push_back("one");
    items.push_back("two");
    items.push_back("three");
    items.push_back("four");
    items.push_back("five");
    items.push_back("six");
    items.push_back("seven");
    items.push_back("eight");
    items.push_back("nine");
    items.push_back("a");
    items.push_back("b");
    items.push_back("c");
    items.push_back("d");
    items.push_back("e");
    items.push_back("f");
    
    mListBox = TUCUT::Curses::ListBox::createSharedListBox(listBoxName, items, 0, 0, 10, 15, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_WHITE, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_WHITE);
    mListBox->setAnchorTop(0);
    mListBox->setAnchorLeft(0);
    addControl(mListBox);
    
    auto exitButton = TUCUT::Curses::Button::createSharedButton(exitButtonName, "Exit", 0, 0, 1, 10, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_RED, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_RED);
    exitButton->setAnchorBottom(0);
    exitButton->setAnchorRight(0);
    exitButton->clicked()->connect(windowName, getSharedMainWindow());
    addControl(exitButton);
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

void MainWindow::notify (TUCUT::Curses::GameManager * gm, const TUCUT::Curses::Button * button)
{
    if (button->name() == exitButtonName)
    {
        gm->selectNextWindow("exit");
    }
}
