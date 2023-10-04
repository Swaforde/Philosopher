#include "philo.h"


void	eat(t_philosopher *philosopher, t_table *table)
{
	pthread_mutex_lock(&philosopher->left_fork->mutex);
	log_action(philosopher, "has taken a left fork");
	pthread_mutex_lock(&philosopher->right_fork->mutex);
	log_action(philosopher, "has taken a right fork");

	log_action(philosopher, "is eating");
	usleep(table->time_to_eat * 1000);
	philosopher->last_meal_time = get_current_time_ms();

	pthread_mutex_unlock(&philosopher->left_fork->mutex);
	pthread_mutex_unlock(&philosopher->right_fork->mutex);
	log_action(philosopher, "has dropped the forks");

	philosopher->meals_eaten++;
}

void	sleep_and_think(t_philosopher *philosopher, t_table *table)
{
	log_action(philosopher, "is sleeping");
	usleep(table->time_to_sleep * 1000);
	log_action(philosopher, "is thinking");
}

void	*monitor_routine(void *arg)
{
	t_philo_context *context = (t_philo_context *)arg;
	t_philosopher *philosopher = context->philosopher;
	t_table *table = context->table;
	while (1) {
		usleep(100);
		if (get_current_time_ms() - philosopher->last_meal_time > table->time_to_die) {
			log_action(philosopher, "has died");
			exit(1);
		}
		if (table->num_of_times_each_philosopher_must_eat != -1 && 
			philosopher->meals_eaten >= table->num_of_times_each_philosopher_must_eat) {
			log_action(philosopher, "has eaten enough times");
			pthread_mutex_lock(&table->end_mutex);
			table->philosophers_done++;

			if (table->philosophers_done >= table->num_of_philosophers) {
				exit(0);
			}
			pthread_mutex_unlock(&table->end_mutex);
		}
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo_context	*context;
	t_philosopher *philosopher;
	t_table *table;

	context = (t_philo_context *)arg;
	philosopher = context->philosopher;
 	table = context->table;
	philosopher->last_meal_time = get_current_time_ms();
	while (1)
	{
		eat(philosopher, table);
		sleep_and_think(philosopher, table);
	}
}
