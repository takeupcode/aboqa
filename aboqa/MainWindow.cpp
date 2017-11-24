//
//  MainWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "MainWindow.h"

#include "Colors.h"
#include "GameManager.h"
#include "LogManager.h"
#include "TextBox.h"

const std::string MainWindow::windowName = "MainWindow";
const std::string MainWindow::textBoxName = "textBox";

MainWindow::MainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, clientForeColor, clientBackColor, border)
{
    setIsDirectFocusPossible(false);
    
    auto textBox = std::unique_ptr<TextBox>(new TextBox(textBoxName, "line 1\nline 2 is longer\nline 3\nline 4 is also long\nline 5\nline 6", 0, 0, 7, 20, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_CYAN, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_BLUE, true));
    textBox->setAnchorTop(2);
    textBox->setAnchorBottom(2);
    textBox->setAnchorLeft(20);
    textBox->setAnchorRight(15);
    addControl(std::move(textBox));
}

bool MainWindow::onKeyPress (GameManager * gm, int key)
{
    switch (key)
    {
    case KEY_DOWN:
        ABOQALOG(Info, "Down key pressed from main window.");
        break;
    case KEY_UP:
        break;
    case 10: // Enter
        break;
    case KEY_F(1):
        gm->selectNextWindow("exit");
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

void MainWindow::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState)
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

void MainWindow::onDrawClient () const
{
    
}
