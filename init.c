/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:21:19 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/25 18:55:42 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_start_time(void)
{
	unsigned long	*start_time;

	start_time = get_start_time();
	*start_time = get_timestamp_ms();
}

void	validate_args(t_simulation *sim)
{
	if (sim->num_philos < 1 || sim->time_to_die < 0
		|| sim->time_to_eat < 0 || sim->time_to_sleep < 0)
		error_exit("Invalid arguments.\n");
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	sim->philosophers = malloc(sizeof(t_philosopher) * sim->num_philos);
	if (!sim->philosophers)
		return (1);
	i = 0;
	while (i < sim->num_philos)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].sim = sim;
		i++;
	}
	return (0);
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
	validate_args(sim);
	if (init_philosophers(sim) != 0)
		return (1);
	return (0);
}
