#include "philosophers.h"

/* error failure: 
    Frees any allocated to the console. Returns the provided exit number
    used for error management.
*/
int error_failure(char *str, char *details, t_table *table)
{
    if (table != NULL)
        free_table(table);
    return (msg(str, details, 0));
}

/*Free table:
    Frees all of the memory allocated by the program.
    Returns a Null pointer if there is nothing to free
    or when all memory has been freed.
*/
void *free_table(t_table *table)
{
    unsigned int i;
    if(!table)
        return (NULL);
    if (table->fork_locks != NULL)
        free(table->fork_locks);
    if(table->philos != NULL)
    {
        i = 0;
        while(i < table->nb_philos)
        {
            if (table->philos[i] != NULL)
                free(table->philos[i]);
            i++;
        }
        free(table->philos);
    }
    free(table);
    return (NULL);
}


/*Destroys every mitexes created by the program; fork lock, meal locks
    the write and somluation stopper lock.
*/
void destroy_mutexes(t_table *table)
{
    unsigned int  i;
    
    i = 0;
    while(i < table->nb_philos)
    {
        pthread_mutex_destroy(&table->fork_locks[i]);
        pthread_mutex_destroy(&table->philos[i]->meal_time_lock);\
        i++;
    }
    pthread_mutex_destroy(&table->write_lock);
    pthread_mutex_destroy(&table->sim_stop_lock);
}

/*writes the message to the consol, Returns teh provided the exit number
used for error management*/
int msg(char *str, char *detail, int exit_no)
{
    if(!detail)
        printf(str, STR_PROG_NAME);
    else
        printf(str, STR_PROG_NAME, detail);
    return (exit_no);
}

/*error null: 
        Frees any allocated memory, prints an error message and returns a NULL pointer.
        used for error management during initialization. 
*/
void *error_null(char *str, char *details, t_table *table)
{
    if (table != NULL)
        free_table(table);
    msg(str, details, EXIT_FAILURE);
    return (NULL);
}