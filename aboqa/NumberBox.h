//
//  NumberBox.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/24/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef NumberBox_h
#define NumberBox_h

#include <string>

#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "Control.h"

class Button;

class NumberBox : public Control, public EventSubscriber<GameManager *, const Button *>
{
public:
    using NumberChangedEvent = EventPublisher<GameManager *, const NumberBox *>;
    
    NumberBox (const std::string & name, int number, int y, int x, int width, int foreColor, int backColor);
    
    bool onKeyPress (GameManager * gm, int key) override;
    
    void onDrawClient () const override;
    
    int textClientWidth () const;
    
    void setMinWidth (int width) override;
    
    int number () const;
    
    void setNumber (int value);
    
    void increment ();
    
    void decrement ();
    
    NumberChangedEvent * numberChanged ();
    
private:
    void notify (GameManager * gm, const Button * button) override;
    
    void handleNumberChange (GameManager * gm) const;
    
    bool removeChar ();
    bool addChar (int key);
    
    static const std::string windowName;
    static const std::string incrementButtonName;
    static const std::string decrementButtonName;
    
    std::string mText;
    std::unique_ptr<NumberChangedEvent> mNumberChanged;
    Button * mIncrementButton;
    Button * mDecrementButton;
};

#endif /* NumberBox_h */
