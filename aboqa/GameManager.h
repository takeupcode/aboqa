//
//  GameManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/26/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h

#include <chrono>
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
    using TimeClock = std::chrono::steady_clock;
    using TimePoint = TimeClock::time_point;
    using TimeResolution = std::chrono::duration<double, std::micro>;
    
    static constexpr int FramesPerSecond = 60;
    static const TimeResolution FixedFrameTime;
    
    void deinitialize ();
    
    void loop ();
    
    int checkHeightBounds (int height) const;

    int checkWidthBounds (int width) const;
    
    TimeResolution elapsed () const;
    void restartClock ();
    bool isFixedFrameReady () const;
    void completeFixedFrame ();

    int mScreenMaxX;
    int mScreenMaxY;
    int mMinScreenWidth;
    int mMinScreenHeight;
    int mMaxScreenWidth;
    int mMaxScreenHeight;
    Window * mNextWindow;
    Window * mCurrentWindow;
    std::vector<std::unique_ptr<Window>> mWindows;
    TimePoint mLastTime;
    TimeResolution mElapsed;
    TimeResolution mFixedFrameTotal;
    bool mExit;
};

#endif /* GameManager_h */
