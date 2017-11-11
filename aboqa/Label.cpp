//
//  Label.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/11/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "Label.h"

#include "ConsoleManager.h"

Label::Label (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor)
: Window(name, y, x, height, width, foreColor, backColor, foreColor, backColor, false, foreColor, backColor),
  mText(text)
{
    setFillClientArea(false);
}

void Label::onDrawClient () const
{
    int vertCenter = height() / 2;
    ConsoleManager::printMessage(*this, vertCenter, 0, width(), mText, clientForeColor(), clientBackColor(), true, true);
}

bool Label::canHaveDirectFocus () const
{
    return false;
}
