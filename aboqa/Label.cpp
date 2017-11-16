//
//  Label.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/11/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "Label.h"

#include "ConsoleManager.h"

Label::Label (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, bool multiline)
: Window(name, y, x, height, width, foreColor, backColor, foreColor, backColor, false, foreColor, backColor),
  mText(text), mMultiline(multiline)
{
    setFillClientArea(false);
}

void Label::onDrawClient () const
{
    if (isMultiline())
    {
        std::vector<ConsoleManager::LineBreakpoint> lineBreakPoints = ConsoleManager::calculateLineBreakpoints (mText, clientWidth());
        int margin = (clientHeight() - static_cast<int>(lineBreakPoints.size())) / 2;
        if (margin < 0)
        {
            margin = 0;
        }
        
        int i = 0;
        for (; i < margin; ++i)
        {
            ConsoleManager::printMessage(*this, i, 0, clientWidth(), " ", clientForeColor(), clientBackColor(), false, true);
        }
        for (auto & breakpoint: lineBreakPoints)
        {
            std::string lineText = mText.substr(breakpoint.beginIndex, breakpoint.endIndex - breakpoint.beginIndex + 1);
            ConsoleManager::printMessage(*this, i, 0, clientWidth(), lineText, clientForeColor(), clientBackColor(), false, true);
            ++i;
        }
        for (; i < clientHeight(); ++i)
        {
            ConsoleManager::printMessage(*this, i, 0, clientWidth(), " ", clientForeColor(), clientBackColor(), false, true);
        }
    }
    else
    {
        int vertCenter = clientHeight() / 2;
        ConsoleManager::printMessage(*this, vertCenter, 0, clientWidth(), mText, clientForeColor(), clientBackColor(), true, true);
    }
}

bool Label::canHaveDirectFocus () const
{
    return false;
}

bool Label::isMultiline () const
{
    return mMultiline;
}

void Label::setMultiline (bool multiline)
{
    mMultiline = multiline;
}
