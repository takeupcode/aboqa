//
//  Character.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#include "Character.h"

Character::Character ()
{ }

void Character::initialize ()
{
}

std::shared_ptr<Character> Character::createSharedCharacter ()
{
    auto result = std::shared_ptr<Character>(new Character());
    
    result->initialize();
    
    return result;
}

std::shared_ptr<Character> Character::getSharedCharacter ()
{
    return shared_from_this();
}

Character::~Character ()
{ }

PropertyContainer & Character::properties ()
{
    return mProperties;
}
