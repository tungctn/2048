#include"_sdl.h"

void initSDL(SDL_Window* &win, SDL_Renderer* &ren)
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) std::cout << "error: SDL_Init() \n";
    if( TTF_Init() != 0) std::cout << "error: TTF_Init() \n";

    {
        std::string nameWindow = "GAME 2048";
        win = SDL_CreateWindow(nameWindow.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN); // ,SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP

        ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(ren, width, height);
}

void setColor(SDL_Renderer* ren, SDL_Color color)
{
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
}

void renderRect( SDL_Renderer* ren, SDL_Color color, int x, int y , int w, int h)
{
    SDL_Rect rect = {x, y, w, h};
    setColor( ren, color );
    SDL_RenderFillRect(ren, &rect);
}

bool check_mouse( int x, int y , int _x , int _y , int w, int h) {
    return x > _x && x < _x + w && y > _y && y < _y + h;
}

