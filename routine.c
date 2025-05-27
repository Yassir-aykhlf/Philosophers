/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:57 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 10:39:46 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	must_stop_simulation(t_philosopher *philo)
{
	int		stop;
	int		meals_eaten;

	pthread_mutex_lock(&philo->sim->sim_mutex);
	stop = philo->sim->simulation_stop;
	pthread_mutex_unlock(&philo->sim->sim_mutex);
	if (stop)
		return (true);
	if (philo->sim->num_meals != -1)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		meals_eaten = philo->meals_eaten;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (meals_eaten >= philo->sim->num_meals)
			return (true);
	}
	return (false);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->sim->num_philos == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(1);
	while (true)
	{
		if (must_stop_simulation(philo))
			break ;
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_die(t_philosopher *philo)
{
	printf("%lu %d has died\n", get_current_time(), philo->id);
	pthread_mutex_lock(&philo->sim->sim_mutex);
	philo->sim->simulation_stop = 1;
	pthread_mutex_unlock(&philo->sim->sim_mutex);
}
