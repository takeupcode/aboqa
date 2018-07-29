//
//  ExitWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef ExitWindow_h
#define ExitWindow_h

#include "../submodules/TUCUT/Curses/Window.h"

class ExitWindow : public TUCUT::Curses::Window
{
public:
    static std::shared_ptr<ExitWindow> createSharedExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    std::shared_ptr<ExitWindow> getSharedExitWindow ();
    
    bool onKeyPress (TUCUT::Curses::GameManager * gm, int key) override;
    
    void onMouseEvent (TUCUT::Curses::GameManager * gm, short id, int y, int x, mmask_t buttonState) override;
    
    void onDrawClient () const override;
    
protected:
    ExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    void initialize () override;
};

#endif /* ExitWindow_h */
