//
// Created by Umut Uzun on 11/13/2017.
//
#ifndef SUBERMARIO_WINDOWMANAGER_H
#define SUBERMARIO_WINDOWMANAGER_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Constants.h"

class WindowManager {
//The window renderer
    SDL_Renderer *gRenderer = NULL;
//The window we'll be rendering to
    SDL_Window *gWindow = NULL;

public:
    SDL_Renderer *getGRenderer() const {
        return gRenderer;
    }
    bool init();
    void close();
};


#endif //SUBERMARIO_WINDOWMANAGER_H
