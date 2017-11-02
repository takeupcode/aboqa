//
//  FileManager.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/24/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "FileManager.h"

#include <fstream>
#include <stdexcept>

using namespace std;

vector<char> FileManager::readBytes (string & fileName)
{
    ifstream fs(fileName, ios_base::binary);
    if (fs.fail())
    {
        string message = "Could not open ";
        message += fileName;
        throw runtime_error(message);
    }
    
    fs.seekg(ios::end);
    auto length = fs.tellg();
    
    vector<char> content;
    content.reserve(length);
    
    fs.seekg(ios::beg);
    fs.read(&content[0], length);
    
    fs.close();
    
    return content;
}

vector<string> FileManager::readLines (string & fileName)
{
    ifstream fs(fileName);
    if (fs.fail())
    {
        string message = "Could not open ";
        message += fileName;
        throw runtime_error(message);
    }
    
    vector<string> content;
    
    string line;
    while (getline(fs, line))
    {
        content.push_back(move(line));
    }
    
    fs.close();
    
    return content;
}
