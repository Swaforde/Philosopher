/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/10/17 11:13:35 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	custom_sleep(int ms, t_philosopher *philo, t_table *table)
{
	long long	start;
	long long	end;

	start = get_time();
	end = get_time();
	while (end - start < ms)
	{
		end = get_time();
		if (end - philo->last_meal_time > table->time_to_die)
		{
			pthread_mutex_unlock(&philo->left_fork->mutex);
			pthread_mutex_unlock(&philo->right_fork->mutex);
			philo->died = 1;
			table->stop = 1;
			return (1);
		}
		usleep(5);
	}
	return (0);
}
