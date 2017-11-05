//
//  main.cpp
//  aboqa
//
//  Created by Abdul Wahid Tanner on 10/29/17.
//  Copyright © 2017 Take Up Code. All rights reserved.
//

#include "GameManager.h"

int main()
{
    GameManager gm;
    gm.setMinScreenDimensions(20, 60);
    gm.setMaxScreenDimensions(60, 200);
    gm.play();
    
    return 0;
}
