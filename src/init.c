#include "philo.h"

int	init_philos(t_infos *infos)
{
	int i;

	i = 0;
	infos->philos = malloc(sizeof(t_philosopher) * infos->nop);
	if (infos->philos == NULL)
		return (0);
	while (i < infos->nop)
	{
		infos->philos[i].infos = infos;
		infos->philos[i].id = i;
		infos->philos[i].time_to_die = infos->ttd;
		infos->philos[i].eats_count = 0;
		infos->philos[i].is_eating = 0;
		infos->philos[i].status = 0;
		infos->philos[i].r_fork = &infos->forks[i];
		infos->philos[i].l_fork = &infos->forks[(i + 1) % infos->nop];
        i++;
    }
	return (1);
}

int	init_forks(t_infos *infos)
{
	int i;

	i = 0;
	infos->forks = malloc (sizeof(pthread_mutex_t) * infos->nop);
	if (!infos->forks)
		return (0);
	while (i < infos->nop)
	{
		pthread_mutex_init(&infos->forks[i], NULL);
		i ++;
	}
	return (1);
}

int	init(t_infos *infos)
{
	infos->dead = 0;
	infos->finished = 0;
	if (init_forks(infos) == 0)
		return (0);
	if (init_philos(infos) == 0)
		return (0);
	return (1);
}