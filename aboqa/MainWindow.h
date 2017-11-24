//
//  MainWindow.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/5/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef MainWindow_h
#define MainWindow_h

#include "Window.h"

class TextBox;
class CheckBox;

class MainWindow : public Window
{
public:
    MainWindow (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);
    
    bool onKeyPress (GameManager * gm, int key) override;
    
    void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) override;
    
    void onDrawClient () const override;
    
private:
    static const std::string windowName;
    static const std::string textBoxName;
    static const std::string checkBoxName;
    
    TextBox * mTextBox;
    CheckBox * mCheckBox;
};

#endif /* MainWindow_h */
