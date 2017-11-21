#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Constants.h"
#include "WindowManager.h"
#include "InputState.h"

int marioFrame = 0;

void handleAction(InputState &inputState, int &sourceRectX, LTexture &gBackgroundTexture, long time) {
    if (inputState.isGoingRight) {
        if (sourceRectX < gBackgroundTexture.getWidth() - SCREEN_WIDTH) {
            time = (time / (1000/10));
            sourceRectX += 5;
            marioFrame = time % 3;
            marioFrame++;
        }
    }
    if (inputState.isGoingLeft) {
        if (sourceRectX > 0) {
            sourceRectX -= 5;
            time = (time / (1000/10));
            marioFrame = time % 3;
            marioFrame++;
        }
   }
}

int main( int argc, char* args[] )
{
    int sourceRectX = 0;
    WindowManager windowManager;
    InputState inputState;
    //Scene sprite
    LTexture gBackgroundTexture;
    LTexture gMarioTexture;
    LTexture gMarioAnimTextures[3];
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
        if(!gMarioAnimTextures[0].loadFromFile( "../resources/images/mario/mario.bmp", windowManager.getGRenderer() ) ||
                !gMarioAnimTextures[1].loadFromFile( "../resources/images/mario/mario_move0.bmp", windowManager.getGRenderer() ) ||
                !gMarioAnimTextures[2].loadFromFile( "../resources/images/mario/mario_move1.bmp", windowManager.getGRenderer() ) ||
                !gMarioAnimTextures[3].loadFromFile( "../resources/images/mario/mario_move2.bmp", windowManager.getGRenderer() ) ){
            printf( "Failed to load mario textures!\n" );
        }
        else
        {
            //Event handler
            SDL_Event e;
            marioFrame = 0;
            long previousTime = 0;
            long time = SDL_GetTicks();
            //While application is running
            while( !inputState.quit ) {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ) {
                    inputState.handleEvent(e);

                }
                if (time - previousTime > 16){
                    for(int i = 0; i < (time-previousTime)/16; i++) {
                        handleAction(inputState, sourceRectX, gBackgroundTexture, time);
                    }
                    previousTime = time;
                }
                //Clear screen
                SDL_SetRenderDrawColor( windowManager.getGRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( windowManager.getGRenderer() );

                //Render background
                gBackgroundTexture.render( sourceRectX, 0, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, windowManager.getGRenderer() );

                //Render Mario
                if ( inputState.isGoingLeft) {
                    gMarioAnimTextures[marioFrame].renderCopyEx( 0, 0, gMarioAnimTextures[marioFrame].getHeight(), gMarioAnimTextures[marioFrame].getWidth(), 30, 385, gMarioAnimTextures[marioFrame].getHeight(), gMarioAnimTextures[marioFrame].getWidth(), windowManager.getGRenderer() );
                } else {
                    gMarioAnimTextures[marioFrame].render( 0, 0, gMarioAnimTextures[marioFrame].getHeight(), gMarioAnimTextures[marioFrame].getWidth(), 30, 385, gMarioAnimTextures[marioFrame].getHeight(), gMarioAnimTextures[marioFrame].getWidth(), windowManager.getGRenderer() );
                }

                //Update screen
                SDL_RenderPresent( windowManager.getGRenderer() );

                time = SDL_GetTicks();
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