#pragma once

#include "color.h"
#include <iostream>
#include <time.h>
#include <random>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


const int width = 600;
const int height = 600;

const std::string FONT = "font\\VNI-Korin.TTF";

void setColor(SDL_Renderer* , SDL_Color );
void renderRect( SDL_Renderer* , SDL_Color , int , int  , int , int );

void initSDL(SDL_Window* &, SDL_Renderer* &);

bool check_mouse( int , int , int , int , int , int );
void waitUntilKeyPressed();
//void logSDLError(ostream& os, const string &msg, bool fatal);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
