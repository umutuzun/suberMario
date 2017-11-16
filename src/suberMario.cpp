#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Constants.h"
#include "WindowManager.h"
#include "InputState.h"

void handleAction(InputState &inputState, int &clipX, LTexture &gBackgroundTexture) {
    if (inputState.isGoingRight) {
        if (clipX < gBackgroundTexture.getWidth() - SCREEN_WIDTH) {
            clipX += 1;
        }
    }
    if (inputState.isGoingLeft) {
        if (clipX > 0) {
            clipX -= 1;
        }
   }
}

int main( int argc, char* args[] )
{
    int clipX = 0;
    WindowManager windowManager;
    InputState inputState;
    //Scene sprite
    LTexture gBackgroundTexture;
    LTexture gMarioTexture;
    //Start up SDL and create window
    if( !windowManager.init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load backgroundTexture
        if( !gBackgroundTexture.loadFromFile( "../resources/images/11.bmp", windowManager.getGRenderer() ) )
        {
            printf( "Failed to load background texture!\n" );
        }
        else
        {
        if(!gMarioTexture.loadFromFile("../resources/images/mario/mario.bmp", windowManager.getGRenderer())) {
            printf( "Failed to load mario texture!\n" );
        }
        else
        {
            //Event handler
            SDL_Event e;

            //While application is running
            while( !inputState.quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ) {
                    inputState.handleEvent(e);
                }
                handleAction(inputState, clipX, gBackgroundTexture);
                //Clear screen
                SDL_SetRenderDrawColor( windowManager.getGRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( windowManager.getGRenderer() );

                //Render background
                gBackgroundTexture.render( clipX, windowManager.getGRenderer() );

                //Render Mario
                //gMarioTexture.render( clipX, windowManager.getGRenderer());

                //Update screen
                SDL_RenderPresent( windowManager.getGRenderer() );
            }
        }
    }
    }

    //Free loaded images
    gBackgroundTexture.free();

    //Free resources and close SDL
    windowManager.close();

    return 0;
}