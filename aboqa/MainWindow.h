//
//  MainWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef MainWindow_h
#define MainWindow_h

#include "../submodules/TUCUT/Event/EventSubscriber.h"
#include "../submodules/TUCUT/Curses/Button.h"
#include "../submodules/TUCUT/Curses/DisplayBox.h"
#include "../submodules/TUCUT/Curses/Label.h"
#include "../submodules/TUCUT/Curses/Window.h"

#include "Character.h"

class MainWindow : public TUCUT::Curses::Window, public TUCUT::Event::EventSubscriber<TUCUT::Curses::GameManager *, TUCUT::Curses::Button *>,
    public TUCUT::Event::EventSubscriber<TUCUT::Curses::GameManager *, TUCUT::Curses::DisplayBox *, int, int, bool &>,
    public TUCUT::Event::EventSubscriber<TUCUT::Curses::GameManager *, TUCUT::Curses::DisplayBox *, int, int>
{
public:
    static std::shared_ptr<MainWindow> createSharedMainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    std::shared_ptr<MainWindow> getSharedMainWindow ();
    
    bool onKeyPress (TUCUT::Curses::GameManager * gm, int key) override;

    void onMouseEvent (TUCUT::Curses::GameManager * gm, short id, int y, int x, mmask_t buttonState) override;
    
protected:
    MainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    void initialize () override;

private:
    void notify (int id, TUCUT::Curses::GameManager * gm, TUCUT::Curses::Button * button) override;
    
    void notify (int id, TUCUT::Curses::GameManager * gm, TUCUT::Curses::DisplayBox * display, int y, int x, bool & cancel) override;
    
    void notify (int id, TUCUT::Curses::GameManager * gm, TUCUT::Curses::DisplayBox * display, int y, int x) override;

    static const std::string windowName;
    static const std::string displayBoxName;
    static const std::string statusName;
    static const std::string exitButtonName;
    
    std::shared_ptr<TUCUT::Curses::DisplayBox> mDisplayBox;
    std::shared_ptr<TUCUT::Curses::Label> mStatus;
    std::shared_ptr<TUCUT::Curses::Button> mExitButton;

    Character mCharacter;
};

#endif // MainWindow_h
