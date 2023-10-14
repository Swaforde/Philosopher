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

int	eat(t_philosopher *philosopher, t_table *table)
{
	if (philosopher->id % 2 != 0)
	{
		pthread_mutex_lock(&philosopher->left_fork->mutex);
		if (table->stop != 1)
			log_action(philosopher, "has taken a fork", table);
		pthread_mutex_lock(&philosopher->right_fork->mutex);
		if (table->stop != 1)
			log_action(philosopher, "has taken a fork", table);
	}
	else
	{
		pthread_mutex_lock(&philosopher->right_fork->mutex);
		if (table->stop != 1)
			log_action(philosopher, "has taken a fork", table);
		pthread_mutex_lock(&philosopher->left_fork->mutex);
		if (table->stop != 1)
			log_action(philosopher, "has taken a fork", table);
	}
	if (table->stop != 1)
	{
		log_action(philosopher, "is eating", table);
		philosopher->last_meal_time = get_time();
		if(custom_sleep(table->time_to_eat, philosopher, table))
			return 1;
	}
	pthread_mutex_unlock(&philosopher->left_fork->mutex);
	pthread_mutex_unlock(&philosopher->right_fork->mutex);
	philosopher->meals_eaten++;
	return 0;
}

int	sleep_and_think(t_philosopher *philosopher, t_table *table)
{
	if (table->stop != 1)
		log_action(philosopher, "is sleeping", table);
	if(custom_sleep(table->time_to_sleep, philosopher, table))
		return 1;
	if (table->stop != 1)
		log_action(philosopher, "is thinking", table);
	return 0;
}

int	custom_sleep(int ms, t_philosopher *philo, t_table *table)
{
	long long start;
	long long end;

	start = get_time();
	end = get_time();
	while (end - start < ms)
	{
		usleep(20);
		end = get_time();
		if (end - philo->last_meal_time > table->time_to_die)
		{
			philo->died = 1;
			pthread_mutex_unlock(&philo->left_fork->mutex);
			pthread_mutex_unlock(&philo->right_fork->mutex);
			return 1;
		}
	}
	return 0;
}

void	monitor_loop(t_table *table)
{
	t_philosopher	philo;
	int				i;

	usleep(100);
	while (table->stop == 0)
	{
		i = 0;
		while (i < table->n_p)
		{
			t_philosopher *philo = &table->philosophers[i++];
			if (philo->died == 1)
			{
				die_log(table, philo);
				table->stop = 1;
				return ;
			}
			if (table->max_eat != -1 && philo->meals_eaten >= table->max_eat)
			{
				pthread_mutex_lock(&table->end_mutex);
				table->philosophers_done++;
				if (table->philosophers_done >= table->n_p)
					return ;
				pthread_mutex_unlock(&table->end_mutex);
			}
		}
	}
}

void	*monitor_routine(void *arg)
{
	t_table			*table;

	table = (t_table *)arg;
	monitor_loop(table);
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
	while (philosopher->died != 1 && (philosopher->meals_eaten < table->max_eat || table->max_eat == -1))
	{
		if(eat(philosopher, table))
			break;
		if(sleep_and_think(philosopher, table))
			break;

	}
	return (NULL);
}
