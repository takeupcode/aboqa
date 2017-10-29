//
//  LogManager.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/28/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "LogManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

#include "ConsoleManager.h"

using namespace std;

LogManager * LogManager::mInstance = nullptr;

LogManager::LogManager (const std::string & logFileName)
: mLogFileName(logFileName)
{ }

void LogManager::initialize (const std::string & logFileName)
{
    if (mInstance)
    {
        throw logic_error("LogManager is already initialized.");
    }
    
    mInstance = new LogManager(logFileName);
}

void LogManager::deinitialize ()
{
    if (!mInstance)
    {
        throw logic_error("LogManager must be initialized.");
    }
    
    delete mInstance;
    mInstance = nullptr;
}

LogManager * LogManager::instance ()
{
    if (!mInstance)
    {
        throw logic_error("LogManager must be initialized.");
    }

    return mInstance;
}

void LogManager::logDebug(const std::string & message) const
{
    ofstream fs = open();
    
    fs << time() << " debug=\"true\" message=\"" << message << "\"\n";
    
    close (fs);
}

void LogManager::logInfo(const std::string & message) const
{
    ofstream fs = open();
    
    fs << time() << " info=\"true\" message=\"" << message << "\"\n";
    
    close (fs);
}

void LogManager::logFatal(const std::string & message) const
{
    ofstream fs = open();
    
    fs << time() << " fatal=\"true\" message=\"" << message << "\"\n";
    
    close (fs);
    
    cout << message << endl;
    
    ConsoleManager::promptPause();
    
    exit(1);
}

ofstream LogManager::open () const
{
    ofstream fs(mLogFileName, ios_base::app);
    if (fs.fail())
    {
        string message = "Could not open ";
        message += mLogFileName;
        throw runtime_error(message);
    }
    
    return fs;
}

void LogManager::close (ofstream & fs) const
{
    fs.close();
}

string LogManager::time () const
{
    auto timeNow = chrono::system_clock::now();
    
    auto timeSinceEpoch = timeNow.time_since_epoch();
    auto secondsSinceEpoch = chrono::duration_cast<chrono::seconds>(timeSinceEpoch);
    auto fraction = timeSinceEpoch - secondsSinceEpoch;
    auto milli = chrono::duration_cast<chrono::milliseconds>(fraction);
    
    auto timetNow = chrono::system_clock::to_time_t(timeNow);
    
    char dtBuffer[30];
    strftime(dtBuffer, sizeof(dtBuffer), "%Y-%m-%dT%H:%M:%S:", localtime(&timetNow));
    
    stringstream ss;
    ss << dtBuffer << std::setfill('0') << std::setw(3) << milli.count();
    return ss.str();
}
