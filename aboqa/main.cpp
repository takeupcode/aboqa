//
//  main.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/29/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include <iostream>
#include <limits>
#include <locale.h>
#include <memory>

#include "../submodules/TUCUT/Curses/Colors.h"
#include "../submodules/TUCUT/Curses/GameManager.h"
#include "../submodules/TUCUT/Log/LogManager.h"

#include "SplashWindow.h"
#include "MainWindow.h"
#include "ExitWindow.h"

int main(int argc, const char *argv[])
{
    setlocale (LC_ALL, "");
    
    TUCUT::Log::LogManager::initialize("logs", "aboqa");
    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--debug") == 0)
        {
            std::cout << "Debugging in terminal. Press enter key to continue." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            std::string temp;
            std::getline(std::cin, temp);
            break;
        }
    }
    
    char *term = getenv("TERM");
    if (!term)
    {
        std::cout << "ncurses not available. Exiting." << std::endl;
        return 1;
    }
    
    TUCUT::Curses::GameManager gm;
    gm.initialize();

    gm.setMinScreenDimensions(10, 35);
    gm.setMaxScreenDimensions(60, 200);

    gm.addWindow(SplashWindow::createSharedSplashWindow("splash", 0, 0, gm.screenHeight(), gm.screenWidth(), TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_WHITE, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_WHITE, false));
    
    gm.addWindow(MainWindow::createSharedMainWindow("main", 0, 0, gm.screenHeight(), gm.screenWidth(), TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_BRIGHT_WHITE, TUCUT::Curses::Colors::COLOR_DIM_YELLOW, TUCUT::Curses::Colors::COLOR_BRIGHT_WHITE, true));
    
    gm.addWindow(ExitWindow::createSharedExitWindow("exit", 0, 0, gm.screenHeight(), gm.screenWidth(), TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_WHITE, TUCUT::Curses::Colors::COLOR_DIM_BLACK, TUCUT::Curses::Colors::COLOR_DIM_WHITE, false));
    
    gm.selectNextWindow("splash");
    
    gm.play();
    
    TUCUT::Log::LogManager::instance()->deinitialize();
    
    return 0;
}
