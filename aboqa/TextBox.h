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
#include <vector>

#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "Window.h"

class Button;

class TextBox : public Window, public EventSubscriber<GameManager *, const Button *>
{
public:
    using TextChangedEvent = EventPublisher<GameManager *, const TextBox *>;
    using SelectionChangedEvent = EventPublisher<GameManager *, const TextBox *>;
    
    TextBox (const std::string & name, const std::string & text, int y, int x, int height, int width, int foreColor, int backColor, int selectedForeColor, int selectedBackColor, bool multiline = false);
    
    bool onKeyPress (GameManager * gm, int key) override;
    
    void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) override;
    
    void onDrawClient () const override;
    
    void onDrawNonClient () const override;
    
    int textClientWidth () const;
    
    void setMinHeight (int height) override;
    
    void setMinWidth (int width) override;
    
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
    
    TextChangedEvent * textChanged ();
    
    SelectionChangedEvent * selectionChanged ();
    
private:
    void notify (GameManager * gm, const Button * button) override;
    
    void moveCursorUp ();
    void moveCursorDown ();
    void moveCursorLeft ();
    void moveCursorRight ();
    
    static const std::string windowName;
    static const std::string moveCursorUpButtonName;
    static const std::string moveCursorDownButtonName;
    static const std::string moveCursorLeftButtonName;
    static const std::string moveCursorRightButtonName;
    
    std::vector<std::string> mText;
    std::unique_ptr<TextChangedEvent> mTextChanged;
    std::unique_ptr<SelectionChangedEvent> mSelectionChanged;
    Button * mMoveCursorUpButton;
    Button * mMoveCursorDownButton;
    Button * mMoveCursorLeftButton;
    Button * mMoveCursorRightButton;
    int mSelectedForeColor;
    int mSelectedBackColor;
    int mScrollY;
    int mScrollX;
    int mCursorY;
    int mCursorX;
    bool mMultiline;
};

#endif /* TextBox_h */
