/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:57 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 10:27:57 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos_threads(t_simulation *sim)
{
	int	i;
	int	result;

	i = 0;
	while (i < sim->num_philos)
	{
		result = pthread_create(&sim->philosophers[i].thread, NULL,
				philosopher_routine, &sim->philosophers[i]);
		if (result != 0)
		{
			printf("Error creating thread for philosopher %d\n", i + 1);
			while (--i >= 0)
				pthread_join(sim->philosophers[i].thread, NULL);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	wait_for_philos_threads(t_simulation *sim)
{
	int	i;
	int	result;

	i = 0;
	while (i < sim->num_philos)
	{
		result = pthread_join(sim->philosophers[i].thread, NULL);
		if (result != 0)
		{
			printf("Error joining thread for philosopher %d\n", i + 1);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	start_simulation(t_simulation *sim)
{
	setup_last_meal_time(sim);
	if (create_philos_threads(sim) != 0)
		return (EXIT_FAILURE);
	if (create_monitor_thread(sim) != 0)
		return (EXIT_FAILURE);
	if (wait_for_philos_threads(sim) != 0)
		return (EXIT_FAILURE);
	if (wait_for_monitor_thread(sim) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	destroy_simulation(t_simulation *sim)
{
	int	i;

	if (sim->philosophers)
	{
		i = 0;
		while (i < sim->num_philos)
		{
			pthread_mutex_destroy(&sim->philosophers[i].meal_mutex);
			i++;
		}
		free(sim->philosophers);
		sim->philosophers = NULL;
	}
	destroy_forks(sim);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->sim_mutex);
}
