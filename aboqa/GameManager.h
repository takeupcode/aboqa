//
//  GameManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/26/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h

class Window;

class GameManager
{
public:
    enum class State
    {
        Exit,
        Normal
    };
    
    GameManager ();
    
    ~GameManager ();
    
    void play ();
    
    int screenWidth () const;
    
    int screenHeight () const;
    
    int minScreenWidth () const;
    
    int minScreenHeight () const;
    
    void setMinScreenDimensions (int height, int width);
    
    int maxScreenWidth () const;
    
    int maxScreenHeight () const;
    
    void setMaxScreenDimensions (int height, int width);
    
private:
    void initialize ();
    
    void deinitialize ();
    
    void loop ();
    
    void processInput ();
    
    int checkHeightBounds (int height) const;

    int checkWidthBounds (int width) const;

    State mState;
    int mScreenWidth;
    int mScreenHeight;
    int mMinScreenWidth;
    int mMinScreenHeight;
    int mMaxScreenWidth;
    int mMaxScreenHeight;
    Window * mWindow;
};

#endif /* GameManager_h */
