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

	infos = parsing(argc, argv);
	if (checker(argv, argc) == 0)
	{
		ft_printf("error\n");
		return (0);
	}
	infos.philos = malloc(sizeof(t_philosopher) * infos.nop);
	if (infos.philos == NULL)
		return (0);
	init(&infos);
	return (1);
}
