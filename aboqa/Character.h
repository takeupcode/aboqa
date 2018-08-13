//
//  Character.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef Character_h
#define Character_h

#include <memory>

#include "PropertyContainer.h"

class Character : public std::enable_shared_from_this<Character>
{
public:
    static std::shared_ptr<Character> createSharedCharacter ();
    
    std::shared_ptr<Character> getSharedCharacter ();
    
    virtual ~Character ();
    
    PropertyContainer & properties ();
    
protected:
    Character ();
    
    virtual void initialize ();

private:
    PropertyContainer mProperties;
};

#endif // Character_h
