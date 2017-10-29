//
//  GameManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/26/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h

class GameManager
{
public:
    enum class State
    {
        Exit,
        Normal
    };
    
    void play ();
    
private:
    void initialize ();
    
    void deinitialize ();
    
    void loop ();
    
    void processInput ();
    
    State mState;
    int mScreenWidth;
    int mScreenHeight;
};

#endif /* GameManager_h */
