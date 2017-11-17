//
//  Justification.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/16/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef Justification_h
#define Justification_h

struct Justification
{
    enum class Horizontal
    {
        left,
        center,
        right
    };
    
    enum class Vertical
    {
        top,
        center,
        bottom
    };
};

#endif /* Justification_h */
