//
//  Colors.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/2/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "Colors.h"

#include <curses.h>

void Colors::initializeColorPairs()
{
    use_default_colors();
    
    if (can_change_color())
    {
        // Initialize as many color pairs as possible
        for (int foreColor = 0; foreColor < colorCount; ++foreColor)
        {
            for (int backColor = 0; backColor < colorCount; ++backColor)
            {
                int i = (foreColor * colorCount) + backColor + 1;
                if (i >= COLOR_PAIRS)
                {
                    // Stop initializing pairs if we reach the limit.
                    return;
                }
                init_pair(i, foreColor, backColor);
            }
        }
    }
}

int Colors::colorPairIndex (int foreColor, int backColor)
{
    int i = (foreColor * colorCount) + backColor + 1;
    if (i >= COLOR_PAIRS)
    {
        // Use the default color pair if we exceed the max.
        i = 0;
    }
    
    return i;
}
