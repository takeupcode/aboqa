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

void GameManager::play ()
{
    initialize();
    
    bool result = ConsoleManager::promptYesOrNo(stdscr, 5, 10, 50, 6, 10, 50, "Would you like to play a game? y/n: ",
                                                Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE, Colors::COLOR_DIM_RED, Colors::COLOR_BRIGHT_WHITE);
    Window w(0, 0, mScreenHeight, mScreenWidth, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE, true);
    w.draw();
    
    if (result)
    {
        loop();
    }
    
    deinitialize();
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
    endwin();
    
    LogManager::deinitialize();
}

void GameManager::loop ()
{
    while (mState != State::Exit)
    {
        processInput();
        refresh();
    }
}

void GameManager::processInput ()
{
    // This relies on nodelay() == true for the main window.
    int c = getch();
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

