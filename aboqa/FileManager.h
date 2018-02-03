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
#include <fstream>
#include <stdexcept>

class FileManager
{
public:
    static std::vector<char> readBytes (const std::string & fileName);
    
    static std::vector<std::string> readLines (const std::string & fileName);
    
    template <typename F, typename... Ts>
    static void processLines (const std::string & fileName, F && func, Ts &&... params)
    {
        std::ifstream fs(fileName);
        if (fs.fail())
        {
            std::string message = "Could not open ";
            message += fileName;
            throw std::runtime_error(message);
        }
        
        std::string line;
        while (getline(fs, line))
        {
            func(std::move(line), std::forward<Ts>(params)...);
        }
        
        fs.close();
    }
};

#endif /* FileManager_h */
