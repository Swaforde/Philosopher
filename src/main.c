/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/10/16 14:46:47 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->forks)
	{
		i = 0;
		while (i < table->n_p)
		{
			pthread_mutex_destroy(&table->forks[i].mutex);
			i++;
		}
		free(table->forks);
	}
	if (table->philosophers)
		free(table->philosophers);
	pthread_mutex_destroy(&table->end_mutex);
	pthread_mutex_destroy(&table->check_mutex);
	pthread_mutex_destroy(&table->log_mutex);
	pthread_mutex_destroy(&table->order_mutex);
	free(table);
}

void	end(pthread_t *th, pthread_t *mo, t_table *ta, t_philo_context *co)
{
	free (th);
	free (mo);
	free_table(ta);
	free (co);
}

void	ct(t_table *ta, t_philo_context *da, pthread_t *th, pthread_t *mo)
{
	int	i;

	i = 0;
	pthread_create(mo, NULL, &monitor_routine, ta);
	while (i < ta->n_p)
	{
		da[i].philosopher = &ta->philosophers[i];
		da[i].table = ta;
		pthread_create(&th[i], NULL, &philo_routine, &da[i]);
		usleep(100);
		i ++;
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_table			*table;
	pthread_t		*threads;
	pthread_t		*monitor;
	t_philo_context	*philo_data;

	if (arg_check(argc, argv) == 0)
		return (0);
	i = 0;
	table = init_table(argc, argv);
	threads = malloc(sizeof(pthread_t) * table->n_p);
	if (!threads)
		return (0);
	monitor = malloc(sizeof(pthread_t));
	if (!monitor)
		return (0);
	philo_data = malloc(sizeof(t_philo_context) * table->n_p);
	if (!philo_data)
		return (0);
	ct(table, philo_data, threads, monitor);
	pthread_join(*monitor, NULL);
	while (i < table->n_p) { 
		pthread_join(threads[i], NULL);
		i++;
	}
	end(threads, monitor, table, philo_data);
	return (1);
}
