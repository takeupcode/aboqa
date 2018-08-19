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

#include "PropertyGroup.h"

class PropertyContainer
{
public:
    PropertyContainer () = default;
    
    virtual ~PropertyContainer () = default;
    
    PropertyGroup * addGroup (const std::string & groupName);
    
    void deleteGroup (const std::string & groupName);

    PropertyGroup * getGroup (const std::string & groupName);

    PropertyValue * getValue (const std::string & groupName, const std::string & valueName);
    
private:
    using GroupMap = std::unordered_map<std::string, std::unique_ptr<PropertyGroup>>;
    
    GroupMap mGroups;
};

#endif // PropertyContainer_h
