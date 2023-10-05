/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/07/21 14:25:44 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				i;
	t_table			*table;
	pthread_t		*threads;
	pthread_t		*monitor;
	t_philo_context	*philo_data;

	i = 0;
	table = init_table(argc, argv);
	threads = malloc(sizeof(pthread_t) * table->n_p);
	monitor = malloc(sizeof(pthread_t) * table->n_p);
	philo_data = malloc(sizeof(t_philo_context) * table->n_p);
	if (!threads || !philo_data || !monitor)
		exit(1);
	while (i < table->n_p)
	{
		philo_data[i].philosopher = &table->philosophers[i];
		philo_data[i].table = table;
		pthread_create(&threads[i], NULL, &philo_routine, &philo_data[i]);
		pthread_create(&monitor[i], NULL, &monitor_routine, &philo_data[i]);
		i ++;
	}
	i = 0;
	while (i < table->n_p)
	{
		pthread_join(threads[i], NULL);
		pthread_join(monitor[i], NULL);
		i ++;
	}
	exit(0);
}
