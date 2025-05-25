/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:58 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/25 18:13:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philosopher *philo)
{
	printf("%lu %d has taken a fork\n", get_current_time(), philo->id);
	printf("%lu %d has taken a fork\n", get_current_time(), philo->id);
	printf("%lu %d is eating\n", get_current_time(), philo->id);
	usleep(philo->sim->time_to_eat * MICROS_PER_MILLI);
	philo->meals_eaten++;
}

void	philo_sleep(t_philosopher *philo)
{
	printf("%lu %d is sleeping\n", get_current_time(), philo->id);
	usleep(philo->sim->time_to_sleep * MICROS_PER_MILLI);
}

void	philo_think(t_philosopher *philo)
{
	printf("%lu %d is thinking\n", get_current_time(), philo->id);
	usleep(1000);
}
