#include "philo.h"

int arg_is_null(char **argv, int argc)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
			return (0);
		i ++;
	}
	return (1);
}

int arg_is_num(char **argv, int argc)
{
	int i;
	int x;

	i = 1;
	x = 0;
	while (i < argc)
	{
		while (x < ft_strlen(argv[i]))
		{
			if (ft_isdigit(argv[i][x]) == 0)
				return (0);
			x ++;
		}
		x = 0;
		i ++;
	}
	return (1);
}

int checker(char **argv, int argc)
{
	if (arg_is_null(argv, argc) == 0)
		return (0);
	if (arg_is_num(argv, argc) == 0)
		return (0);
	return (1);
}