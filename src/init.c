/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/07/21 14:25:44 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table (int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->start_time = get_time();
	table->n_p = 3;
	table->time_to_die = 400;
	table->time_to_eat = 100;
	table->time_to_sleep = 150;
	pthread_mutex_init(&table->end_mutex, NULL);
	table->philosophers_done = 0;
	table->max_eat = 2;
	table->philosophers = malloc(sizeof(t_philosopher) * table->n_p);
	table->forks = malloc(sizeof(t_fork) * table->n_p);
	if (!table->philosophers || !table->forks)
		return (NULL);
	i = 0;
	while (i < table->n_p)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].right_fork = &table->forks[(i + 1) % table->n_p];
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		i ++;
	}
	return (table);
}
