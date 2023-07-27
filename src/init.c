#include "philo.h"

void init_philos(t_infos *infos)
{
    int i;

    i = 0;
    while (i < infos->nop)
    {
        infos->philos[i].infos = infos;
        infos->philos[i].id = i + 1;
        infos->philos[i].time_to_die = infos->ttd;
        infos->philos[i].eats_count = 0;
        infos->philos[i].is_eating = 0;
        infos->philos[i].status = 0;
        pthread_mutex_init(&infos->philos[i].lock, NULL);
        i++;
    }
}

void init(t_infos *infos)
{
    infos->dead = 0;
    infos->finished = 0;

    pthread_mutex_init(&infos->write, NULL);
    pthread_mutex_init(&infos->lock, NULL);
    init_philos(infos);
}