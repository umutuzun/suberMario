//
// Created by Umut Uzun on 11/10/2017.
//

#include "LTexture.h"

using namespace std;

LTexture::LTexture()
{
    //Initialize
    imageTexture = NULL;
    imageWidth = 0;
    imageHeight = 0;
    destinationRect.x= 0;
    destinationRect.y = 0;
    destinationRect.h = SCREEN_HEIGHT;
    destinationRect.w = SCREEN_WIDTH;
    sourceRect = destinationRect;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(const string &path, SDL_Renderer* gRenderer )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        cout << "Unable to load image "<< path.c_str() << "! SDL_image Error: " <<  IMG_GetError() << endl;
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            imageWidth = loadedSurface->w;
            imageHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    imageTexture = newTexture;
    return imageTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( imageTexture != NULL )
    {
        SDL_DestroyTexture( imageTexture );
        imageTexture = NULL;
        imageWidth = 0;
        imageHeight = 0;
    }
}

void LTexture::render( int sourceRectX, int sourceRectY, int sourceRectH, int sourceRectW, int destinationRectX, int destinationRectY, int destinationRectH, int destinationRectW, SDL_Renderer* gRenderer )
{
    sourceRect.x = sourceRectX;
    sourceRect.y = sourceRectY;
    sourceRect.h = sourceRectH;
    sourceRect.w = sourceRectW;

    destinationRect.x = destinationRectX;
    destinationRect.y = destinationRectY;
    destinationRect.h = destinationRectH;
    destinationRect.w = destinationRectW;

    //Render to screen
    SDL_RenderCopy( gRenderer, imageTexture, &sourceRect, &destinationRect );
}

int LTexture::getWidth()
{
    return imageWidth;
}

int LTexture::getHeight()
{
    return imageHeight;
}
