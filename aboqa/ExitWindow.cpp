//
//  ExitWindow.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "ExitWindow.h"

#include "GameManager.h"
#include "LogManager.h"

ExitWindow::ExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border)
: Window(name, y, x, height, width, clientForeColor, clientBackColor, borderForeColor, borderBackColor, border)
{ }

void ExitWindow::processInput (GameManager * gm)
{
    int c = wgetch(cursesWindow());
    switch(c)
    {
        case ERR:
            break;
        case KEY_DOWN:
            LogManager::instance()->logInfo("Down key pressed from exit window.");
            break;
        case KEY_UP:
            break;
        case 10: /* Enter */
            break;
        case KEY_F(1):
            gm->exit();
            break;
    }
}

void ExitWindow::onDrawClient () const
{
    
}
