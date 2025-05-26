/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:57 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 13:30:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	must_stop_simulation(t_philosopher *philo)
{
	if (philo->sim->simulation_stop)
		return (true);
	if (philo->sim->num_meals != -1
		&& philo->meals_eaten >= philo->sim->num_meals)
		return (true);
	return (false);
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
		if (must_stop_simulation(philo))
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

void	philo_die(t_philosopher *philo)
{
	printf("%lu %d has died\n", get_current_time(), philo->id);
	pthread_mutex_lock(&philo->sim->print_mutex);
	philo->sim->simulation_stop = 1;
	pthread_mutex_unlock(&philo->sim->print_mutex);
}
