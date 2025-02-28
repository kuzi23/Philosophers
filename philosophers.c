#include "philosophers.h"

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
    void    philo_sleep(t_table *table, time_t sleep_time)
}