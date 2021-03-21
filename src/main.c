#define SDL_MAIN_HANDLED

#define true 1
#define false 0

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#endif
#include <stdio.h>
#include <math.h>

#include "game.c"
#include "entity_component.c"
#include "utils.c"
#include "helper.c"
#include "systems.c"
#include "game_functions.c"
#include "loop.c"


int main(int argc, char* args[])
{
    srand(time(NULL));
    init();
    
    int start_time = SDL_GetTicks();
    unsigned int counted_frames = 0;
    
    while(g.running == true)
    {
        int frame_start_time = SDL_GetTicks();
        
        input();
        update();
        render();
                                    
#ifndef RELEASE
        show_framerate(start_time,counted_frames);
#endif
        cap_framerate(frame_start_time);
        
        counted_frames++;
    }
                
    cleanup();
    return 0;
}