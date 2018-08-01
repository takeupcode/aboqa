//
//  Character.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef Character_h
#define Character_h

#include "PropertyContainer.h"

class Character
{
public:
    Character ();
    
    virtual ~Character ();
    
    PropertyContainer & properties ();
    
private:
    PropertyContainer mProperties;
};

#endif // Character_h
