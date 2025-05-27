/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:30:16 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 15:32:30 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_fork_order(t_philosopher *philo,
			int *first_fork, int *second_fork)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

int	take_forks(t_philosopher *philo)
{
	int	first_fork;
	int	second_fork;

	assign_fork_order(philo, &first_fork, &second_fork);
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
	pthread_mutex_lock(&philo->meal_mutex);
	philo->is_eating = true;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	return (EXIT_SUCCESS);
}

void	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork]);
}
