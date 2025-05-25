/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:57 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/25 18:13:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	int				cycles;

	philo = (t_philosopher *)arg;
	cycles = 0;
	if (philo->sim->num_philos == 1)
		handle_single_philo(*(philo->sim), philo->id);
	while (cycles < 5)
	{
		if (philo->sim->num_meals != -1
			&& philo->meals_eaten >= philo->sim->num_meals)
			break ;
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		cycles++;
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
