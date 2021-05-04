#include "Game2048.h"


using namespace std;

SDL_Surface* menuSurface = NULL;
SDL_Texture* menu = nullptr;

SDL_Surface* bkgSurface = NULL;
SDL_Texture* bkg = nullptr;

SDL_Surface* gameoverSurface = NULL;
SDL_Texture* go = nullptr;


SDL_Surface* winSurface = NULL;
SDL_Texture* win = nullptr;
Game2048 game2048;
void draw(SDL_Renderer*&);

SDL_Window* window;
SDL_Renderer* renderer;
string MUS = "Jincheng-Zhang-Earnest-I-Love-You-_Background-Music_-_Instrumental-Song_-_Official-Music-Audio_.mp3";

bool Again()
{

    SDL_Event e;
    while( true )
    {

    //SDL_Delay(1000);
        while( SDL_PollEvent( &e ) )
        {
            if(e.type == SDL_QUIT) return 0;

            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                int x = e.button.x;
                int y = e.button.y;
                if( check_mouse(x, y, 240, 275, 120, 50) ) return 0;
                if( check_mouse(x, y, 180, 200, 240, 50) ) return 1;
            }
        }
    }
}

int Continue();


void gameOver();




void gameWin()
{
//    setColor( renderer, BLACK_COLOR );
//    SDL_RenderClear( renderer );
    bkgSurface = IMG_Load("thien-ha-700x466.jpg");
    bkg = SDL_CreateTextureFromSurface(renderer,bkgSurface);
    SDL_FreeSurface(bkgSurface);
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    //SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,bkg,nullptr,nullptr);
    SDL_Rect filled_rect;
    show( renderer, "YOU WIN", WHITE_COLOR, 195, 125, 270, 50, 60);
    show( renderer, "RESUME", WHITE_COLOR, 210, 200, 270, 50, 60);
    show( renderer, "NEW GAME", WHITE_COLOR, 180, 275, 240, 50, 60);
    show( renderer, "EXIT", WHITE_COLOR, 240, 350, 120, 50, 60);
    SDL_RenderPresent( renderer );
}

bool PlayGame()
{

    game2048.init();
    SDL_Event e;
    game2048.render(renderer);
    SDL_RenderPresent( renderer );
    while( true )
    {
        while(SDL_PollEvent( &e ) )
        {
            //cout << "1\n";
            if( SDL_QUIT == e.type ) return 0;
            if( e.type == SDL_KEYDOWN )
            {

                switch( e.key.keysym.sym )
                {

                    case SDLK_UP:
                        game2048.isRandom = game2048.upMove(); break;

                    case SDLK_DOWN:
                        game2048.isRandom = game2048.downMove(); break;

                    case SDLK_LEFT:
                        game2048.isRandom = game2048.leftMove(); break;

                    case SDLK_RIGHT:
                        game2048.isRandom = game2048.rightMove(); break;
                }
            }
        }


        if( game2048.isRandom )
        {
            game2048.random();
            game2048.render(renderer);
        }

        SDL_RenderPresent( renderer);

        if( game2048.checkOver() )  {
            gameOver();
            return 1;
        }

        if( game2048.checkWin() ) {
            gameWin();
            int k = Continue();
            if( k == 0 ) return 0;
            if( k == 1 ) return PlayGame();
            if( k == 2 ) continue;
        }
    }
}

bool start()
{

    menuSurface = IMG_Load("background_01.jpg");
    menu = SDL_CreateTextureFromSurface(renderer,menuSurface);
    SDL_FreeSurface(menuSurface);
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
     //SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,menu,nullptr,nullptr);
    SDL_Rect filled_rect;
    SDL_RenderPresent(renderer);
     //SDL_Delay(1);
    show( renderer, "NEW GAME", WHITE_COLOR, 180, 240, 240, 50, 60);
    show( renderer, "EXIT", WHITE_COLOR, 240, 315, 120, 50, 60);
    SDL_RenderPresent( renderer );
    SDL_Event e;
    while( true )
    {
        while( SDL_PollEvent( &e ) )
        {
            if(e.type == SDL_QUIT) return 0;

            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                int x = e.button.x;
                int y = e.button.y;
                if( check_mouse(x, y, 240, 315 , 120, 50) ) return 0;
                if( check_mouse(x, y, 180, 240 , 240, 50) ) return 1;
            }
        }
    }
}

void Size()
{

    menuSurface = IMG_Load("background_01.jpg");
    menu = SDL_CreateTextureFromSurface(renderer,menuSurface);
    SDL_FreeSurface(menuSurface);
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
     //SDL_RenderClear(renderer);
     SDL_RenderCopy(renderer,menu,nullptr,nullptr);
     SDL_Rect filled_rect;
     SDL_RenderPresent(renderer);
    show( renderer, "4 x 4" , WHITE_COLOR, width / 2 - 5 *30 / 2, height / 2 - 100, 30 * 5, 100, 40);
    show( renderer, "5 x 5" , WHITE_COLOR, width / 2 - 5 *30 / 2, height / 2 , 30 * 5, 100, 40);
    SDL_RenderPresent( renderer) ;

    SDL_Event e;
    while( true )
    {
        while( SDL_PollEvent( &e ) )
        {
            if(e.type == SDL_QUIT) return;

            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                int x = e.button.x;
                int y = e.button.y;

                if( check_mouse(x, y, width / 2 - 5 *30 / 2, height / 2 - 50, 30 * 5, 100) ) { game2048.Size = 4; return; }
                if( check_mouse(x, y, width / 2 - 5 *30 / 2, height / 2 + 50, 30 * 5, 100) ) { game2048.Size = 5; return; }
            }
        }
    }

}

int main(int argc, char* argv[])
{



    srand(time(NULL));
    initSDL( window, renderer);
    SDL_Texture * texture;
    Mix_Music* mus;
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    mus = Mix_LoadMUS(MUS.c_str());
    Mix_PlayMusic(mus,-1);

    if(!start()) return 0;

    do {
         Size();
         gameoverSurface = IMG_Load("thien-ha-700x466.jpg");
    go = SDL_CreateTextureFromSurface(renderer,gameoverSurface);
    SDL_FreeSurface(gameoverSurface);
    //SDL_SetRenderDrawColor(renderer,0,0,0,0);
    //SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,go,nullptr,nullptr);
    SDL_Rect filled_rect;
    SDL_RenderPresent(renderer);
        if( !PlayGame() ) return 0;

        if( Again() == false ) return 0;

    } while( true );
    Mix_PauseMusic();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(mus);
    return 0;
}

int Continue()
{
    SDL_Event e;
    while( true )
    {
        while( SDL_PollEvent( &e ) )
        {
            if(e.type == SDL_QUIT) return 0;

            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                int x = e.button.x;
                int y = e.button.y;
                if( check_mouse(x, y, 210, 200, 270, 50) ) return 2;
                if( check_mouse(x, y, 180, 275, 240, 50) ) return 1;
                if( check_mouse(x, y, 240, 350, 240, 50) ) return 0;
            }
        }
    }
}

void gameOver()
{

    //setColor( renderer, BLACK_COLOR );
    //SDL_RenderClear( renderer );
    bkgSurface = IMG_Load("thien-ha-700x466.jpg");
    bkg = SDL_CreateTextureFromSurface(renderer,bkgSurface);
    SDL_FreeSurface(bkgSurface);
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    //SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,bkg,nullptr,nullptr);
    SDL_Rect filled_rect;
    SDL_RenderPresent(renderer);
    show( renderer, "GAME OVER", WHITE_COLOR, 165, 125, 270, 50, 60);
    show( renderer, "NEW GAME", WHITE_COLOR, 180, 200, 240, 50, 60);
    show( renderer, "EXIT", WHITE_COLOR, 240, 275, 120, 50, 60);
    SDL_RenderPresent( renderer );
}
