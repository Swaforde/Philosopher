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

void eat(t_philosopher *philosopher, t_table *table)
{
    if (philosopher->id % 2 != 0)
	{    
        pthread_mutex_lock(&philosopher->left_fork->mutex);
        if (table->stop != 1)
            log_action(philosopher, "has taken a fork", table);
        pthread_mutex_lock(&philosopher->right_fork->mutex);
        if (table->stop != 1)
            log_action(philosopher, "has taken a fork", table);
    } else
	{
        pthread_mutex_lock(&philosopher->right_fork->mutex);
        if (table->stop != 1)
            log_action(philosopher, "has taken a fork", table);
        pthread_mutex_lock(&philosopher->left_fork->mutex);
        if (table->stop != 1)
            log_action(philosopher, "has taken a fork", table);
    }
    if (table->stop != 1)
        log_action(philosopher, "is eating", table);
    usleep(table->time_to_eat * 1000);
    philosopher->last_meal_time = get_time();
    pthread_mutex_unlock(&philosopher->left_fork->mutex);
    pthread_mutex_unlock(&philosopher->right_fork->mutex);
    philosopher->meals_eaten++;
}




void	sleep_and_think(t_philosopher *philosopher, t_table *table)
{
	if (table->stop != 1) {
		log_action(philosopher, "is sleeping", table);
	}
	usleep(table->time_to_sleep * 1000);
	if (table->stop != 1) {
		log_action(philosopher, "is thinking", table);
	}
}

void	monitor_loop(t_table *table)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (1)
	{
		usleep(100);
		while (x < table->n_p)
		{
			t_philosopher philo = table->philosophers[x];

			if (get_time() - philo.last_meal_time > table->time_to_die)
			{
				if (table->stop == 0) {
					log_action(&philo, "died", table);
					while (i < table->n_p) {
						table->philosophers[i].died = 1;
						i ++;
					}
					table->stop = 1;
				}
				return ;
			}
			if (table->max_eat != -1 && philo.meals_eaten >= table->max_eat)
			{
				pthread_mutex_lock(&table->end_mutex);
				table->philosophers_done++;
				if (table->philosophers_done >= table->n_p)
					return ;
				pthread_mutex_unlock(&table->end_mutex);
			}
			x ++;
		}
		x = 0;
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
		eat(philosopher, table);
		sleep_and_think(philosopher, table);
	}
	return (NULL);
}
