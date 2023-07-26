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
	printf("nop : %d\n", infos.nop);
	printf("ttd : %d\n", infos.ttd);
	printf("ttw : %d\n", infos.tte);
	printf("tts : %d\n", infos.tts);
	if (argc > 5)
		printf("minimum_eat : %d", infos.minimum_eat);
	return (1);
}
