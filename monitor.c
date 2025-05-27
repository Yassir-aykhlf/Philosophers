/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:04:13 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 15:25:10 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philosopher_death(t_philosopher *philo)
{
	unsigned long	current_time;
	unsigned long	time_since_last_meal;
	bool			currently_eating;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->meal_mutex);
	time_since_last_meal = current_time - philo->last_meal_time;
	currently_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_since_last_meal >= (unsigned long)(philo->sim->time_to_die + 5)
		&& !currently_eating)
	{
		pthread_mutex_lock(&philo->sim->print_mutex);
		if (philo->sim->simulation_stop == false)
		{
			printf("%lu %d has died\n", current_time, philo->id);
			pthread_mutex_lock(&philo->sim->sim_mutex);
			philo->sim->simulation_stop = true;
			pthread_mutex_unlock(&philo->sim->sim_mutex);
		}
		pthread_mutex_unlock(&philo->sim->print_mutex);
		return (true);
	}
	return (false);
}

bool	check_all_philosophers_fed(t_simulation *sim)
{
	int	i;
	int	fed_philos;

	if (sim->num_meals == -1)
		return (false);
	fed_philos = 0;
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
		if (sim->philosophers[i].meals_eaten >= sim->num_meals)
			fed_philos++;
		pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
		i++;
	}
	if (fed_philos == sim->num_philos)
	{
		pthread_mutex_lock(&sim->sim_mutex);
		sim->simulation_stop = true;
		pthread_mutex_unlock(&sim->sim_mutex);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	int				i;
	t_simulation	*sim;
	bool			should_stop;

	sim = (t_simulation *)arg;
	while (true)
	{
		pthread_mutex_lock(&sim->sim_mutex);
		should_stop = sim->simulation_stop;
		pthread_mutex_unlock(&sim->sim_mutex);
		if (should_stop)
			break ;
		if (check_all_philosophers_fed(sim))
			break ;
		i = 0;
		while (i < sim->num_philos)
		{
			if (check_philosopher_death(&sim->philosophers[i]))
				break ;
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
