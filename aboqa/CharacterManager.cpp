//
//  CharacterManager.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 8/12/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#include "CharacterManager.h"
#include "Character.h"

CharacterManager::CharacterManager ()
{ }

CharacterManager * CharacterManager::instance ()
{
    static CharacterManager * mInstance = nullptr;
    
    if (!mInstance)
    {
        mInstance = new CharacterManager();
    }
    
    return mInstance;
}

void CharacterManager::initialize ()
{
    mHero = Character::createSharedCharacter();
}

void CharacterManager::deinitialize ()
{
    mHero.reset();
}

Character * CharacterManager::getHero ()
{
    return mHero.get();
}
