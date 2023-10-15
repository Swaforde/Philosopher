/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/07/21 14:25:44 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	int	i;
	long long	return_value;
	int	is_negative;

	i = 0;
	return_value = 0;
	is_negative = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_negative = 1;
		i ++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		return_value = return_value * 10 + (str[i++] - 48);
	if (is_negative == 1)
		return (return_value * -1);
	return (return_value);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	arg_check(int argc, char **argv)
{
	int	i;
	int	b;

	i = 1;
	b = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		while (b < ft_strlen(argv[i]))
		{
			if (b == 0 && (argv[i][b] == '-'))
				return (0);
			if (b == 0 && argv[i][b] == '+')
				b++;
			if (ft_isdigit(argv[i][b]) == 0)
				return (0);
			b++;
		}
		b = 0;
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return (0);
	return (1);
}

void	die_log(t_table *table, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < table->n_p) {
		if (table->philosophers[i].died == 1) {
			log_action(&table->philosophers[i], "died", table);
			break;
		}
		i ++;
	}
}
