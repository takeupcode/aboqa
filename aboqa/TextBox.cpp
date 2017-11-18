//
//  TextBox.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/18/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "TextBox.h"

#include "ConsoleManager.h"
#include "Justification.h"

TextBox::TextBox (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int selectedForeColor, int selectedBackColor, bool multiline)
: Window(name, y, x, height, width, foreColor, backColor, foreColor, backColor, foreColor, backColor, false),
mText(text), mSelectedForeColor(selectedForeColor), mSelectedBackColor(selectedBackColor), mMultiline(multiline)
{
    setFillClientArea(false);
}

void TextBox::onDrawClient () const
{
    if (isMultiline())
    {
        std::vector<ConsoleManager::LineBreakpoint> lineBreakPoints = ConsoleManager::calculateLineBreakpoints (mText, clientWidth());
        
        int i = 0;
        for (auto & breakpoint: lineBreakPoints)
        {
            std::string lineText = mText.substr(breakpoint.beginIndex, breakpoint.endIndex - breakpoint.beginIndex + 1);
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
        ConsoleManager::printMessage(*this, vertCenter, 0, clientWidth(), mText, clientForeColor(), clientBackColor(), Justification::Horizontal::left, true);
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
