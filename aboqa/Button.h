//
//  Button.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef Button_h
#define Button_h

#include "Window.h"

class Button : public Window
{
public:
    Button (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor);
    
    void onKeyPress (GameManager * gm, int key) const override;
    
    void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const override;
    
    void onDrawClient () const override;
    
    void handleClick () const;
    
private:
    std::string mText;
};

#endif /* Button_h */
