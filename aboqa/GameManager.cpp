//
//  GameManager.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/26/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "GameManager.h"

#include <curses.h>

#include "LogManager.h"

using namespace std;

void GameManager::play ()
{
    initialize();
    
    loop();
    
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
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    mState = State::Normal;
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
    }
}

void GameManager::processInput ()
{
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

