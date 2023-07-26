#include "philo.h"

t_infos	parsing(int argc, char **argv)
{
	t_infos infos;

	infos.nop = (int64_t) ft_atoi(argv[1]);
	infos.ttd = (int64_t) ft_atoi(argv[2]);
	infos.tte = (int64_t) ft_atoi(argv[3]);
	infos.tts = (int64_t) ft_atoi(argv[4]);
	if (argc > 5)
		infos.minimum_eat = ft_atoi(argv[5]);
	return (infos);
}
