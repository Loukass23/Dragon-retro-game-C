#include "timer.h"

void init_timer(Timer *timer)
{
    timer->startTicks = 0;
    timer->started = 0;
}

void start_timer(Timer *timer)
{
    //Start the timer
    timer->started = 1;

    //Get the current clock time
    timer->startTicks = SDL_GetTicks();
}

void stop_timer(Timer *timer)
{
    //Stop the timer
    timer->started = 0;

    //Unpause the timer
    timer->paused = 0;
}

int get_ticks(Timer *timer)
{
    //If the timer is running
    if(timer->started)
    {
        //Return the current time minus the start time
        return SDL_GetTicks() - timer->startTicks;
    } else {
        //If the timer isn't running
        return 0;
    }
}

int is_started(Timer *timer)
{
    return timer->started;
}
