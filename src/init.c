/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/10/16 12:25:35 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_value(t_table *table, char **argv)
{
	table->stop = 0;
	table->start_time = get_time();
	table->n_p = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->start_time = get_time();
	table->philosophers_done = 0;
	pthread_mutex_init(&table->end_mutex, NULL);
	pthread_mutex_init(&table->log_mutex, NULL);
	pthread_mutex_init(&table->check_mutex, NULL);
	pthread_mutex_init(&table->order_mutex, NULL);
}

void	set_philo_value(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_p)
	{
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].died = 0;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].has_left_fork = 0;
		table->philosophers[i].has_right_fork = 0;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].right_fork = &table->forks[(i + 1) % table->n_p];
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		i ++;
	}
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	int		i;	

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	set_value(table, argv);
	if (argc == 6)
		table->max_eat = ft_atoi(argv[5]);
	else
		table->max_eat = -1;
	table->philosophers = malloc(sizeof(t_philosopher) * table->n_p);
	table->forks = malloc(sizeof(t_fork) * table->n_p);
	if (!table->philosophers || !table->forks)
		return (NULL);
	set_philo_value(table);
	return (table);
}
