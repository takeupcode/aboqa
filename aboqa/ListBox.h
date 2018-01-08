//
//  ListBox.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/24/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef ListBox_h
#define ListBox_h

#include <string>
#include <vector>

#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "Control.h"

class Button;

class ListBox : public Control, public EventSubscriber<GameManager *, const Button *>
{
public:
    using SelectionChangedEvent = EventPublisher<GameManager *, const ListBox *>;
    
    ListBox (const std::string & name, const std::vector<std::string> & items, int y, int x, int height, int width, int foreColor, int backColor, int selectionForeColor, int selectionBackColor);
    
    bool onKeyPress (GameManager * gm, int key) override;
    
    void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) override;
    
    void onDrawClient () const override;
    
    void onResize () override;
    
    int textClientWidth () const;
    
    void setMinHeight (int height) override;
    
    void setMinWidth (int width) override;
    
    int selectionForeColor () const;
    
    void setSelectionForeColor (int color);
    
    int selectionBackColor () const;
    
    void setSelectionBackColor (int color);
    
    int size () const;
    
    int selection () const;
    
    std::string text (int index) const;
    
    void setText (int index, const std::string & text);
    
    void appendItems (const std::vector<std::string> & items);
    
    void insertItems (int index, const std::vector<std::string> & items);
    
    SelectionChangedEvent * selectionChanged ();
    
private:
    void notify (GameManager * gm, const Button * button) override;
    
    void handleSelectionChange (GameManager * gm) const;
    
    void moveSelectionUp ();
    void moveSelectionDown ();
    
    void ensureSelectionIsVisible ();
    
    static const std::string windowName;
    static const std::string moveSelectionUpButtonName;
    static const std::string moveSelectionDownButtonName;
    
    std::vector<std::string> mItems;
    std::unique_ptr<SelectionChangedEvent> mSelectionChanged;
    Button * mMoveSelectionUpButton;
    Button * mMoveSelectionDownButton;
    int mSelectionForeColor;
    int mSelectionBackColor;
    int mScrollItem;
    int mSelectionItem;
};

#endif /* ListBox_h */