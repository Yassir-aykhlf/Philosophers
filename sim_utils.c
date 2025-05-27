/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:35:44 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 10:27:57 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_stopped(t_philosopher *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->sim->sim_mutex);
	stopped = philo->sim->simulation_stop;
	pthread_mutex_unlock(&philo->sim->sim_mutex);
	return (stopped ? EXIT_FAILURE : EXIT_SUCCESS);
}

void	validate_args(t_simulation *sim)
{
	if (sim->num_philos < 1 || sim->time_to_die < 0
		|| sim->time_to_eat < 0 || sim->time_to_sleep < 0)
		error_exit("Invalid arguments.\n");
}

int	create_monitor_thread(t_simulation *sim)
{
	int	result;

	result = pthread_create(&sim->monitor_thread, NULL,
			monitor_routine, sim);
	if (result != 0)
	{
		printf("Error creating monitor thread\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	wait_for_monitor_thread(t_simulation *sim)
{
	if (pthread_join(sim->monitor_thread, NULL) != 0)
	{
		printf("Error joining monitor thread\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	setup_last_meal_time(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
		sim->philosophers[i].last_meal_time = get_current_time();
		pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
		i++;
	}
}
