//
//  SplashWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef SplashWindow_h
#define SplashWindow_h

#include "../submodules/TUCUT/Event/EventSubscriber.h"
#include "../submodules/TUCUT/Curses/Button.h"
#include "../submodules/TUCUT/Curses/Window.h"

class SplashWindow : public TUCUT::Curses::Window, public TUCUT::Event::EventSubscriber<TUCUT::Curses::GameManager *, const TUCUT::Curses::Button *>
{
public:
    static std::shared_ptr<SplashWindow> createSharedSplashWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    std::shared_ptr<SplashWindow> getSharedSplashWindow ();
    
    bool onKeyPress (TUCUT::Curses::GameManager * gm, int key) override;
    
    void onMouseEvent (TUCUT::Curses::GameManager * gm, short id, int y, int x, mmask_t buttonState) override;
    
    void onDrawClient () const override;
    
protected:
    SplashWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    void initialize () override;

private:
    void notify (TUCUT::Curses::GameManager * gm, const TUCUT::Curses::Button * button) override;
    
    static const std::string windowName;
    static const std::string playButtonName;
    static const std::string exitButtonName;
    static const std::string introLabelName;
};

#endif /* SplashWindow_h */
