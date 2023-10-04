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
	pthread_t		*monitor_threads;
	t_philo_context	*philosophers_context;

	i = 0;
	table = init_table(argc, argv);
	threads = malloc(sizeof(pthread_t) * table->num_of_philosophers);
	monitor_threads = malloc(sizeof(pthread_t) * table->num_of_philosophers);
	philosophers_context = malloc(sizeof(t_philo_context) * table->num_of_philosophers);
	if (!threads || !philosophers_context || !monitor_threads)
		exit(1);
	while (i < table->num_of_philosophers)
	{
		philosophers_context[i].philosopher = &table->philosophers[i];
		philosophers_context[i].table = table;
		pthread_create(&threads[i], NULL, &philosopher_routine, &philosophers_context[i]);
		pthread_create(&monitor_threads[i], NULL, &monitor_routine, &philosophers_context[i]);
		i ++;
	}
	i = 0;
	while (i < table->num_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		pthread_join(monitor_threads[i], NULL);
		i ++;
	}
	free(philosophers_context);
	free(threads);
	free(monitor_threads);
}
