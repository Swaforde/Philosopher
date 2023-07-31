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
	while (1)
	{
		printf ("Philosopher : %d is thinking\n", philosopher->id);
		usleep(rand() % 2000 + 1000);
		pthread_mutex_lock(philosopher->l_fork);
		if (pthread_mutex_trylock(philosopher->r_fork) == 0)
		{
			philosopher->is_eating = 1;
			printf("Philosopher : %d has taken left fork\n", philosopher->id);
			usleep(rand() % 2000 + 1000);
			philosopher->is_eating = 0;
			philosopher->eats_count ++;
			pthread_mutex_unlock(philosopher->r_fork);
		}
		pthread_mutex_unlock(philosopher->l_fork);
		if (philosopher->is_eating)
			sleep(rand() % 2000 + 1000);
	}
	return (NULL);
}