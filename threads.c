/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:57 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 20:29:54 by yaykhlf          ###   ########.fr       */
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
			return (1);
		}
		i++;
	}
	return (0);
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
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_simulation(t_simulation *sim)
{
	setup_last_meal_time(sim);
	if (create_philos_threads(sim) != 0)
		return (1);
	if (create_monitor_thread(sim) != 0)
		return (1);
	if (wait_for_philos_threads(sim) != 0)
		return (1);
	if (wait_for_monitor_thread(sim) != 0)
		return (1);
	return (0);
}

void	destroy_simulation(t_simulation *sim)
{
	destroy_forks(sim);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->sim_mutex);
	if (sim->philosophers)
		free(sim->philosophers);
}
