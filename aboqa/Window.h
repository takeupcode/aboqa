//
//  Window.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 11/1/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef Window_h
#define Window_h

class Window
{
public:
    Window (int y, int x, int height, int width, bool border);
    
    virtual ~Window ();
    
    virtual void draw () const;
    
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
    
    bool hasBorder () const;
    
    void setBorder (bool border);
    
private:
    int mY;
    int mX;
    int mHeight;
    int mWidth;
    bool mBorder;
};

#endif /* Window_h */
