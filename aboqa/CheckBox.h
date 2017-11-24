//
//  CheckBox.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/24/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef CheckBox_h
#define CheckBox_h

#include <memory>

#include "EventPublisher.h"
#include "Control.h"

class CheckBox : public Control
{
public:
    using ClickedEvent = EventPublisher<GameManager *, const CheckBox *>;
    
    CheckBox (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int focusForeColor, int focusBackColor);
    
    bool onKeyPress (GameManager * gm, int key) override;
    
    void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) override;
    
    void onDrawClient () const override;
    
    virtual bool isChecked () const;
    
    virtual void setIsChecked (bool value);
    
    ClickedEvent * clicked ();
    
private:
    void handleClick (GameManager * gm);
    
    std::string mText;
    std::unique_ptr<ClickedEvent> mClicked;
    bool mIsChecked;
};

#endif /* CheckBox_h */
