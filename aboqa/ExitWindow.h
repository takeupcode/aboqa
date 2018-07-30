//
//  ExitWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef ExitWindow_h
#define ExitWindow_h

#include "../submodules/TUCUT/Event/EventSubscriber.h"
#include "../submodules/TUCUT/Curses/Button.h"
#include "../submodules/TUCUT/Curses/Window.h"

class ExitWindow : public TUCUT::Curses::Window, public TUCUT::Event::EventSubscriber<TUCUT::Curses::GameManager *, const TUCUT::Curses::Button *>
{
public:
    static std::shared_ptr<ExitWindow> createSharedExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    std::shared_ptr<ExitWindow> getSharedExitWindow ();
    
    bool onKeyPress (TUCUT::Curses::GameManager * gm, int key) override;
    
protected:
    ExitWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    void initialize () override;

private:
    void notify (TUCUT::Curses::GameManager * gm, const TUCUT::Curses::Button * button) override;
    
    static const std::string windowName;
    static const std::string exitButtonName;
    static const std::string thanksLabelName;
};

#endif /* ExitWindow_h */
