/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:58 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 17:45:13 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eat_message(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (philo->sim->simulation_stop == false)
		printf("%lu %d is eating\n", get_current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_mutex);
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
