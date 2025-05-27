/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:35:44 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 15:35:43 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_stopped(t_philosopher *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->sim->sim_mutex);
	stopped = philo->sim->simulation_stop;
	pthread_mutex_unlock(&philo->sim->sim_mutex);
	if (stopped)
		return (EXIT_FAILURE);
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

void	update_last_meal_time(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	increase_meals_eaten(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}
