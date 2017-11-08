//
//  Window.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/1/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef Window_h
#define Window_h

#include <curses.h>
#include <memory>
#include <string>
#include <vector>

class GameManager;

class Window
{
public:
    Window (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border, int focusForeColor, int focusBackColor);

    virtual ~Window ();

    WINDOW * cursesWindow () const;
    
    virtual void processInput (GameManager * gm);

    void draw () const;

    virtual bool onKeyPress (GameManager * gm, int key) const;
    
    virtual void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const;
    
    virtual void onDrawClient () const;

    const std::string & name () const;
    
    int y () const;
    
    int clientY () const;

    void setY (int y);

    int x () const;
    
    int clientX () const;

    void setX (int x);

    void move (int y, int x);

    int height () const;
    
    int clientHeight () const;

    void setHeight (int height);

    int width () const;
    
    int clientWidth () const;

    void setWidth (int width);

    void resize (int height, int width);

    void moveAndResize (int y, int x, int height, int width);
    
    int anchorTop () const;
    
    void setAnchorTop (int anchor);
    
    int anchorBottom () const;
    
    void setAnchorBottom (int anchor);
    
    int anchorLeft () const;
    
    void setAnchorLeft (int anchor);
    
    int anchorRight () const;
    
    void setAnchorRight (int anchor);
    
    void setAnchorsAll (int anchor);
    
    void setAnchorsAll (int top, int bottom, int left, int right);
    
    void setAnchorsTopBottom (int top, int bottom);
    
    void setAnchorsLeftRight (int left, int right);

    bool hasBorder () const;

    void setBorder (bool border);
    
    int clientForeColor () const;
    
    void setClientForeColor (int color);
    
    int clientBackColor () const;
    
    void setClientBackColor (int color);
    
    int borderForeColor () const;
    
    void setBorderForeColor (int color);
    
    int borderBackColor () const;
    
    void setBorderBackColor (int color);
    
    int focusForeColor () const;
    
    void setFocusForeColor (int color);
    
    int focusBackColor () const;
    
    void setFocusBackColor (int color);
    
    void addControl(std::unique_ptr<Window> && control);
    
    const Window * findWindow (int y, int x) const;
    
    const Window * findFocus () const;
    
    virtual bool canHaveDirectFocus () const;
    
    bool hasDirectFocus () const;
    
    bool setFocus (bool focus);
    
    bool setFocus (int y, int x);
    
    bool advanceFocus ();
    
    const Window * parent () const;
    
    void setParent (const Window * parent);

protected:
    void setFillClientArea (bool value);
    
private:
    void createWindows ();
    
    void destroyWindows ();
    
    void anchorWindow (Window * win);
    
    void drawBorder () const;

    WINDOW * mClientCursesWindow;
    std::unique_ptr<Window> mBorderWindow;
    std::string mName;
    int mY;
    int mX;
    int mHeight;
    int mWidth;
    int mAnchorTop;
    int mAnchorBottom;
    int mAnchorLeft;
    int mAnchorRight;
    int mClientForeColor;
    int mClientBackColor;
    int mBorderForeColor;
    int mBorderBackColor;
    int mFocusForeColor;
    int mFocusBackColor;
    std::vector<std::unique_ptr<Window>> mControls;
    const Window * mParent;
    bool mBorder;
    bool mHasFocus;
    bool mHasDirectFocus;
    bool mFillClientArea;
};

#endif /* Window_h */
