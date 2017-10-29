//
//  LogManager.h
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/28/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#ifndef LogManager_h
#define LogManager_h

#include <string>

class LogManager
{
public:
    static void initialize (const std::string & logFileName);
    
    static void deinitialize ();
    
    static LogManager * instance ();
    
    void logDebug(const std::string & message) const;
    
    void logInfo(const std::string & message) const;
    
    void logFatal(const std::string & message) const;
    
private:
    LogManager (const std::string & logFileName);
    
    std::ofstream open () const;
    
    void close (std::ofstream & fs) const;
    
    std::string time () const;
    
    static LogManager * mInstance;
    std::string mLogFileName;
};

#endif /* LogManager_h */
