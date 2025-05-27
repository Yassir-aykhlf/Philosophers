/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:32:48 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 15:37:38 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_monitor_thread(t_simulation *sim)
{
	int	result;

	result = pthread_create(&sim->monitor_thread, NULL,
			monitor_routine, sim);
	if (result != 0)
	{
		printf("Error creating monitor thread\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	wait_for_monitor_thread(t_simulation *sim)
{
	if (pthread_join(sim->monitor_thread, NULL) != 0)
	{
		printf("Error joining monitor thread\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
