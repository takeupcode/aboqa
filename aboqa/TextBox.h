//
//  TextBox.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/18/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef TextBox_h
#define TextBox_h

#include <string>

#include "Window.h"

class TextBox : public Window
{
public:
    TextBox (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int selectedForeColor, int selectedBackColor, bool multiline = false);
    
    void onDrawClient () const override;
    
    int selectedForeColor () const;
    
    void setSelectedForeColor (int color);
    
    int selectedBackColor () const;
    
    void setSelectedBackColor (int color);
    
    bool isMultiline () const;
    
    void setMultiline (bool multiline);
    
    std::string text () const;
    
    std::string selectedText () const;
    
    void setText (const std::string & text);
    
    void appendText (const std::string & text);
    
    void insertText (const std::string & text);
    
private:
    std::string mText;
    int mSelectedForeColor;
    int mSelectedBackColor;
    bool mMultiline;
};

#endif /* TextBox_h */
