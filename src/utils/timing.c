/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:00:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 10:27:57 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(unsigned long duration_ms)
{
	unsigned long	start;
	unsigned long	elapsed;

	start = get_current_time();
	while (1)
	{
		elapsed = get_current_time() - start;
		if (elapsed >= duration_ms)
			break ;
		if (duration_ms - elapsed > 10)
			usleep((duration_ms - elapsed) * 500);
		else
			usleep(100);
	}
}
