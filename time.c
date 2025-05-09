#include "philosophers.h"

time_t get_time_in_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_sec / 1000));
}

/* philo_sleep:
*	Pauses the philosopher thread for a certain amount of time in miliseconds.
*	Periodically checks to see if the simulation has ended during the sleep
*	time and cuts the sleep short if it has.
*/
void    philo_sleep(t_table *table, time_t sleep_time)
{
    time_t  wake_up;

    wake_up = get_time_in_ms() + sleep_time;
    while (get_time_in_ms() < wake_up)
    {
        if (has_simulation_stopped(table))
            break;
        usleep(100);
    }
}

/*sime_start_delay:
    waits for a small delay at the beginning of each threads execution
    so that all threads start at the same time with the same start time
    reference. This ensures the grim reaper thread is synchronized with the
    philosopher threads.
*/
void sim_start_delay(time_t start_time)
{
    while(get_time_in_ms() < start_time)
        continue;
}