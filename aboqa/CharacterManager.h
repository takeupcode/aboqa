//
//  CharacterManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 8/12/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef CharacterManager_h
#define CharacterManager_h

#include <memory>

class Character;

class CharacterManager
{
public:
    static CharacterManager * instance ();
    
    void initialize ();
    
    void deinitialize ();
    
    Character * getHero ();
    
private:
    CharacterManager ();
    
    std::shared_ptr<Character> mHero;
};

#endif // CharacterManager_h
