//
//  main.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/29/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include <memory>

#include "Colors.h"
#include "GameManager.h"
#include "SplashWindow.h"
#include "MainWindow.h"
#include "ExitWindow.h"

int main()
{
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
