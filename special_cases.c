/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:54:41 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 15:45:00 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_single_philo(t_philosopher *philo)
{
	if (philo->sim->num_philos == 1)
	{
		pthread_mutex_lock(&philo->sim->print_mutex);
		printf("%lu %d has taken a fork\n", get_current_time(), philo->id);
		pthread_mutex_unlock(&philo->sim->print_mutex);
		usleep(philo->sim->time_to_die * MICROS_PER_MILLI);
		pthread_mutex_lock(&philo->sim->print_mutex);
		printf("%lu %d has died\n", get_current_time(), philo->id);
		pthread_mutex_unlock(&philo->sim->print_mutex);
	}
}
