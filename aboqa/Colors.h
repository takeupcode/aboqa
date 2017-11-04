//
//  Colors.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/2/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef Colors_h
#define Colors_h

class Colors
{
public:
    static constexpr bool useBrightColors = true;
    static constexpr int basicColorCount = 8;
    static constexpr int colorCount = useBrightColors ? basicColorCount * 2 : basicColorCount;

    static constexpr int COLOR_DIM_BLACK        = 0;
    static constexpr int COLOR_DIM_RED          = 1;
    static constexpr int COLOR_DIM_GREEN        = 2;
    static constexpr int COLOR_DIM_YELLOW       = 3;
    static constexpr int COLOR_DIM_BLUE         = 4;
    static constexpr int COLOR_DIM_MAGENTA      = 5;
    static constexpr int COLOR_DIM_CYAN         = 6;
    static constexpr int COLOR_DIM_WHITE        = 7;
    static constexpr int COLOR_BRIGHT_BLACK     = 8;
    static constexpr int COLOR_BRIGHT_RED       = 9;
    static constexpr int COLOR_BRIGHT_GREEN     = 10;
    static constexpr int COLOR_BRIGHT_YELLOW    = 11;
    static constexpr int COLOR_BRIGHT_BLUE      = 12;
    static constexpr int COLOR_BRIGHT_MAGENTA   = 13;
    static constexpr int COLOR_BRIGHT_CYAN      = 14;
    static constexpr int COLOR_BRIGHT_WHITE     = 15;

    static void initializeColorPairs();
    
    static int colorPairIndex (int foreColor, int backColor);
};

#endif /* Colors_h */
