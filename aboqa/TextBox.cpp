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
  mScrollLine(0), mScrollColumn(0), mCursorLine(0), mCursorColumn(0), mDesiredColumn(0), mMultiline(multiline)
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
    setWantEnter(true);
    
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
    case KEY_ENTER:
        breakLineAtCursor();
        break;
    
    case 127: // Delete
        removeCharAtCursor();
        break;
        
    case 8: // Backspace
    case KEY_DC:
    case KEY_BACKSPACE:
        if (mCursorColumn > 0)
        {
            mDesiredColumn = --mCursorColumn;
            
            removeCharAtCursor();
            
            ensureCursorIsVisible();
        }
        else if (mCursorLine > 0)
        {
            --mCursorLine;
            mDesiredColumn = mCursorColumn = static_cast<int>(mText[mCursorLine].size());
            
            removeCharAtCursor();
            
            ensureCursorIsVisible();
        }
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
        addCharAtCursor(key);
        break;
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
        // Don't move the cursor if the click is in the non-client area.
        if (x - clientX() < textClientWidth())
        {
            int winY = y - clientY();
            int line = winY + mScrollLine;
            int winX = x - clientX();
            int column = winX + mScrollColumn;
            
            bool goToMaxColumn = false;
            if (line >= (static_cast<int>(mText.size())))
            {
                line = static_cast<int>(mText.size()) - 1;
                goToMaxColumn = true;
            }
            
            if (goToMaxColumn ||
                column > (static_cast<int>(mText[line].size())))
            {
                column = static_cast<int>(mText[line].size());
            }
            
            mCursorLine = line;
            mCursorColumn = column;
            mDesiredColumn = column;
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
            if (i + mScrollLine >= static_cast<int>(mText.size()))
            {
                break;
            }
            
            std::string lineText = "";
            if (mScrollColumn < static_cast<int>(mText[i + mScrollLine].size()))
            {
                lineText = mText[i + mScrollLine].substr(mScrollColumn, textClientWidth());
            }
            ConsoleManager::printMessage(*this, i, 0, textClientWidth(), lineText, clientForeColor(), clientBackColor(), Justification::Horizontal::left, true, mCursorLine - mScrollLine, mCursorColumn - mScrollColumn);
        }
        for (; i < clientHeight(); ++i)
        {
            ConsoleManager::printMessage(*this, i, 0, textClientWidth(), " ", clientForeColor(), clientBackColor(), Justification::Horizontal::left, true);
        }
    }
    else
    {
        int vertCenter = clientHeight() / 2;
        std::string lineText = "";
        if (mScrollColumn < static_cast<int>(mText[0].size()))
        {
            lineText = mText[0].substr(mScrollColumn, textClientWidth());
        }
        ConsoleManager::printMessage(*this, vertCenter, 0, textClientWidth(), lineText, clientForeColor(), clientBackColor(), Justification::Horizontal::left, true, vertCenter, mCursorColumn - mScrollColumn);
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
    if (mCursorLine > 0)
    {
        --mCursorLine;
        
        placeCursorClosestToDesiredColumn();
        ensureCursorIsVisible();
    }
}

void TextBox::moveCursorDown ()
{
    if (mCursorLine < (static_cast<int>(mText.size()) - 1))
    {
        ++mCursorLine;
        
        placeCursorClosestToDesiredColumn();
        ensureCursorIsVisible();
    }
}

void TextBox::moveCursorLeft ()
{
    if (mCursorColumn > 0)
    {
        --mCursorColumn;
        
        mDesiredColumn = mCursorColumn;
        ensureCursorIsVisible();
    }
    else if (mCursorLine > 0)
    {
        --mCursorLine;
        mCursorColumn = static_cast<int>(mText[mCursorLine].size());
        
        mDesiredColumn = mCursorColumn;
        ensureCursorIsVisible();
    }
}

void TextBox::moveCursorRight ()
{
    if (mCursorColumn < (static_cast<int>(mText[mCursorLine].size())))
    {
        ++mCursorColumn;
        
        mDesiredColumn = mCursorColumn;
        ensureCursorIsVisible();
    }
    else if (mCursorLine < (static_cast<int>(mText.size()) - 1))
    {
        ++mCursorLine;
        mCursorColumn = 0;
        
        mDesiredColumn = mCursorColumn;
        ensureCursorIsVisible();
    }
}

void TextBox::breakLineAtCursor ()
{
    std::string currentText = mText[mCursorLine].substr(0, mCursorColumn);
    std::string nextText = mText[mCursorLine].substr(mCursorColumn, mText[mCursorLine].size());
    
    mText[mCursorLine] = currentText;
    mText.insert(mText.begin() + mCursorLine + 1, nextText);
    
    ++mCursorLine;
    mDesiredColumn = mCursorColumn = 0;
    ensureCursorIsVisible();
}

void TextBox::removeCharAtCursor ()
{
    if (mCursorColumn == static_cast<int>(mText[mCursorLine].size()) &&
        mCursorLine < static_cast<int>(mText.size()) - 1)
    {
        mText[mCursorLine] = mText[mCursorLine] + mText[mCursorLine + 1];
        mText.erase(mText.begin() + mCursorLine + 1);
    }
    else
    {
        mText[mCursorLine].erase(mText[mCursorLine].begin() + mCursorColumn);
    }
}

void TextBox::addCharAtCursor (int key)
{
    if (key < 32 || key > 126)
    {
        return;
    }
    
    mText[mCursorLine].insert(mText[mCursorLine].begin() + mCursorColumn, static_cast<char>(key));
    
    mDesiredColumn = ++mCursorColumn;
    ensureCursorIsVisible();
}

void TextBox::placeCursorClosestToDesiredColumn ()
{
    if (mDesiredColumn > static_cast<int>(mText[mCursorLine].size()))
    {
        mCursorColumn = static_cast<int>(mText[mCursorLine].size());
    }
    else
    {
        mCursorColumn = mDesiredColumn;
    }
}

void TextBox::ensureCursorIsVisible ()
{
    if (mCursorLine < mScrollLine)
    {
        mScrollLine = mCursorLine;
    }
    else if (mCursorLine >= mScrollLine + clientHeight())
    {
        mScrollLine = mCursorLine - clientHeight() + 1;
    }
    
    if (mCursorColumn < mScrollColumn)
    {
        mScrollColumn = mCursorColumn;
    }
    else if (mCursorColumn >= mScrollColumn + textClientWidth())
    {
        mScrollColumn = mCursorColumn - textClientWidth() + 1;
    }
}
