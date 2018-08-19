//
//  PropertyGroup.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef PropertyGroup_h
#define PropertyGroup_h

#include <string>
#include <unordered_map>

#include "PropertyValue.h"

class PropertyGroup
{
public:
    PropertyGroup () = default;
    
    virtual ~PropertyGroup () = default;
    
    bool addValue (const std::string & valueName, const std::string & value, bool readOnly = false);
    bool addValue (const std::string & valueName, int value, bool readOnly = false);
    bool addValue (const std::string & valueName, double value, bool readOnly = false);
    bool addValue (const std::string & valueName, bool value, bool readOnly = false);

    void deleteValue (const std::string & valueName);

    PropertyValue * getValue (const std::string & valueName);
    
private:
    using ValueMap = std::unordered_map<std::string, std::unique_ptr<PropertyValue>>;
    
    ValueMap mValues;
};

#endif // PropertyGroup_h
