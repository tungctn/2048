

#include "Game2048.h"

SDL_Surface* gameoverSurface = NULL;
SDL_Texture* go = nullptr;
bool Game2048::leftMove()
{
    bool ok = false;
    for(int j = 0; j < 4; j++)
    {
        int k = 0;
        for( int i = 0; i < 4; i++)
            if( arr[i][j] != 0 ) {
                    if( arr[k][j] == 0 ) ok = true;
                    arr[k][j] = arr[i][j], k++;
            }


        while(k < 4) arr[k][j] = 0, k++;

        for( int i = 0; i < 3; i++ )
        if(arr[i][j] == arr[i+1][j] && arr[i][j] != 0){
            arr[i][j] *= 2; ok = true;
            for(int u = i+1; u < 3; u++)
                arr[u][j] = arr[u+1][j];
            arr[3][j] = 0;
        }
    }

    return ok;
}

bool Game2048::rightMove()
{
    bool ok = false;
    for(int j = 0; j < 4; j++)
    {
        int k = 3;
        for( int i = 3; i >= 0; i--)
            if( arr[i][j] != 0 ) {
                    if( arr[k][j] == 0 ) ok = true;
                    arr[k][j] = arr[i][j], k--;
            }

        while(k >= 0) arr[k][j] = 0, k--;

        for( int i = 3; i > 0; i-- )
        if(arr[i][j] == arr[i-1][j] && arr[i][j] != 0){
            arr[i][j] *= 2;ok = true;
            for(int u = i-1; u > 0; u--)
                arr[u][j] = arr[u-1][j];
            arr[0][j] = 0;
        }
    }
    return ok;
}
// j hang
// i cot
bool Game2048::downMove()
{
    bool ok = false;
    for(int j = 0; j < 4; j++)
    {
        int k = 3;
        for( int i = 3; i >= 0; i--)
            if( arr[j][i] != 0 ) {
                    if( arr[j][k] == 0 ) ok = true;
                    arr[j][k] = arr[j][i], k--;
            }

        while(k >= 0) arr[j][k] = 0, k--;

        for( int i = 3; i > 0; i-- )
        if(arr[j][i] == arr[j][i - 1] && arr[j][i] != 0){
            arr[j][i] *= 2; ok = true;
            for(int u = i-1; u > 0; u--)
                arr[j][u] = arr[j][u - 1];
            arr[j][0] = 0;
        }
    }
    return ok;
}
bool Game2048::upMove()
{
    bool ok = false;
    for(int j = 0; j < 4; j++)
    {
        int k = 0;
        for( int i = 0; i < 4; i++)
            if( arr[j][i] != 0 ) {
                    if( arr[j][k] == 0 ) ok = true;
                    arr[j][k] = arr[j][i], k++;
            }

        while(k < 4) arr[j][k] = 0, k++;

        for( int i = 0; i < 3; i++ )
        if(arr[j][i] == arr[j][i + 1] && arr[j][i] != 0){
            arr[j][i] *= 2; ok = true;
            for(int u = i+1; u < 3; u++)
                arr[j][u] = arr[j][u + 1];
            arr[j][3] = 0;
        }
    }
    return ok;
}

bool Game2048::checkOver()
{
    for( int i = 0; i < 4; i++)
        for( int j = 0; j < 4; j++)
            if( arr[i][j] == 0) return false;
    return true;
}

bool Game2048::checkWin()
{
    for( int i = 0; i < 4; i++)
        for( int j = 0; j < 4; j++)
            if( arr[i][j] == 2048) return true;
    return false;
}

void Game2048::random(){
    int k = pow(2, rand() % 2 + 1);
    int x, y;
    do{
        x = rand()% 4;
        if( arr[x][0] * arr[x][1] * arr[x][2] * arr[x][3] == 0 ) break;
    }while( true );

    do{
        y = rand()% 4;
        if( arr[x][y] == 0 ) break;
    }while( true );

    arr[x][y] = k;
    isRandom = false;
    return;
}

void Game2048::init()
{
    for( int i = 0; i < 4; i++)
        for( int j = 0; j < 4; j++)
            arr[i][j] = 0;
    random();
    random();
}

void Game2048::render(SDL_Renderer* renderer)
{
//    setColor(renderer, WHITE_COLOR );
   //SDL_RenderClear(renderer);
    gameoverSurface = IMG_Load("thien-ha-700x466.jpg");
    go = SDL_CreateTextureFromSurface(renderer,gameoverSurface);
    SDL_FreeSurface(gameoverSurface);
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    //SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,go,nullptr,nullptr);
    SDL_Rect filled_rect;
    SDL_RenderPresent(renderer);
    setColor(renderer, WHITE_COLOR );
    for( int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            int x = 100 + i * 100;
            int y = 100 + j * 100;
            SDL_Rect rect = { x, y, 99,99 };
            SDL_RenderFillRect( renderer, &rect);
            show( renderer, std::to_string(arr[i][j]), BLACK_COLOR, x + 50 - 15 * std::to_string(arr[i][j]).size() / 2 , y + 20, 15 * std::to_string(arr[i][j]).size(), 50, 40);
        }
    SDL_RenderPresent( renderer );
}
