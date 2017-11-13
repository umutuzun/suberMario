//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int CLIP_X = 0;

class WindowManager {
//The window renderer
    SDL_Renderer *gRenderer = NULL;
//The window we'll be rendering to
    SDL_Window *gWindow = NULL;

public:

    SDL_Renderer *getGRenderer() const {
        return gRenderer;
    }

    bool init()
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
            if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
            {
                printf( "Warning: Linear texture filtering not enabled!" );
            }

            //Create window
            gWindow = SDL_CreateWindow( "Suber Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
            if( gWindow == NULL )
            {
                printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Create renderer for window
                gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
                if( gRenderer == NULL )
                {
                    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                    success = false;
                }
                else
                {
                    //Initialize renderer color
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

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
    void close()
    {
        //Destroy window
        SDL_DestroyRenderer( gRenderer );
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        gRenderer = NULL;

        //Quit SDL subsystems
        IMG_Quit();
        SDL_Quit();
    }
};

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );


//Scene sprite
SDL_Rect gSpriteClip;
LTexture gSpriteSheetTexture;

void setSpriteClip(int x)
{
    //Set sprite
    gSpriteClip.x =   x;
    gSpriteClip.y =   0;
    gSpriteClip.w = 640;
    gSpriteClip.h = 480;

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
    setSpriteClip(CLIP_X);
    return success;
}




bool isGoingRight = false;
bool isGoingLeft = false;

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
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ) {
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

                if(isGoingRight) {
                    if(CLIP_X < gSpriteSheetTexture.getWidth() - 640) {
                        CLIP_X += 1;
                    }
                    setSpriteClip(CLIP_X);
                }
                if(isGoingLeft) {
                    if(CLIP_X>0) {
                        CLIP_X -= 1;
                    }
                    setSpriteClip(CLIP_X);
                }
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