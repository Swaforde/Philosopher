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

typedef struct s_fork {
    pthread_mutex_t mutex;
}              t_fork;

typedef struct s_table t_table;

typedef struct s_philosopher {
    int             died;
    int             id;
    long long       last_meal_time;
    int             meals_eaten;
    t_fork          *left_fork;
    t_fork          *right_fork;
    t_table         *table;
}              t_philosopher;

typedef struct s_table {
    int             stop;
    int             philosophers_done;
    pthread_mutex_t end_mutex;
    int             n_p;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    int            	max_eat;
    long long       start_time;
    t_philosopher   *philosophers;
    t_fork          *forks;
}              t_table;


typedef struct  s_philo_context {
    t_philosopher *philosopher;
    t_table      *table;
}               t_philo_context;

void *philo_routine(void *arg);
void *monitor_routine(void *arg);
long long get_time();
int	ft_atoi(const char *str);
void log_action(t_philosopher *philosopher, const char *action, t_table *table);
t_table *init_table(int argc, char **argv);

#endif