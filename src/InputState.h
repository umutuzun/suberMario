//
// Created by Umut Uzun on 11/16/2017.
//

#ifndef SUBERMARIO_INPUTSTATE_H
#define SUBERMARIO_INPUTSTATE_H
#include <SDL2/SDL.h>

class InputState {
public:
    //Initializes variables
    InputState();
    //Handles input
    void handleEvent(SDL_Event &event);
    bool isGoingRight;
    bool isGoingLeft;
    //Main loop flag
    bool quit;
};

#endif //SUBERMARIO_INPUTSTATE_H
