//
//  GameManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/26/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h

#include <memory>
#include <string>
#include <vector>

class Window;

class GameManager
{
public:
    GameManager ();
    
    ~GameManager ();
    
    void initialize ();
    
    void play ();
    
    void exit ();
    
    void addWindow(std::unique_ptr<Window> && window);
    
    void selectNextWindow(const std::string & name);
    
    int screenWidth () const;
    
    int screenHeight () const;
    
    int minScreenWidth () const;
    
    int minScreenHeight () const;
    
    void setMinScreenDimensions (int height, int width);
    
    int maxScreenWidth () const;
    
    int maxScreenHeight () const;
    
    void setMaxScreenDimensions (int height, int width);
    
private:
    void deinitialize ();
    
    void loop ();
    
    int checkHeightBounds (int height) const;

    int checkWidthBounds (int width) const;

    int mScreenWidth;
    int mScreenHeight;
    int mMinScreenWidth;
    int mMinScreenHeight;
    int mMaxScreenWidth;
    int mMaxScreenHeight;
    Window * mNextWindow;
    Window * mCurrentWindow;
    std::vector<std::unique_ptr<Window>> mWindows;
    bool mExit;
};

#endif /* GameManager_h */
