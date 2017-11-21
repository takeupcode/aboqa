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
const std::string TextBox::scrollUpButtonName = "scrollUpButton";
const std::string TextBox::scrollDownButtonName = "scrollDownButton";
const std::string TextBox::scrollLeftButtonName = "scrollLeftButton";
const std::string TextBox::scrollRightButtonName = "scrollRightButton";

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
    
    mScrollLeftButton = new Button(scrollLeftButtonName, "<", 0, 0, 1, 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
    mScrollLeftButton->clicked()->connect(windowName, this);
    
    mScrollRightButton = new Button(scrollRightButtonName, ">", 0, 0, 1, 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
    mScrollRightButton->clicked()->connect(windowName, this);
    
    if (multiline)
    {
        mScrollUpButton = new Button(scrollUpButtonName, "+", 0, 0, 1, 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
        mScrollUpButton->clicked()->connect(windowName, this);
        addControl(std::unique_ptr<Button>(mScrollUpButton));
        
        mScrollDownButton = new Button(scrollDownButtonName, "-", 0, 0, 1, 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE);
        mScrollDownButton->clicked()->connect(windowName, this);
        addControl(std::unique_ptr<Button>(mScrollDownButton));
        
        mScrollUpButton->setAnchorTop(0);
        mScrollUpButton->setAnchorRight(0);
        
        mScrollDownButton->setAnchorTop(1);
        mScrollDownButton->setAnchorRight(0);

        mScrollLeftButton->setAnchorTop(2);
        mScrollLeftButton->setAnchorRight(0);
        
        mScrollRightButton->setAnchorTop(3);
        mScrollRightButton->setAnchorRight(0);
}
    else
    {
        mScrollLeftButton->setAnchorTop(0);
        mScrollLeftButton->setAnchorRight(1);
        
        mScrollRightButton->setAnchorTop(0);
        mScrollRightButton->setAnchorRight(0);
    }
    
    addControl(std::unique_ptr<Button>(mScrollLeftButton));
    addControl(std::unique_ptr<Button>(mScrollRightButton));
}

bool TextBox::onKeyPress (GameManager * gm, int key) const
{
    if (enableState() != Window::EnableState::enabled)
    {
        return false;
    }
    
    switch (key)
    {
        case 10: // Enter
            break;
        default:
            return true;
    }
    
    return true;
}

void TextBox::onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const
{
    if (enableState() != Window::EnableState::enabled)
    {
        return;
    }
    
    if (buttonState & BUTTON1_CLICKED)
    {
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
    if (button->name() == scrollUpButtonName)
    {
    }
    else if (button->name() == scrollDownButtonName)
    {
    }
    else if (button->name() == scrollLeftButtonName)
    {
    }
    else if (button->name() == scrollRightButtonName)
    {
    }
}
