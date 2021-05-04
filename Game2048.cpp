#include "Game2048.h"

bool Game2048::leftMove()
{
    bool ok = false;
    for(int j = 0; j < Size; j++)
    {
        int k = 0;
        for( int i = 0; i < Size; i++)
            if( arr[i][j] != 0 ) {
                    if( arr[k][j] == 0 ) ok = true;
                    arr[k][j] = arr[i][j], k++;
            }


        while(k < Size) arr[k][j] = 0, k++;

        for( int i = 0; i < Size - 1; i++ )
        if(arr[i][j] == arr[i+1][j] && arr[i][j] != 0){
            arr[i][j] *= 2; ok = true;
            for(int u = i+1; u < Size - 1; u++)
                arr[u][j] = arr[u+1][j];
            arr[Size - 1][j] = 0;
        }
    }

    return ok;
}

bool Game2048::rightMove()
{
    bool ok = false;
    for(int j = 0; j < Size; j++)
    {
        int k = Size - 1;
        for( int i = Size - 1; i >= 0; i--)
            if( arr[i][j] != 0 ) {
                    if( arr[k][j] == 0 ) ok = true;
                    arr[k][j] = arr[i][j], k--;
            }

        while(k >= 0) arr[k][j] = 0, k--;

        for( int i = Size - 1; i > 0; i-- )
        if(arr[i][j] == arr[i-1][j] && arr[i][j] != 0){
            arr[i][j] *= 2; ok = true;
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
    for(int j = 0; j < Size; j++)
    {
        int k = Size - 1;
        for( int i = Size - 1; i >= 0; i--)
            if( arr[j][i] != 0 ) {
                    if( arr[j][k] == 0 ) ok = true;
                    arr[j][k] = arr[j][i], k--;
            }

        while(k >= 0) arr[j][k] = 0, k--;

        for( int i = Size - 1; i > 0; i-- )
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
    for(int j = 0; j < Size; j++)
    {
        int k = 0;
        for( int i = 0; i < Size; i++)
            if( arr[j][i] != 0 ) {
                    if( arr[j][k] == 0 ) ok = true;
                    arr[j][k] = arr[j][i], k++;
            }

        while(k < Size) arr[j][k] = 0, k++;

        for( int i = 0; i < Size - 1; i++ )
        if(arr[j][i] == arr[j][i + 1] && arr[j][i] != 0){
            arr[j][i] *= 2; ok = true;
            for(int u = i+1; u < Size - 1; u++)
                arr[j][u] = arr[j][u + 1];
            arr[j][Size - 1] = 0;
        }
    }
    return ok;
}

bool Game2048::checkOver()
{
    for( int i = 0; i < Size; i++)
        for( int j = 0; j < Size; j++)
            if( arr[i][j] == 0) return false;
    return true;
}

bool Game2048::checkWin()
{
    for( int i = 0; i < Size; i++)
        for( int j = 0; j < Size; j++)
            if( arr[i][j] == 2048) return true;
    return false;
}

void Game2048::random(){
    int k = pow(2, rand() % 2 + 1);
    int x, y;
    do{
        x = rand()% Size;
        int S = 1;
        for( int i = 0; i < Size; i++)
            S *= arr[x][i];
        if( S == 0 ) break;
    }while( true );

    do{
        y = rand()% Size;
        if( arr[x][y] == 0 ) break;
    }while( true );

    arr[x][y] = k;
    isRandom = false;
    return;
}

void Game2048::init()
{
    for( int i = 0; i < Size; i++)
        for( int j = 0; j < Size; j++)   arr[i][j] = 0;
//    random();
//    random();
//    random();
      if(Size == 3) {random();random();random();random();random();}
      else if(Size == 4) {random();random();random();random();random();random();random();random();}
      else {random();random();random();random();random();random();random();random();random();random();}
}

void Game2048::render(SDL_Renderer* renderer)
{
    //setColor(renderer, BLACK_COLOR );
    //SDL_RenderClear(renderer);
    setColor(renderer, WHITE_COLOR );
    for( int i = 0; i < Size; i++)
        for(int j = 0; j < Size; j++)
        {
            int x = (width - Size * 100) / 2 + i * 100;
            int y = (height - Size * 100) / 2 + j * 100;
            SDL_Rect rect = { x, y, 99, 99};
            SDL_RenderFillRect( renderer, &rect);
            show( renderer, std::to_string(arr[i][j]), BLACK_COLOR, x + 50 - 15 * std::to_string(arr[i][j]).size() / 2 , y + 20, 15 * std::to_string(arr[i][j]).size(), 50, 40);
        }
    SDL_RenderPresent( renderer );
}
