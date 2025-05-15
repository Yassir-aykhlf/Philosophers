/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:21:19 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/15 11:34:15 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_start_time(void)
{
	unsigned long	*start_time;

	start_time = get_start_time();
	*start_time = get_timestamp_ms();
}

void	init_context(int argc, char **argv, t_context *context)
{
	context->num_philos = ft_atoi(argv[1]);
	context->time_to_die = ft_atoi(argv[2]);
	context->time_to_eat = ft_atoi(argv[3]);
	context->time_to_sleep = ft_atoi(argv[4]);
	if (argc == MAX_ARGS)
		context->num_meals = ft_atoi(argv[5]);
	else
		context->num_meals = -1;
}
