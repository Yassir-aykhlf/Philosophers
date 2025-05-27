/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:51 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 15:42:13 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	init_start_time();
	if (check_args(argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_simulation(argc, argv, &sim) != 0)
	{
		print_error("Error initializing simulation.\n");
		return (EXIT_FAILURE);
	}
	if (start_simulation(&sim) != 0)
	{
		print_error("Error starting simulation.\n");
		destroy_simulation(&sim);
		return (EXIT_FAILURE);
	}
	destroy_simulation(&sim);
	return (EXIT_SUCCESS);
}
