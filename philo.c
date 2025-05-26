/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:51 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 20:23:33 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	init_start_time();
	check_args(argc, argv);
	if (init_simulation(argc, argv, &sim) != 0)
		error_exit("Error initializing simulation.\n");
	if (start_simulation(&sim) != 0)
		error_exit("Error starting simulation.\n");
	destroy_simulation(&sim);
	return (0);
}
