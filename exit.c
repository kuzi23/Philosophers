#include "philosophers.h"

int error_failure(char *str, char *details, t_table *table)
{
    if (table != NULL)
        free_table(table);
    return (msg(str, details, 0));
}

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

int msg(char *str, char *detail, int exit_no)
{
    if(!detail)
        printf(str, STR_PROG_NAME);
    else
        printf(str, STR_PROG_NAME, detail);
    return (exit_no);
}

void *error_null(char *str, char *details, t_table *table)
{
    if (table != NULL)
        free_table(table);
    msg(str, details, EXIT_FAILURE);
    return (NULL);
}