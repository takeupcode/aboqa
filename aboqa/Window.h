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
    enum class VisibleState
    {
        collapsed,
        hidden,
        shown
    };

    enum class EnableState
    {
        disabled,
        readonly,
        enabled
    };

    Window (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, int focusForeColor, int focusBackColor, bool border);

    virtual ~Window ();

    WINDOW * cursesWindow () const;
    
    virtual void processInput (GameManager * gm);

    void draw () const;

    virtual bool onKeyPress (GameManager * gm, int key) const;
    
    virtual void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const;
    
    virtual void onDrawClient () const;
    
    virtual void onDrawNonClient () const;

    const std::string & name () const;
    
    virtual int y () const;
    
    virtual int clientY () const;

    virtual void setY (int y);

    virtual int x () const;
    
    virtual int clientX () const;

    virtual void setX (int x);

    virtual void move (int y, int x);

    virtual int height () const;
    
    virtual int minHeight () const;
    
    virtual int clientHeight () const;

    virtual void setHeight (int height);
    
    virtual void setMinHeight (int height);

    virtual int width () const;
    
    virtual int minWidth () const;
    
    virtual int clientWidth () const;

    virtual void setWidth (int width);
    
    virtual void setMinWidth (int width);

    virtual void resize (int height, int width);

    virtual void moveAndResize (int y, int x, int height, int width);
    
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

    virtual bool hasBorder () const;

    virtual void setBorder (bool border);
    
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
    
    virtual bool hasDirectFocus () const;
    
    virtual bool setFocus (bool focus) const;
    
    virtual bool setFocus (int y, int x) const;
    
    virtual bool advanceFocus () const;
    
    const Window * parent () const;
    
    void setParent (const Window * parent);
    
    virtual bool wantEnter () const;
    
    virtual void setWantEnter (bool value);
    
    virtual VisibleState visibleState () const;
    
    virtual void setVisibleState (VisibleState value);
    
    virtual EnableState enableState () const;
    
    virtual void setEnableState (EnableState value);

protected:
    void setFillClientArea (bool value);
    
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
    int mMinHeight;
    int mMinWidth;
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
    mutable bool mHasFocus;
    mutable bool mHasDirectFocus;
    bool mFillClientArea;
    bool mWantEnter;
    VisibleState mVisibleState;
    EnableState mEnableState;
};

#endif /* Window_h */
