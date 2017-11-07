//
//  GameManager.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/26/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "GameManager.h"

#include <curses.h>

#include "Colors.h"
#include "LogManager.h"
#include "ConsoleManager.h"
#include "Window.h"

using namespace std;

GameManager::GameManager ()
: mScreenMaxX(0), mScreenMaxY(0),
  mMinScreenWidth(0), mMinScreenHeight(0), mMaxScreenWidth(80), mMaxScreenHeight(40),
  mNextWindow(nullptr), mCurrentWindow(nullptr), mExit(false)
{ }

GameManager::~GameManager ()
{
    deinitialize();
}

void GameManager::play ()
{
    loop();
}

void GameManager::exit ()
{
    mExit = true;
}

void GameManager::addWindow(std::unique_ptr<Window> && window)
{
    mWindows.push_back(std::move(window));
}

void GameManager::selectNextWindow(const std::string & name)
{
    for (auto & win: mWindows)
    {
        if (win->name() == name)
        {
            mNextWindow = win.get();
            break;
        }
    }
}

int GameManager::screenWidth () const
{
    return mScreenMaxX + 1;
}

int GameManager::screenHeight () const
{
    return mScreenMaxY + 1;
}

int GameManager::minScreenWidth () const
{
    return mMinScreenWidth;
}

int GameManager::minScreenHeight () const
{
    return mMinScreenHeight;
}

void GameManager::setMinScreenDimensions (int height, int width)
{
    mMinScreenHeight = height;
    mMinScreenWidth = width;
}

int GameManager::maxScreenWidth () const
{
    return mMaxScreenWidth;
}

int GameManager::maxScreenHeight () const
{
    return mMaxScreenHeight;
}

void GameManager::setMaxScreenDimensions (int height, int width)
{
    mMaxScreenHeight = height;
    mMaxScreenWidth = width;
}

void GameManager::initialize ()
{
    LogManager::initialize("/log/aboqa.log");

    initscr();
    start_color();
    raw();
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
    
    Colors::initializeColorPairs();

    getmaxyx(stdscr, mScreenMaxY, mScreenMaxX);
    // For some reason, these values come back too big.
    --mScreenMaxY;
    --mScreenMaxX;
}

void GameManager::deinitialize ()
{
    endwin();
    
    LogManager::deinitialize();
}

void GameManager::loop ()
{
    while (!mExit)
    {
        if (mNextWindow)
        {
            // Switch current window at the beginning of the loop.
            mCurrentWindow = mNextWindow;
            mNextWindow = nullptr;
        }
        if (!mCurrentWindow)
        {
            break;
        }
        
        getmaxyx(stdscr, mScreenMaxY, mScreenMaxX);
        // For some reason, these values come back too big.
        --mScreenMaxY;
        --mScreenMaxX;
        
        mCurrentWindow->resize(checkHeightBounds(screenHeight()), checkWidthBounds(screenWidth()));
        
        mCurrentWindow->processInput(this);
        
        mCurrentWindow->draw();
        
        doupdate();
    }
}

int GameManager::checkHeightBounds (int height) const
{
    if (height < mMinScreenHeight)
    {
        return mMinScreenHeight;
    }

    if (height > mMaxScreenHeight)
    {
        return mMaxScreenHeight;
    }

    return height;
}

int GameManager::checkWidthBounds (int width) const
{
    if (width < mMinScreenWidth)
    {
        return mMinScreenWidth;
    }

    if (width > mMaxScreenWidth)
    {
        return mMaxScreenWidth;
    }

    return width;
}
