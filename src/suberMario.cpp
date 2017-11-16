//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Constants.h"
#include "WindowManager.h"
#include "InputState.h"

void handleAction(InputState &inputState, int &clipX, LTexture &gSpriteSheetTexture) {
    if (inputState.isGoingRight) {
        if (clipX < gSpriteSheetTexture.getWidth() - SCREEN_WIDTH) {
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
    LTexture gSpriteSheetTexture;
    //Start up SDL and create window
    if( !windowManager.init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !gSpriteSheetTexture.loadFromFile( "../resources/images/11.bmp", windowManager.getGRenderer() ) )
        {
            printf( "Failed to load sprite sheet texture!\n" );
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
                handleAction(inputState, clipX, gSpriteSheetTexture);
                //Clear screen
                SDL_SetRenderDrawColor( windowManager.getGRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( windowManager.getGRenderer() );

                //Render sprite
                gSpriteSheetTexture.render( clipX, windowManager.getGRenderer() );

                //Update screen
                SDL_RenderPresent( windowManager.getGRenderer() );
            }
        }
    }

    //Free loaded images
    gSpriteSheetTexture.free();

    //Free resources and close SDL
    windowManager.close();

    return 0;
}