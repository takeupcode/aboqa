//
//  MainWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef MainWindow_h
#define MainWindow_h

#include "Window.h"

class MainWindow : public Window
{
public:
    MainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    void onKeyPress (GameManager * gm, int key) const override;
    
    void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const override;
    
    void onDrawClient () const override;
};

#endif /* MainWindow_h */
