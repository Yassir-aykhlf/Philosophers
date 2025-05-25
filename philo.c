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

void	*philosopher_lifecycle(void *arg)
{
	t_context	*context;

	context = (t_context *)arg;
	simulate_philosopher(*context);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_context	context;
	pthread_t	philosopher_thread;

	init_start_time();
	if (argc > MAX_ARGS || argc < MIN_ARGS)
		error_exit(USAGE);
	init_context(argc, argv, &context);
	if (context.num_philos < 1 || context.time_to_die < 0
		|| context.time_to_eat < 0 || context.time_to_sleep < 0)
		error_exit(USAGE);
	if (pthread_create(&philosopher_thread, NULL, philosopher_lifecycle, &context) != 0)
		error_exit("Failed to create thread\\n");
	if (pthread_join(philosopher_thread, NULL) != 0)
		error_exit("Failed to join thread\\n");
	return (0);
}
