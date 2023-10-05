/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/07/21 14:25:44 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philosopher, t_table *table)
{
	pthread_mutex_lock(&philosopher->left_fork->mutex);
	log_action(philosopher, "has taken a left fork");
	pthread_mutex_lock(&philosopher->right_fork->mutex);
	log_action(philosopher, "has taken a right fork");
	log_action(philosopher, "is eating");
	usleep(table->time_to_eat * 1000);
	philosopher->last_meal_time = get_time();
	pthread_mutex_unlock(&philosopher->left_fork->mutex);
	pthread_mutex_unlock(&philosopher->right_fork->mutex);
	log_action(philosopher, "has dropped the forks");
	philosopher->meals_eaten++;
}

void	sleep_and_think(t_philosopher *philosopher, t_table *table)
{
	log_action(philosopher, "is sleeping");
	usleep(table->time_to_sleep * 1000);
	log_action(philosopher, "is thinking");
}

void	monitor_loop(t_philosopher *philo, t_table *table)
{
	while (1)
	{
		usleep(100);
		if (get_time() - philo->last_meal_time > table->time_to_die)
		{
			log_action(philo, "has died");
			exit(1);
		}
		if (table->max_eat != -1 && philo->meals_eaten >= table->max_eat)
		{
			log_action(philo, "has eaten enough times");
			pthread_mutex_lock(&table->end_mutex);
			table->philosophers_done++;
			if (table->philosophers_done >= table->n_p)
			{
				exit(0);
			}
			pthread_mutex_unlock(&table->end_mutex);
		}
	}
}

void	*monitor_routine(void *arg)
{
	t_philo_context	*context;
	t_philosopher	*philosopher;
	t_table			*table;

	context = (t_philo_context *)arg;
	philosopher = context->philosopher;
	table = context->table;
	monitor_loop(philosopher, table);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo_context	*context;
	t_philosopher	*philosopher;
	t_table			*table;

	context = (t_philo_context *)arg;
	philosopher = context->philosopher;
	table = context->table;
	philosopher->last_meal_time = get_time();
	while (1)
	{
		eat(philosopher, table);
		sleep_and_think(philosopher, table);
	}
}
