#include "philo.h"

t_table *init_table(int argc, char **argv) {
    t_table *table = malloc(sizeof(t_table));
    if (!table) return NULL;

    table->start_time = get_current_time_ms();
    table->num_of_philosophers = atoi(argv[1]);
    table->time_to_die = atoll(argv[2]);
    table->time_to_eat = atoll(argv[3]);
    table->time_to_sleep = atoll(argv[4]);
    table->num_of_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) : -1;

    table->philosophers = malloc(sizeof(t_philosopher) * table->num_of_philosophers);
    table->forks = malloc(sizeof(t_fork) * table->num_of_philosophers);
    if (!table->philosophers || !table->forks) return NULL;

    for (int i = 0; i < table->num_of_philosophers; i++) {
        table->philosophers[i].id = i + 1;
        table->philosophers[i].last_meal_time = 0;
        table->philosophers[i].left_fork = &table->forks[i];
        table->philosophers[i].right_fork = &table->forks[(i + 1) % table->num_of_philosophers];
        pthread_mutex_init(&table->forks[i].mutex, NULL);
    }

    return table;
}