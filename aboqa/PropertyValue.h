//
//  PropertyValue.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 7/31/18.
//  Copyright © 2018 Take Up Code. All rights reserved.
//

#ifndef PropertyValue_h
#define PropertyValue_h

#include <string>

class PropertyValue
{
public:
    explicit PropertyValue (bool readOnly = false);
    
    virtual ~PropertyValue ();
    
    std::string get () const;
    
    void set (const std::string & value);
    
private:
    std::string mValue;
    bool mReadOnly;
};

#endif // PropertyValue_h
