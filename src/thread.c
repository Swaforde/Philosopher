#include "philo.h"

int get_random (int max)
{
   double val;
 
   val = (double) max * rand ();
   val = val / (RAND_MAX + 1.0);
 
   return ((int) val);
}

void	*routine(void * data)
{
	t_philosopher *philosopher = (t_philosopher *)data;
	for (int i = 0; i < 10; i++)
		printf(RED_COLOR "[LOG] ->\n" RESET_COLOR);
	return (NULL);
}