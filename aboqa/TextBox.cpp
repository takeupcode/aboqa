//
//  TextBox.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/18/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "TextBox.h"

#include <sstream>

#include "ConsoleManager.h"
#include "Justification.h"

TextBox::TextBox (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int selectedForeColor, int selectedBackColor, bool multiline)
: Window(name, y, x, height, width, foreColor, backColor, foreColor, backColor, foreColor, backColor, false),
  mTextChanged(new TextChangedEvent()), mSelectionChanged(new SelectionChangedEvent()),
  mSelectedForeColor(selectedForeColor), mSelectedBackColor(selectedBackColor), mMultiline(multiline)
{
    setFillClientArea(false);
    
    std::istringstream ss(text);
    std::string line;
    while (std::getline(ss, line))
    {
        mText.push_back(std::move(line));
    }
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
            std::string lineText = line.substr(0, clientWidth());
            ConsoleManager::printMessage(*this, i, 0, clientWidth(), lineText, clientForeColor(), clientBackColor(), Justification::Horizontal::left, true);
            
            ++i;
            if (i >= clientHeight())
            {
                return;
            }
        }
        for (; i < clientHeight(); ++i)
        {
            ConsoleManager::printMessage(*this, i, 0, clientWidth(), " ", clientForeColor(), clientBackColor(), Justification::Horizontal::left, true);
        }
    }
    else
    {
        int vertCenter = clientHeight() / 2;
        std::string lineText = mText.front().substr(0, clientWidth());
        ConsoleManager::printMessage(*this, vertCenter, 0, clientWidth(), lineText, clientForeColor(), clientBackColor(), Justification::Horizontal::left, true);
    }
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
