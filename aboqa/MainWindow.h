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
#include "../submodules/TUCUT/Curses/CheckBox.h"
#include "../submodules/TUCUT/Curses/ListBox.h"
#include "../submodules/TUCUT/Curses/NumberBox.h"
#include "../submodules/TUCUT/Curses/TextBox.h"
#include "../submodules/TUCUT/Curses/Window.h"

#include "Character.h"

class MainWindow : public TUCUT::Curses::Window, public TUCUT::Event::EventSubscriber<TUCUT::Curses::GameManager *, const TUCUT::Curses::Button *>
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
    void notify (TUCUT::Curses::GameManager * gm, const TUCUT::Curses::Button * button) override;
    
    static const std::string windowName;
    static const std::string textBoxName;
    static const std::string exitButtonName;
    
    std::shared_ptr<TUCUT::Curses::TextBox> mTextBox;
    
    Character mCharacter;
};

#endif // MainWindow_h
