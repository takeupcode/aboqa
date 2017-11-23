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
  mScrollY(0), mScrollX(0), mCursorY(0), mCursorX(0), mDesiredColumn(0), mMultiline(multiline)
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
    if (mText.empty())
    {
        mText.push_back("");
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
            int cursorY = y - clientY();
            int cursorX = x - clientX();
            
            bool goToMaxX = false;
            if (cursorY > (static_cast<int>(mText.size()) - mScrollY - 1))
            {
                cursorY = static_cast<int>(mText.size()) - mScrollY - 1;
                goToMaxX = true;
            }
            
            if (goToMaxX ||
                cursorX > (static_cast<int>(mText[cursorY + mScrollY].size()) - mScrollX))
            {
                cursorX = static_cast<int>(mText[cursorY + mScrollY].size() - mScrollX);
            }
            
            mCursorY = cursorY;
            mCursorX = cursorX;
            mDesiredColumn = mScrollX + cursorX;
            ensureCursorIsVisible();
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
        for (; i < clientHeight(); ++i)
        {
            if (i + mScrollY >= static_cast<int>(mText.size()))
            {
                break;
            }
            
            std::string lineText = "";
            if (mScrollX < static_cast<int>(mText[i + mScrollY].size()))
            {
                lineText = mText[i + mScrollY].substr(mScrollX, textClientWidth());
            }
            ConsoleManager::printMessage(*this, i, 0, textClientWidth(), lineText, clientForeColor(), clientBackColor(), Justification::Horizontal::left, true, mCursorY, mCursorX);
        }
        for (; i < clientHeight(); ++i)
        {
            ConsoleManager::printMessage(*this, i, 0, textClientWidth(), " ", clientForeColor(), clientBackColor(), Justification::Horizontal::left, true, mCursorY, mCursorX);
        }
    }
    else
    {
        int vertCenter = clientHeight() / 2;
        std::string lineText = "";
        if (mScrollX < static_cast<int>(mText[0].size()))
        {
            lineText = mText[0].substr(mScrollX, textClientWidth());
        }
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

void TextBox::onResize ()
{
    ensureCursorIsVisible();
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
    else
    {
        if (mScrollY > 0)
        {
            --mScrollY;
        }
    }
    
    placeCursorClosestToDesiredColumn();
    ensureCursorIsVisible();
}

void TextBox::moveCursorDown ()
{
    if (mCursorY < (clientHeight() - 1) &&
        mCursorY < (static_cast<int>(mText.size()) - mScrollY - 1))
    {
        ++mCursorY;
    }
    else if (mCursorY == (clientHeight() - 1) &&
             mScrollY < (static_cast<int>(mText.size()) - clientHeight()))
    {
        ++mScrollY;
    }
    
    placeCursorClosestToDesiredColumn();
    ensureCursorIsVisible();
}

void TextBox::moveCursorLeft ()
{
    if (mCursorX > 0)
    {
        --mCursorX;
    }
    else
    {
        if (mScrollX > 0)
        {
            --mScrollX;
        }
        else if (mCursorY > 0 || mScrollY > 0)
        {
            --mCursorY;
            mCursorX = static_cast<int>(mText[mScrollY + mCursorY].size());
        }
    }
    mDesiredColumn = mCursorX + mScrollX;
    ensureCursorIsVisible();
}

void TextBox::moveCursorRight ()
{
    if (mCursorX < (textClientWidth() - 1) &&
        mCursorY < (static_cast<int>(mText.size()) - mScrollY) &&
        mCursorX < (static_cast<int>(mText[mCursorY + mScrollY].size()) - mScrollX))
    {
        ++mCursorX;
    }
    else if (mCursorX == (textClientWidth() - 1) &&
             mCursorY < (static_cast<int>(mText.size()) - mScrollY) &&
             mScrollX <= (static_cast<int>(mText[mCursorY + mScrollY].size()) - textClientWidth()))
    {
        ++mScrollX;
    }
    mDesiredColumn = mCursorX + mScrollX;
    ensureCursorIsVisible();
}

void TextBox::placeCursorClosestToDesiredColumn ()
{
    if (mDesiredColumn > static_cast<int>(mText[mCursorY + mScrollY].size()))
    {
        mCursorX = static_cast<int>(mText[mCursorY + mScrollY].size() - mScrollX);
    }
    else
    {
        mCursorX = mDesiredColumn - mScrollX;
    }
}

void TextBox::ensureCursorIsVisible ()
{
    int cursorLineNumber = mScrollY + mCursorY;
    if (mCursorY < 0)
    {
        mScrollY = cursorLineNumber;
        mCursorY = 0;
    }
    else if (mCursorY > clientHeight() - 1)
    {
        mScrollY = cursorLineNumber - clientHeight() + 1;
        mCursorY = clientHeight() - 1;
    }
    
    int cursorColumnNumber = mScrollX + mCursorX;
    if (mCursorX < 0)
    {
        mScrollX = cursorColumnNumber;
        mCursorX = 0;
    }
    else if (mCursorX > textClientWidth() - 1)
    {
        mScrollX = cursorColumnNumber - textClientWidth() + 1;
        mCursorX = textClientWidth() - 1;
    }
}
