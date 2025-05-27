/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:54:41 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 10:27:57 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_single_philo(t_philosopher *philo)
{
	if (philo->sim->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		precise_usleep(philo->sim->time_to_die);
		print_status(philo, "has died");
	}
}
