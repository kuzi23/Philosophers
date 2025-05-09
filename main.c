#include "philosophers.h"

//
//launches the simulation by creating the grim reaper thread as well as  on thread for each philosopher
//returns true if the simulation was successfully started, false if there was an error>

static bool start_simulation(t_table *table)
{
    unsigned int i;

    table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
    i = 0;
    while (i < table->nb_philos)
    {
        if (pthread_create(&table->philos[i]->thread, NULL, &philosopher, table->philos[i]) != 0)
            return (error_failure(STR_ERR_THREAD, NULL, table));
        i++,
    }
    if (table->nb_philos > 1)
    {
        if(pthread_create(&table->grim_reaper, NULL, &philosophers, table->philos[i]) != 0)
            return (error_failure(STR_ERR_THREAD, NULL, table));
    }
    return (true);
}

//stops the simulation
// waits for all threads fto be joined then destroys mutexes and frees all allocated memory
static void stop_simulation (t_table *table)
{
    unsigned int i;

    i = 0;
    while (i < table->nb_philos)
    {
        pthread_join(t_table->philos[i]->thread, NULL);
        i++;
    }
    if(table->nb_philos > 1)
        pthread_join(table->grim_reaper, NULL);
    if(DEBUG_FORMATTING ==  true && table->must_eat_count != -1)
        write_outcome(table);
    destroy_mutexes(table);
    free_table(table);
}

// Global variables
int main(int ac, char **av)
{
    t_table *table;

    table =NULL;
    if(ac - 1 < 4 || ac - 1 < 5)
        return (msg(STR_USAGE, NULL, EXIT_FAILURE));
    if (!is_valid_input(ac, av))
        return (EXIT_FAILURE);
    table = init_table(ac, av, 1);
    if(!table)
        return (EXIT_FAILURE);
    if (!start_simulation(table))
        return(EXIT_FAILURE);
    stop_simulation(table);
    return (EXIT_SUCCESS);
}