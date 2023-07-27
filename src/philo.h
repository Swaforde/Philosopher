/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/07/21 14:25:44 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>

typedef struct s_infos {
	int	dead;
	int finished;
	int nop;
	int64_t ttd;
	int64_t tte;
	int64_t tts;
	int64_t minimum_eat;
	struct s_philosopher *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t write;
} t_infos;

typedef struct s_philosopher {
	int id;
	int is_eating;
	int status;
	int eats_count;
	int64_t time_to_die;
	long int last_eat;
	t_infos *infos;
	pthread_mutex_t	lock;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;

} t_philosopher;

t_infos	parsing(int argc, char **argv);
int	checker(char **argv, int argc);
void init(t_infos *infos);

#endif