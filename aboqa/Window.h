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
    Window (const std::string & name, int y, int x, int height, int width, int clientForeColor, int clientBackColor, int borderForeColor, int borderBackColor, bool border);

    virtual ~Window ();

    WINDOW * cursesWindow () const;
    
    virtual void processInput (GameManager * gm);

    void draw () const;

    virtual void onKeyPress (GameManager * gm, int key) const;
    
    virtual void onMouseEvent (GameManager * gm, short id, int y, int x, mmask_t buttonState) const;
    
    virtual void onDrawClient () const;

    const std::string & name () const;
    
    int y () const;

    void setY (int y);

    int x () const;

    void setX (int x);

    void move (int y, int x);

    int height () const;

    void setHeight (int height);

    int width () const;

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
    
    void addControl(std::unique_ptr<Window> && control);

private:
    void createWindows ();
    void destroyWindows ();

    WINDOW * mClientWindowPtr;
    WINDOW * mBorderWindowPtr;
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
    std::vector<std::unique_ptr<Window>> mControls;
    bool mBorder;
};

#endif /* Window_h */
