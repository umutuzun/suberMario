//
// Created by Umut Uzun on 11/10/2017.
//

#ifndef SUBERMARIO_LTEXTURE_H
#define SUBERMARIO_LTEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

//Texture wrapper class
class LTexture  {
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(const std::string &path, SDL_Renderer* gRenderer );

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip=NULL );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif //SUBERMARIO_LTEXTURE_H
