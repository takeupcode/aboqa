//
//  Control.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/24/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef Control_h
#define Control_h

#include "Window.h"

class Control : public Window
{
public:
    Control (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int focusForeColor, int focusBackColor);
    
    void onDrawNonClient () const override;
};

#endif /* Control_h */
