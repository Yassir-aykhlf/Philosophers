/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:16:50 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/15 12:05:24 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_context	context;

	init_start_time();
	if (argc > MAX_ARGS || argc < MIN_ARGS)
		error_exit(USAGE);
	else
		init_context(argc, argv, &context);
	while (1)
	{
		printf("ms: %lu\n", get_current_time());
		usleep(1000);
	}
}
