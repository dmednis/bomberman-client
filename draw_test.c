#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/*
 * Lesson 0: Test to make sure SDL is setup properly
 */
int main(int argc, char **argv) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        puts("SDL_Init error");
    } else {
        puts("SDL_Init success!");
    }
//
//    // Initialize SDL
//    SDL_Window *lobby_window = SDL_CreateWindow("Drawing test",
//                                                SDL_WINDOWPOS_UNDEFINED,
//                                                SDL_WINDOWPOS_UNDEFINED,
//                                                800,
//                                                600,
//                                                SDL_WINDOW_OPENGL);
//
//    SDL_Renderer *renderer = SDL_CreateRenderer(lobby_window,
//                                                -1,
//                                                SDL_RENDERER_ACCELERATED |
//                                                SDL_RENDERER_PRESENTVSYNC);
//
//    SDL_Surface *screen;
//
//    TTF_Font *font = TTF_OpenFont("ARIAL.TTF", 12);
//    SDL_Color foregroundColor = {255, 255, 255};
//    SDL_Color backgroundColor = {0, 0, 255};
//    SDL_Surface *textSurface = TTF_RenderText_Shaded(font,
//                                                     "Testa teksts, yo!",
//                                                     foregroundColor,
//                                                     backgroundColor);
//
//    // Pass zero for width and height to draw the whole surface
//    SDL_Rect textLocation = {100, 100, 0, 0};
//
//    bool running = true;
//    SDL_Event event;
//
//    while (running) {
//        // Process events
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//        }
//
//        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
//
//        SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
//
////        // Clear screen with black
////        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
////        SDL_RenderClear(renderer);
//
//        // Show what was drawn
//        SDL_RenderPresent(renderer);
//    }
    SDL_Surface *screen;

    TTF_Font *font = TTF_OpenFont("ARIAL.TTF", 12);

    SDL_Color color={0,0,0};
    SDL_Surface *text_surface;
    if(!(text_surface=TTF_RenderText_Solid(font,"Hello World!",color))) {
        //handle error here, perhaps print TTF_GetError at least
        perror(TTF_GetError);
    } else {
        SDL_BlitSurface(text_surface,NULL,screen,NULL);
        //perhaps we can reuse it, but I assume not for simplicity.
        SDL_FreeSurface(text_surface);
    }

}
