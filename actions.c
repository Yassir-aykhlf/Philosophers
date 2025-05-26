/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:58 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 14:40:22 by codespace        ###   ########.fr       */
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
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (philo->sim->simulation_stop == false)
		printf("%lu %d has taken a fork\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_mutex);
	pthread_mutex_lock(&philo->sim->forks[second_fork]);
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (philo->sim->simulation_stop == false)
		printf("%lu %d has taken a fork\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_mutex);
	return (0);
}

void	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork]);
}

void	philo_eat(t_philosopher *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (philo->sim->simulation_stop == false)
	{
		printf("%lu %d is eating\n", get_current_time(), philo->id);
		philo->last_meal_time = get_current_time();
	}
	pthread_mutex_unlock(&philo->sim->print_mutex);
	usleep(philo->sim->time_to_eat * MICROS_PER_MILLI);
	philo->meals_eaten++;
	put_down_forks(philo);
}

void	philo_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (philo->sim->simulation_stop == false)
		printf("%lu %d is sleeping\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_mutex);
	usleep(philo->sim->time_to_sleep * MICROS_PER_MILLI);
}

void	philo_think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (philo->sim->simulation_stop == false)
		printf("%lu %d is thinking\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_mutex);
	usleep(1000);
}
