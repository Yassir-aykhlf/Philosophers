/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:51 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/16 11:26:28 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_context	context;

	// Set up the context
	// Create the philophers thread
	// wait for the threads to finish
	init_start_time();
	if (argc > MAX_ARGS || argc < MIN_ARGS)
		error_exit(USAGE);
	init_context(argc, argv, &context);
	if (context.num_philos < 1 || context.time_to_die < 0
		|| context.time_to_eat < 0 || context.time_to_sleep < 0)
		error_exit(USAGE);
	simulate_philosopher(context);
	return (0);
}
