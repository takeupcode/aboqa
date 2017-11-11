//
//  Label.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/11/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef Label_h
#define Label_h

#include "Window.h"

class Label : public Window
{
public:
    Label (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor);
    
    void onDrawClient () const override;
    
    bool canHaveDirectFocus () const override;
    
private:
    std::string mText;
};

#endif /* Label_h */
