/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:21:19 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 14:13:44 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_start_time(void)
{
	unsigned long	*start_time;

	start_time = get_start_time();
	*start_time = get_timestamp_ms();
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	sim->philosophers = malloc(sizeof(t_philosopher) * sim->num_philos);
	if (!sim->philosophers)
		return (EXIT_FAILURE);
	i = 0;
	while (i < sim->num_philos)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].last_meal_time = 0;
		sim->philosophers[i].is_eating = false;
		sim->philosophers[i].sim = sim;
		sim->philosophers[i].left_fork = i;
		sim->philosophers[i].right_fork = (i + 1) % sim->num_philos;
		if (pthread_mutex_init(&sim->philosophers[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->philosophers[i].meal_mutex);
			free(sim->philosophers);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_mutexes(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&sim->sim_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->print_mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_simulation(int argc, char **argv, t_simulation *sim)
{
	sim->num_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == MAX_ARGS)
		sim->num_meals = ft_atoi(argv[5]);
	else
		sim->num_meals = -1;
	sim->simulation_stop = 0;
	validate_args(sim);
	if (init_philosophers(sim) != 0)
		return (EXIT_FAILURE);
	if (init_forks(sim) != 0)
	{
		free(sim->philosophers);
		return (EXIT_FAILURE);
	}
	if (init_mutexes(sim) != 0)
	{
		destroy_forks(sim);
		free(sim->philosophers);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
