//
//  CharacterSystem.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 8/12/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef CharacterSystem_h
#define CharacterSystem_h

#include <memory>
#include <unordered_map>

#include "../submodules/TUCUT/Game/GameManager.h"

class CharacterSystem : public TUCUT::Game::GameSystem
{
public:
    std::shared_ptr<CharacterSystem> getSharedCharacterSystem ();

    std::shared_ptr<TUCUT::Game::GameObject> getOrCreateCharacter (const std::string & characterName);

    void removeCharacter (const std::string & characterName);
    
private:
    friend class TUCUT::Game::GameManager;
    
    using CharacterMap = std::unordered_map<std::string, std::shared_ptr<TUCUT::Game::GameObject>>;
    
    CharacterSystem (const std::string & token, int identity);

    CharacterMap mCharacters;
};

#endif // CharacterManager_h
