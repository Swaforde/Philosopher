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
	int nop;
	int ttd;
	int tte;
	int tts;
	int minimum_eat;
} t_infos;

typedef struct s_philosopher {
	int id;
	int is_eating;
	long int last_eat;
	struct t_arguments *arguments;
	pthread_t pthread;

} t_philosopher;

t_infos	parsing(int argc, char **argv);
int checker(char **argv, int argc);

#endif