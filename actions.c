/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:58 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 10:27:57 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philosopher *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&philo->sim->forks[first_fork]);
	if (simulation_stopped(philo))
	{
		pthread_mutex_unlock(&philo->sim->forks[first_fork]);
		return (EXIT_FAILURE);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->sim->forks[second_fork]);
	if (simulation_stopped(philo))
	{
		pthread_mutex_unlock(&philo->sim->forks[first_fork]);
		pthread_mutex_unlock(&philo->sim->forks[second_fork]);
		return (EXIT_FAILURE);
	}
	print_status(philo, "has taken a fork");
	return (EXIT_SUCCESS);
}

void	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork]);
}

void	philo_eat(t_philosopher *philo)
{
	if (simulation_stopped(philo))
		return ;
	if (take_forks(philo) != EXIT_SUCCESS)
		return ;
	update_last_meal_time(philo);
	print_eat_message(philo);
	precise_usleep(philo->sim->time_to_eat);
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
			precise_usleep(think_time);
	}
}
