//
//  Character.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#include "Character.h"

const std::string Character::LocationPropertyGroup = "location";
const std::string Character::XPropertyValue = "x";
const std::string Character::YPropertyValue = "y";

Character::Character ()
{ }

void Character::initialize ()
{
    auto group = mProperties.addGroup(LocationPropertyGroup);
    group->addValue(XPropertyValue, 0);
    group->addValue(YPropertyValue, 0);
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
