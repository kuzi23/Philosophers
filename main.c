#include "philosophers.h"

static bool start_simulation(t_table *table)
{
    unsigned int i;

    table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
    i = 0;
    while (i < table->nb_philos)
    {
        if (pthread_create(&table->philos[i]->thread, NULL, &philosopher, ))
    }
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
    
}