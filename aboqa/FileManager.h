//
//  FileManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/24/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef FileManager_h
#define FileManager_h

#include <string>
#include <vector>

class FileManager
{
public:
    static std::vector<char> readBytes (std::string & fileName);
    
    static std::vector<std::string> readLines (std::string & fileName);
};

#endif /* FileManager_h */
