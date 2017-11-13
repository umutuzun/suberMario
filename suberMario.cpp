//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Constants.h"
#include "WindowManager.h"

int CLIP_X = 0;
bool isGoingRight = false;
bool isGoingLeft = false;
//Main loop flag
bool quit = false;

//Scene sprite
SDL_Rect gSpriteClip;
LTexture gSpriteSheetTexture;

void setSpriteClip(int x)
{
    //Set sprite
    gSpriteClip.x =   x;
    gSpriteClip.y =   0;
    gSpriteClip.w = SCREEN_WIDTH;
    gSpriteClip.h = SCREEN_HEIGHT;

}

bool loadMedia(SDL_Renderer* gRenderer)
{
    //Loading success flag
    bool success = true;

    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "../resources/images/11.bmp", gRenderer ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    setSpriteClip(0);
    return success;
}

void handleEvent(SDL_Event &e){
    //User requests quit
    if (e.type == SDL_QUIT) {
        quit = true;
    }
        //User presses a key
    else if (e.type == SDL_KEYDOWN) {
        //Select surfaces based on key press
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                isGoingRight=true;
                break;
            case SDLK_LEFT:
                isGoingLeft=true;
                break;
        }
    } else if (e.type == SDL_KEYUP) {
        //Select surfaces based on key press
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                isGoingRight=false;
                break;
            case SDLK_LEFT:
                isGoingLeft=false;
                break;
        }
    }
}

void handleAction() {
    if (isGoingRight) {
        if (CLIP_X < gSpriteSheetTexture.getWidth() - SCREEN_WIDTH) {
            CLIP_X += 1;
        }
        setSpriteClip(CLIP_X);
    }
    if (isGoingLeft) {
        if (CLIP_X > 0) {
            CLIP_X -= 1;
        }
        setSpriteClip(CLIP_X);
    }
}

int main( int argc, char* args[] )
{
    WindowManager windowManager;
    //Start up SDL and create window
    if( !windowManager.init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia(windowManager.getGRenderer()) )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ) {
                    handleEvent(e);
                }
                handleAction();
                //Clear screen
                SDL_SetRenderDrawColor( windowManager.getGRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( windowManager.getGRenderer() );

                //Render sprite
                gSpriteSheetTexture.render( 0, 0, windowManager.getGRenderer(), &gSpriteClip );

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