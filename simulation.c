/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:58 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/25 18:56:57 by yaykhlf          ###   ########.fr       */
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

void	philo_die(t_philosopher *philo)
{
	printf("%lu %d has died\n", get_current_time(), philo->id);
	pthread_mutex_lock(&philo->sim->print_mutex);
	philo->sim->simulation_stop = 1;
	pthread_mutex_unlock(&philo->sim->print_mutex);
}

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

int	create_threads(t_simulation *sim)
{
	int	i;
	int	result;

	i = 0;
	while (i < sim->num_philos)
	{
		result = pthread_create(&sim->philosophers[i].thread, NULL,
				philosopher_routine, &sim->philosophers[i]);
		if (result != 0)
		{
			printf("Error creating thread for philosopher %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	wait_for_threads(t_simulation *sim)
{
	int	i;
	int	result;

	i = 0;
	while (i < sim->num_philos)
	{
		result = pthread_join(sim->philosophers[i].thread, NULL);
		if (result != 0)
		{
			printf("Error joining thread for philosopher %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_simulation(t_simulation *sim)
{
	if (create_threads(sim) != 0)
		return (1);
	if (wait_for_threads(sim) != 0)
		return (1);
	return (0);
}

void	destroy_simulation(t_simulation *sim)
{
	if (sim->philosophers)
		free(sim->philosophers);
}
