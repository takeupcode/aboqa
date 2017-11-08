//
//  CursesUtil.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/7/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "CursesUtil.h"

#include <curses.h>

void CursesUtil::getScreenMaxYX (int & y, int & x)
{
    getmaxyx(stdscr, y, x);
    // For some reason, these values come back too big.
    --y;
    --x;
}
