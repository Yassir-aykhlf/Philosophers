/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:25:37 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/15 12:05:36 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * MICROS_PER_MILLI + (tv.tv_usec / MICROS_PER_MILLI));
}

unsigned long	*get_start_time(void)
{
	static unsigned long	start_time;

	return (&start_time);
}

unsigned long	get_current_time(void)
{
	return (get_timestamp_ms() - *get_start_time());
}
