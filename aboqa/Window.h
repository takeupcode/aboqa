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
#include <string>

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

    bool hasBorder () const;

    void setBorder (bool border);

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
    int mClientForeColor;
    int mClientBackColor;
    int mBorderForeColor;
    int mBorderBackColor;
    bool mBorder;
};

#endif /* Window_h */
