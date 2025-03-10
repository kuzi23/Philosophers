#include "philosophers.h"

/*The lone philo routine:

This routine is invoked when there is only a single philosophers
a single philosphers only has one fork, and so cannot eat. the 
philosophers will pick it up that fork, wait as long as time_to_die and die 
This is a separate routine to make sure that the thread does not get
stuck waiting for the second fork in the eat routine*/

static void *lone_philo_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
    write_status(philo, false, GOT_FORK_1);
}
//the philosophers thread routtine the philosopsher must eat, sleep
//and think. In order to avoid conflicts between tghe philosophers threads, philosphers with an even id start by thinking, which delays their
//meal time by a small margi. thi allowas odd-id philosophers to grab their forks firs, avoiding deadlocks.

void *philosophers(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (philo->table->must_eat_count == 0)
        return (NULL);
    pthread_mutex_lock(&philo->meal_time_lock);
    philo->last_meal = philo->table->start_time;
    pthread_mutex_unlock(&philo->meal_time_lock);
    sim_start_delay(philo->table->start_time);
    if(philo->table->time_to_die == 0)
        return (NULL);
    if(philo->table->nb_philos == 1)
        return (lone_philo_routine(philo));
}