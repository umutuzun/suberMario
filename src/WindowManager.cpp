//
// Created by Umut Uzun on 11/13/2017.
//

#include "WindowManager.h"

bool WindowManager::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) )
        {
            printf( "Warning: Nearest pixel filtering not enabled!" );
        }

        //Create window
        gameWindow = SDL_CreateWindow( "Suber Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gameWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gameRenderer = SDL_CreateRenderer( gameWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gameRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize BMP loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

//Frees media and shuts down SDL
void WindowManager::close()
{
    //Destroy window
    SDL_DestroyRenderer( gameRenderer );
    SDL_DestroyWindow( gameWindow );
    gameWindow = NULL;
    gameRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}