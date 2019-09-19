#ifndef __TIMER_H__
#define __TIMER_H__

#include "SDL.h"

typedef struct _timer
{
    //The clock time when the timer started
    int startTicks;
    //The ticks stored when the timer was paused
    int pausedTicks;
    //The timer status
    int paused;
    int started;

} Timer;


void init_timer(Timer *timer);
void start_timer(Timer *timer);
void stop_timer(Timer *timer);
void pause_timer(Timer *timer);
void unpause_timer(Timer *timer);

//Gets the timer's time
int get_ticks(Timer *timer);

//Checks the status of the timer
int is_started(Timer *timer);
int is_paused(Timer *timer);




#endif // __TIMER_H__
