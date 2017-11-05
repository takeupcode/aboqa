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
: mState(State::Normal), mScreenWidth(0), mScreenHeight(0),
  mMinScreenWidth(0), mMinScreenHeight(0), mMaxScreenWidth(80), mMaxScreenHeight(40),
  mWindow(nullptr)
{ }

GameManager::~GameManager ()
{ }

void GameManager::play ()
{
    initialize();
    
    bool result;
    {
        Window splash(0, 0, mScreenHeight + 1, mScreenWidth + 1, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, false);
        splash.draw();
        doupdate();
        result = ConsoleManager::promptYesOrNo(splash.cursesWindow(), 5, 10, 50, 6, 10, 50, "Would you like to play a game? y/n: ",
                                               Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_BRIGHT_RED, Colors::COLOR_DIM_WHITE);
    }
    if (result)
    {
        mWindow = new Window(1, 1, mScreenHeight - 2, mScreenWidth - 2, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE, true);
        loop();
    }
    
    deinitialize();
}

int GameManager::screenWidth () const
{
    return mScreenWidth;
}

int GameManager::screenHeight () const
{
    return mScreenHeight;
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
    
    Colors::initializeColorPairs();

    mState = State::Normal;
    mScreenHeight = LINES;
    mScreenWidth = COLS;
}

void GameManager::deinitialize ()
{
    delete mWindow;
    mWindow = nullptr;

    endwin();
    
    LogManager::deinitialize();
}

void GameManager::loop ()
{
    while (mState != State::Exit)
    {
        int maxY;
        int maxX;

        getmaxyx(stdscr, maxY, maxX);
        mWindow->resize(checkHeightBounds(maxY - 2), checkWidthBounds(maxX - 2));
        
        processInput();
        mWindow->draw();
        
        doupdate();
    }
}

void GameManager::processInput ()
{
    // This relies on nodelay() == true for the main window.
    int c = wgetch(stdscr);
    switch(c)
    {
        case ERR:
            break;
        case KEY_DOWN:
            LogManager::instance()->logInfo("Down key pressed.");
            break;
        case KEY_UP:
            break;
        case 10: /* Enter */
            break;
        case KEY_F(1):
            mState = State::Exit;
            break;
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
