/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:57 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 12:34:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	must_stop_simulation(t_simulation *sim)
{
	if (sim->simulation_stop)
		return (true);
	for (int i = 0; i < sim->num_philos; i++)
	{
		if (sim->philosophers[i].meals_eaten < sim->num_meals)
			return (false);
	}
	return (true);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->sim->num_philos == 1)
		handle_single_philo(philo);
	while (true)
	{
		pthread_mutex_lock(&philo->sim->sim_mutex);
		if (must_stop_simulation(philo->sim))
		{
			pthread_mutex_unlock(&philo->sim->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->sim->sim_mutex);
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
