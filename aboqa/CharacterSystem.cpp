//
//  CharacterSystem.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 8/12/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#include "CharacterSystem.h"
#include "../submodules/TUCUT/Game/PositionComponent.h"
#include "../submodules/TUCUT/Game/MovementComponent.h"

#include <stdexcept>

const std::string CharacterSystem::defaultToken = "CharacterSystem";

std::shared_ptr<CharacterSystem> CharacterSystem::getSharedCharacterSystem ()
{
    return std::static_pointer_cast<CharacterSystem>(shared_from_this());
}

CharacterSystem::CharacterSystem (const std::string & token, int identity)
: GameSystem(token, identity)
{ }

std::shared_ptr<TUCUT::Game::GameObject> CharacterSystem::getOrCreateCharacter (const std::string & characterName)
{
    auto characterMapResult = mCharacters.find(characterName);
    if (characterMapResult == mCharacters.end())
    {
        TUCUT::Game::GameManager * pGameMgr = TUCUT::Game::GameManager::instance();
        
        auto gameObj = pGameMgr->createGameObject<TUCUT::Game::GameObject>();

        auto result = mCharacters.try_emplace(characterName, gameObj);
        if (!result.second)
        {
            throw std::runtime_error("Unable to create game object");
        }

        auto positionComp = pGameMgr->getOrCreateGameComponent<TUCUT::Game::PositionComponent>();
        positionComp->setMaxPosition({29, 29, 9});
        gameObj->addGameComponent(positionComp);

        auto movementComp = pGameMgr->getOrCreateGameComponent<TUCUT::Game::MovementComponent>();
        gameObj->addGameComponent(movementComp);
        movementComp->setFloating(gameObj, TUCUT::Game::IMovementComponent::xVelocityMax, 1.0);
        movementComp->setFloating(gameObj, TUCUT::Game::IMovementComponent::yVelocityMax, 1.0);

        return gameObj;
    }
    
    return characterMapResult->second;
}

void CharacterSystem::removeCharacter (const std::string & characterName)
{
    auto characterMapResult = mCharacters.find(characterName);
    if (characterMapResult != mCharacters.end())
    {
        TUCUT::Game::GameManager * pGameMgr = TUCUT::Game::GameManager::instance();
        
        pGameMgr->removeGameObject(characterMapResult->second->identity());
        
        mCharacters.erase(characterName);
    }
}
