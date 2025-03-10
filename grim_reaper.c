#include "philosophers.h"

/*set_sim_stop_flag:
    Sets the simulation stop flag to true or false. Only the grim
    reaper thread can set this flag. if the simulation stop flag is set to true,
    that means the simulation has met an end condition.
*/
static void set_sim_stop_flag(t_table *table, bool state)
{
    pthread_mutex_lock(&table->sim_stop_lock);
        table->sim_stop = state;
    pthread_mutex_unlock(&table->sim_stop_lock);
}

/*has simulation stooped:abort  
    check whather the simulation is at an end. The stop flag
    is protected by a mutex lock to allow any thread to check the simualtion status without conflict.
    Returns true if the simulation stop flag is set to true
    false if the flag is set to false.
*/
bool has_simulation_stopped(t_table *table)
{
    bool r;

    r = false;
    pthread_mutex_lock(&table->sim_stop_lock);
    if(table->sim_stop == true)
        r = true;
    pthread_mutex_unlock(&table->sim_stop_lock);
    return (r);
}

/*Kill_philo:
    Checks if the philospher must be killed by comparing the time since the philosophera last meal and the time_to_die paramter.
    if it is time for the philosopher to die, sets the simulation stop. 
    flag and displays the death status. 
    Returns true if the philosopher has been killed, false if not. 
*/
static bool kill_philo(t_philo *philo)
{
    time_t time;

    time = get_time_in_ms();
    if((time -  philo->last_meal) >= philo->table->time_to_die)
    {
        set_sim_stop_flag(philo->table, true);
        write_status(philo, true, DIED);
        pthread_mutex_unlock(&philo->meal_time_lock);
        return (true);
    }
    return (false);
}

/*end_condition_reached:
    checks each philosophers to see if one of the two end conditions
    has been reached.Stops the simulation if a philospher needs
    to be killed, or if every philosopgher has eaten enough.
    Returns True if an end condition has been reached, false if not.
*/
static  bool end_condition_reached(t_table *table)
{
    unsigned int i;
    bool    all_ate_enough;

    all_ate_enough = true;
    i = 0;
    while(i < table->nb_philos)
    {
        pthread_mutex_lock(&table->philos[i]->meal_time_lock);
        if (kill_philo(table->philos[i]))
            return (true);
        if (table->must_eat_count != -1)
            if (table->philos[i]->times_ate
                <(unsigned int)table->must_eat_count)
                all_ate_enough = false;
        pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
        i++;
    }
    if (table->must_eat_count != -1 && all_ate_enough == true)
    {
        set_sim_stop_flag(table, true);
        return (true);
    }
    return (false);
}

/*grim_reaper:
        the grim reaper thread's routine, checks if a philospher must 
        be killed and if all philosophers ate enough. If one of tghise two end condtions are reached it stops the simulation.
*/
void *grim_reaper(void *date)
{
    t_table  *table;

    table = (t_table *)data;
    if (table->must_eat_count == 0)
        return (NULL);
    set_sim_stop_flag(table, false);
    sim_start_delay(table->start_time);
    while(true)
    {
        if(end_condition_reached(table) == true)
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}