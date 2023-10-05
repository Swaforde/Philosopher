/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/07/21 14:25:44 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

long long	get_time(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((long long)(ct.tv_sec * 1000 + ct.tv_usec / 1000));
}

void	log_action(t_philosopher *philosopher, const char *action)
{
	long long	timestamp;

	timestamp = get_time() - philosopher->last_meal_time;
	printf("[%lld] Philosopher %d %s\n", timestamp, philosopher->id, action);
}
