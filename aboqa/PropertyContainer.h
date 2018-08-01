//
//  PropertyContainer.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef PropertyContainer_h
#define PropertyContainer_h

#include <string>
#include <unordered_map>

#include "PropertyValue.h"

class PropertyGroup;

class PropertyContainer
{
public:
    PropertyContainer ();
    
    virtual ~PropertyContainer ();
    
    PropertyValue & value (const std::string & group, const std::string & name);
    
private:
    using GroupMap = std::unordered_map<std::string, std::unique_ptr<PropertyGroup>>;
    
    GroupMap mGroups;
    PropertyValue mDefaultValue;
};

#endif // PropertyContainer_h
