//
//  SplashWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef SplashWindow_h
#define SplashWindow_h

#include "EventSubscriber.h"
#include "Window.h"

class Button;

class SplashWindow : public Window, public EventSubscriber<GameManager *, const Button *>
{
public:
    SplashWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    bool onKeyPress (GameManager * gm, int key) const override;
    
    void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const override;
    
    void onDrawClient () const override;
    
    bool canHaveDirectFocus () const override;

private:
    void notify (GameManager * gm, const Button * button) override;
    
    static const std::string windowName;
    static const std::string playButtonName;
    static const std::string exitButtonName;
};

#endif /* SplashWindow_h */
