/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:51 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/25 17:22:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_lifecycle(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	philosopher_routine(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	init_start_time();
	if (argc > MAX_ARGS || argc < MIN_ARGS)
		error_exit(USAGE);
	if (init_simulation(argc, argv, &sim) != 0)
		error_exit("Error initializing simulation.\n");
	if (start_simulation(&sim) != 0)
		error_exit("Error starting simulation.\n");
	destroy_simulation(&sim);
	return (0);
}
