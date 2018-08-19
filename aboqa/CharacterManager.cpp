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
    addCharacter("hero", Character::createSharedCharacter());
}

void CharacterManager::deinitialize ()
{
    mCharacters.clear();
}


bool CharacterManager::addCharacter (const std::string & characterName, const std::shared_ptr<Character> & character)
{
    auto result = mCharacters.try_emplace(characterName, character);
    
    return result.second;
}

void CharacterManager::removeCharacter (const std::string & characterName)
{
    mCharacters.erase(characterName);
}

std::shared_ptr<Character> CharacterManager::getCharacter (const std::string & characterName) const
{
    auto characterMapResult = mCharacters.find(characterName);
    if (characterMapResult == mCharacters.end())
    {
        return nullptr;
    }
    
    return characterMapResult->second;
}
