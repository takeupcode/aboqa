//
//  ExitWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef ExitWindow_h
#define ExitWindow_h

#include "Window.h"

class ExitWindow : public Window
{
public:
    ExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    void processInput (GameManager * gm) override;
    
    void onDrawClient () const override;
};

#endif /* ExitWindow_h */
