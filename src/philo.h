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

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>

# define RESET_COLOR "\033[0m"
# define RED_COLOR "\033[31m"
# define GREEN_COLOR "\033[32m"
# define YELLOW_COLOR "\033[33m"
# define BLUE_COLOR "\033[34m"
# define MAGENTA_COLOR "\033[35m"
# define CYAN_COLOR "\033[36m"
# define WHITE_COLOR "\033[37m"

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
} t_infos;

typedef struct s_philosopher {
	int id;
	int is_eating;
	int status;
	int eats_count;
	int64_t time_to_die;
	long int last_eat;
	t_infos *infos;
	pthread_t thread;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;

} t_philosopher;

t_infos	parsing(int argc, char **argv);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	checker(char **argv, int argc);
int init(t_infos *infos);
int	ft_strlen(const char *str);
void *routine(void * data);

#endif