//
//  PropertyContainer.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#include "PropertyContainer.h"
#include "PropertyGroup.h"

PropertyContainer::PropertyContainer ()
{ }

PropertyContainer::~PropertyContainer ()
{ }

PropertyValue & PropertyContainer::value (const std::string & group, const std::string & name)
{
    return mDefaultValue;
}
