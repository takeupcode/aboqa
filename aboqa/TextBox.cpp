//
//  TextBox.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/18/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "TextBox.h"

#include <sstream>
#include <stdexcept>

#include "Button.h"
#include "Colors.h"
#include "ConsoleManager.h"
#include "Justification.h"

const std::string TextBox::windowName = "parent";
const std::string TextBox::moveCursorUpButtonName = "moveUpButton";
const std::string TextBox::moveCursorDownButtonName = "moveDownButton";
const std::string TextBox::moveCursorLeftButtonName = "moveLeftButton";
const std::string TextBox::moveCursorRightButtonName = "moveRightButton";

TextBox::TextBox (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int selectedForeColor, int selectedBackColor, bool multiline)
: Window(name, y, x, height, width, foreColor, backColor, foreColor, backColor, foreColor, backColor, false),
  mTextChanged(new TextChangedEvent()), mSelectionChanged(new SelectionChangedEvent()),
  mSelectedForeColor(selectedForeColor), mSelectedBackColor(selectedBackColor),
  mScrollY(0), mScrollX(0), mCursorY(0), mCursorX(0), mMultiline(multiline)
{
    if (multiline)
    {
        if (height < 4)
        {
            throw std::out_of_range("height cannot be less than 4 when using multi-line.");
        }
        if (width < 2)
        {
            throw std::out_of_range("width cannot be less than 2 when using multi-line.");
        }
        
        mMinHeight = 4;
        mMinWidth = 2;
    }
    else
    {
        if (height != 1)
        {
            throw std::out_of_range("height must be 1 when using single-line.");
        }
        if (width < 3)
        {
            throw std::out_of_range("width cannot be less than 3 when using single-line.");
        }
        
        mMinHeight = 1;
        mMinWidth = 3;
    }
    
    setFillClientArea(false);
    
    std::istringstream ss(text);
    std::string line;
    while (std::getline(ss, line))
    {
        mText.push_back(std::move(line));
    }
    
    mMoveCursorLeftButton = new Button(moveCursorLeftButtonName, "<", 0, 0, 1, 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
    mMoveCursorLeftButton->clicked()->connect(windowName, this);
    
    mMoveCursorRightButton = new Button(moveCursorRightButtonName, ">", 0, 0, 1, 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
    mMoveCursorRightButton->clicked()->connect(windowName, this);
    
    if (multiline)
    {
        mMoveCursorUpButton = new Button(moveCursorUpButtonName, "+", 0, 0, 1, 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
        mMoveCursorUpButton->clicked()->connect(windowName, this);
        addControl(std::unique_ptr<Button>(mMoveCursorUpButton));
        
        mMoveCursorDownButton = new Button(moveCursorDownButtonName, "-", 0, 0, 1, 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
        mMoveCursorDownButton->clicked()->connect(windowName, this);
        addControl(std::unique_ptr<Button>(mMoveCursorDownButton));
        
        mMoveCursorUpButton->setAnchorTop(0);
        mMoveCursorUpButton->setAnchorRight(0);
        
        mMoveCursorDownButton->setAnchorTop(1);
        mMoveCursorDownButton->setAnchorRight(0);

        mMoveCursorLeftButton->setAnchorTop(2);
        mMoveCursorLeftButton->setAnchorRight(0);
        
        mMoveCursorRightButton->setAnchorTop(3);
        mMoveCursorRightButton->setAnchorRight(0);
    }
    else
    {
        mMoveCursorLeftButton->setAnchorTop(0);
        mMoveCursorLeftButton->setAnchorRight(1);
        
        mMoveCursorRightButton->setAnchorTop(0);
        mMoveCursorRightButton->setAnchorRight(0);
    }
    
    addControl(std::unique_ptr<Button>(mMoveCursorLeftButton));
    addControl(std::unique_ptr<Button>(mMoveCursorRightButton));
}

bool TextBox::onKeyPress (GameManager * gm, int key)
{
    if (enableState() != Window::EnableState::enabled)
    {
        return false;
    }
    
    switch (key)
    {
    case 10: // Enter
        break;
        
    case KEY_UP:
        moveCursorUp();
        break;
        
    case KEY_DOWN:
        moveCursorDown();
        break;
        
    case KEY_LEFT:
        moveCursorLeft();
        break;
        
    case KEY_RIGHT:
        moveCursorRight();
        break;
        
    default:
        return true;
    }
    
    return true;
}

void TextBox::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState)
{
    if (enableState() != Window::EnableState::enabled)
    {
        return;
    }
    
    if (buttonState & BUTTON1_CLICKED)
    {
        if (x - clientX() < textClientWidth())
        {
            // Don't move the cursor if the click is in the non-client area.
            mCursorY = y - clientY();
            mCursorX = x - clientX();
        }
    }
}

void TextBox::onDrawClient () const
{
    if (visibleState() != Window::VisibleState::shown)
    {
        return;
    }
    
    if (isMultiline())
    {
        int i = 0;
        for (auto & line: mText)
        {
            std::string lineText = line.substr(0, textClientWidth());
            ConsoleManager::printMessage(*this, i, 0, textClientWidth(), lineText, clientForeColor(), clientBackColor(), Justification::Horizontal::left, true, mCursorY, mCursorX);
            
            ++i;
            if (i >= clientHeight())
            {
                return;
            }
        }
        for (; i < clientHeight(); ++i)
        {
            ConsoleManager::printMessage(*this, i, 0, textClientWidth(), " ", clientForeColor(), clientBackColor(), Justification::Horizontal::left, true, mCursorY, mCursorX);
        }
    }
    else
    {
        int vertCenter = clientHeight() / 2;
        std::string lineText = mText.front().substr(0, textClientWidth());
        ConsoleManager::printMessage(*this, vertCenter, 0, textClientWidth(), lineText, clientForeColor(), clientBackColor(), Justification::Horizontal::left, true, mCursorY, mCursorX);
    }
}

void TextBox::onDrawNonClient () const
{
    if (visibleState() != Window::VisibleState::shown)
    {
        return;
    }
    
    for (int i = 0; i < clientHeight(); ++i)
    {
        ConsoleManager::printMessage(*this, i, clientWidth() - 1, 1, " ", Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Justification::Horizontal::left, false);
    }
}

int TextBox::textClientWidth () const
{
    // This method accounts for the area used by the scrolling buttons.
    if (mMultiline)
    {
        // If multi-line, then all the scrolling buttons are in the rightmost column.
        return clientWidth() - 1;
    }
    
    // For single-line, the left and right scrolling buttons occupy the last two columns.
    return clientWidth() - 2;
}

void TextBox::setMinHeight (int height)
{
    if (mMultiline)
    {
        if (height < 4)
        {
            throw std::out_of_range("height cannot be less than 4 when using multi-line.");
        }
    }
    else
    {
        if (height != 1)
        {
            throw std::out_of_range("height must be 1 when using single-line.");
        }
    }
    
    mMinHeight = height;
}

void TextBox::setMinWidth (int width)
{
    if (mMultiline)
    {
        if (width < 2)
        {
            throw std::out_of_range("width cannot be less than 2 when using multi-line.");
        }
    }
    else
    {
        if (width < 3)
        {
            throw std::out_of_range("width cannot be less than 3 when using single-line.");
        }
    }
    
    mMinWidth = width;
}

int TextBox::selectedForeColor () const
{
    return mSelectedForeColor;
}

void TextBox::setSelectedForeColor (int color)
{
    mSelectedForeColor = color;
}

int TextBox::selectedBackColor () const
{
    return mSelectedBackColor;
}

void TextBox::setSelectedBackColor (int color)
{
    mSelectedBackColor = color;
}

bool TextBox::isMultiline () const
{
    return mMultiline;
}

void TextBox::setMultiline (bool multiline)
{
    mMultiline = multiline;
}

TextBox::TextChangedEvent * TextBox::textChanged ()
{
    return mTextChanged.get();
}

TextBox::SelectionChangedEvent * TextBox::selectionChanged ()
{
    return mSelectionChanged.get();
}

void TextBox::notify (GameManager * gm, const Button * button)
{
    if (button->name() == moveCursorUpButtonName)
    {
        moveCursorUp();
    }
    else if (button->name() == moveCursorDownButtonName)
    {
        moveCursorDown();
    }
    else if (button->name() == moveCursorLeftButtonName)
    {
        moveCursorLeft();
    }
    else if (button->name() == moveCursorRightButtonName)
    {
        moveCursorRight();
    }
}

void TextBox::moveCursorUp ()
{
    if (mCursorY > 0)
    {
        --mCursorY;
    }
}

void TextBox::moveCursorDown ()
{
    if (mCursorY < clientHeight() - 1)
    {
        ++mCursorY;
    }
}

void TextBox::moveCursorLeft ()
{
    if (mCursorX > 0)
    {
        --mCursorX;
    }
}

void TextBox::moveCursorRight ()
{
    if (mCursorX < textClientWidth() - 1)
    {
        ++mCursorX;
    }
}
