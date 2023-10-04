#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

long long get_current_time_ms() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (long long)(current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void log_action(t_philosopher *philosopher, const char *action) {
    long long timestamp = get_current_time_ms() - philosopher->last_meal_time;
    printf("[%lld] Philosopher %d %s\n", timestamp, philosopher->id, action);
}