/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:58 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 15:32:16 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philosopher *philo)
{
	if (simulation_stopped(philo))
		return ;
	if (take_forks(philo) != EXIT_SUCCESS)
		return ;
	print_eat_message(philo);
	precise_usleep(philo->sim->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->meal_mutex);
	increase_meals_eaten(philo);
	put_down_forks(philo);
}

void	philo_sleep(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->sim->time_to_sleep);
}

void	philo_think(t_philosopher *philo)
{
	unsigned long	think_time;

	print_status(philo, "is thinking");
	if (philo->sim->num_philos % 2 == 1)
	{
		think_time = (philo->sim->time_to_eat * 2) - philo->sim->time_to_sleep;
		if (think_time > 0 && think_time < 600)
		{
			if (think_time > 5)
				think_time -= 5;
			precise_usleep(think_time);
		}
	}
}

void	philo_die(t_philosopher *philo)
{
	printf("%lu %d has died\n", get_current_time(), philo->id);
	pthread_mutex_lock(&philo->sim->sim_mutex);
	philo->sim->simulation_stop = 1;
	pthread_mutex_unlock(&philo->sim->sim_mutex);
}
