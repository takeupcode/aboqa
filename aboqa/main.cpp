//
//  main.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/29/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include <iostream>
#include<limits>
#include <locale.h>
#include <memory>

#include "Colors.h"
#include "GameManager.h"
#include "SplashWindow.h"
#include "MainWindow.h"
#include "ExitWindow.h"

int main(int argc, const char *argv[])
{
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
    
    setlocale (LC_ALL, "");
    
    GameManager gm;
    
    gm.setMinScreenDimensions(10, 35);
    gm.setMaxScreenDimensions(60, 200);
    gm.initialize();

    gm.addWindow(std::unique_ptr<Window>(new SplashWindow("splash", 0, 0, gm.screenHeight(), gm.screenWidth(), Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, false)));
    
    gm.addWindow(std::unique_ptr<Window>(new MainWindow("main", 0, 0, gm.screenHeight(), gm.screenWidth(), Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_BRIGHT_WHITE, true)));
    
    gm.addWindow(std::unique_ptr<Window>(new ExitWindow("exit", 0, 0, gm.screenHeight(), gm.screenWidth(), Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, Colors::COLOR_DIM_BLACK, Colors::COLOR_DIM_WHITE, false)));
    
    gm.selectNextWindow("splash");
    
    gm.play();
    
    return 0;
}
