//
//  Button.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef Button_h
#define Button_h

#include <memory>

#include "EventPublisher.h"
#include "Control.h"

class Button : public Control
{
public:
    using ClickedEvent = EventPublisher<GameManager *, const Button *>;

    Button (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int focusForeColor, int focusBackColor);
    
    bool onKeyPress (GameManager * gm, int key) override;
    
    void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) override;
    
    void onDrawClient () const override;
    
    ClickedEvent * clicked ();

private:
    void handleClick (GameManager * gm) const;
    
    std::string mText;
    std::unique_ptr<ClickedEvent> mClicked;
};

#endif /* Button_h */
