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


	if (arg_check(argc, argv) == 0) {
		return (0);
	}
	i = 0;
	table = init_table(argc, argv);
	threads = malloc(sizeof(pthread_t) * table->n_p);
	monitor = malloc(sizeof(pthread_t));
	philo_data = malloc(sizeof(t_philo_context) * 4);
	if (!threads || !philo_data || !monitor)
		exit(1);
	pthread_create(monitor, NULL, &monitor_routine, table);
	while (i < table->n_p)
	{
		philo_data[i].philosopher = &table->philosophers[i];
		philo_data[i].table = table;
		pthread_create(&threads[i], NULL, &philo_routine, &philo_data[i]);
		i ++;
	}
	i = 0;
	pthread_join(*monitor, NULL);
	while (i < table->n_p)
	{
		pthread_join(threads[i], NULL);
		i ++;
	}
	return (1);
}
