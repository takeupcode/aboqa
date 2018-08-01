//
//  PropertyValue.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#include "PropertyValue.h"

PropertyValue::PropertyValue (bool readOnly)
: mValue("0"), mReadOnly(readOnly)
{ }

PropertyValue::~PropertyValue ()
{ }

std::string PropertyValue::get () const
{
    return mValue;
}

void PropertyValue::set (const std::string & value)
{
    if (mReadOnly)
    {
        return;
    }
    
    mValue = value;
}
