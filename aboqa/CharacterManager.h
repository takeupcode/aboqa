//
//  CharacterManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 8/12/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef CharacterManager_h
#define CharacterManager_h

#include <memory>
#include <unordered_map>

#include "Character.h"

class CharacterManager
{
public:
    static CharacterManager * instance ();
    
    void initialize ();
    
    void deinitialize ();
    
    bool addCharacter (const std::string & characterName, const std::shared_ptr<Character> & character);
    
    void removeCharacter (const std::string & characterName);

    std::shared_ptr<Character> getCharacter (const std::string & characterName) const;
    
private:
    using CharacterMap = std::unordered_map<std::string, std::shared_ptr<Character>>;
    
    CharacterManager ();
    
    CharacterMap mCharacters;
};

#endif // CharacterManager_h
