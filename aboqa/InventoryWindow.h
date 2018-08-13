//
//  InventoryWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 8/12/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef InventoryWindow_h
#define InventoryWindow_h

#include "../submodules/TUCUT/Event/EventSubscriber.h"
#include "../submodules/TUCUT/Curses/Button.h"
#include "../submodules/TUCUT/Curses/Window.h"

class InventoryWindow : public TUCUT::Curses::Window, public TUCUT::Event::EventSubscriber<TUCUT::Curses::GameManager *, TUCUT::Curses::Button *>
{
public:
    static std::shared_ptr<InventoryWindow> createSharedInventoryWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    std::shared_ptr<InventoryWindow> getSharedInventoryWindow ();
    
    bool onKeyPress (TUCUT::Curses::GameManager * gm, int key) override;
    
protected:
    InventoryWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    void initialize () override;
    
private:
    void notify (int id, TUCUT::Curses::GameManager * gm, TUCUT::Curses::Button * button) override;
    
    static const std::string windowName;
    static const std::string exitButtonName;
};

#endif // InventoryWindow_h
