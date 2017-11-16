//
// Created by Umut Uzun on 11/16/2017.
//

#include "InputState.h"

InputState::InputState(){
    isGoingRight = false;
    isGoingLeft = false;
    quit = false;
}

void InputState::handleEvent(SDL_Event &e){
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