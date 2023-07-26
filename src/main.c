/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/07/21 14:25:44 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_infos infos;
	t_philosopher *philosopher;

	infos = parsing(argc, argv);
	if (checker(argv, argc) == 0)
	{
		ft_printf("error\n");
		return (0);
	}
	philosopher = malloc(sizeof(t_philosopher) * infos.nop);
	if (philosopher == NULL)
		return (0);
	return (1);
}
