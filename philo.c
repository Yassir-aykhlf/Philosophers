/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:16:50 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/15 11:27:40 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str);

unsigned long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * MICROS_PER_MILLI + (tv.tv_usec / MICROS_PER_MILLI));
}

int	main(int argc, char **argv)
{
	t_context	context;

	init_start_time();
	while (1)
	{
		printf("ms: %lu\n", get_current_time());
		usleep(1000);
	}
	if (argc > MAX_ARGS || argc < MIN_ARGS)
		printf(USAGE);
	else
		init_context(argc, argv, &context);
}
