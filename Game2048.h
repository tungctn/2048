#pragma once

#include "text.h"

struct Game2048{
    bool upMove();
    bool downMove();
    bool leftMove();
    bool rightMove();

    void init();
    bool checkOver();
    void random();
    bool checkWin();

    void render(SDL_Renderer* );

    int arr[4][4];
    bool isRandom = true;
};

