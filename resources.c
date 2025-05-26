#include "philo.h"

int	init_forks(t_simulation *sim)
{
	int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_philos);
	if (!sim->forks)
		return (1);
	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->forks[i]);
			free(sim->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

void	destroy_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	if (sim->forks)
	{
		while (i < sim->num_philos)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
}