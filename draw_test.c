#include <stdio.h>
#include <SDL2/SDL.h>


/*
 * Lesson 0: Test to make sure SDL is setup properly
 */
int main(int argc, char** argv){

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){

        return 1;
    }
    SDL_Quit();

    return 0;
}
