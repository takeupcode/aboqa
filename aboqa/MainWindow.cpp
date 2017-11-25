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
#include "CheckBox.h"
#include "NumberBox.h"
#include "ListBox.h"

const std::string MainWindow::windowName = "MainWindow";
const std::string MainWindow::textBoxName = "textBox";
const std::string MainWindow::checkBoxName = "checkBox";
const std::string MainWindow::numberBoxName = "numberBox";
const std::string MainWindow::listBoxName = "listBox";

MainWindow::MainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, clientForeColor, clientBackColor, border)
{
    setIsDirectFocusPossible(false);
    
    mTextBox = new TextBox(textBoxName, "line 1\nline 2 is longer\nline 3\nline 4 is also long\nline 5\nline 6", 0, 0, 7, 20, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_CYAN, true);
    mTextBox->setAnchorTop(2);
    mTextBox->setAnchorBottom(3);
    mTextBox->setAnchorLeft(20);
    mTextBox->setAnchorRight(15);
    addControl(std::unique_ptr<TextBox>(mTextBox));
    
    mCheckBox = new CheckBox(checkBoxName, "check box", 0, 0, 1, 15, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_RED, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_RED);
    mCheckBox->setAnchorBottom(1);
    mCheckBox->setAnchorRight(1);
    addControl(std::unique_ptr<CheckBox>(mCheckBox));
    
    mNumberBox = new NumberBox(numberBoxName, 0, 0, 0, 10, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE);
    mNumberBox->setAnchorBottom(1);
    mNumberBox->setAnchorLeft(1);
    addControl(std::unique_ptr<NumberBox>(mNumberBox));

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
    
    mListBox = new ListBox(listBoxName, items, 0, 0, 10, 15, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
    mListBox->setAnchorTop(2);
    mListBox->setAnchorLeft(2);
    addControl(std::unique_ptr<ListBox>(mListBox));
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
        ABOQALOG(Info, mTextBox->text());
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
