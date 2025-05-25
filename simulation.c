/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:58 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/16 10:58:04 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulate_eating(t_context context, int philo_id)
{
	printf("%lu %d has taken a fork\n", get_current_time(), philo_id);
	printf("%lu %d has taken a fork\n", get_current_time(), philo_id);
	printf("%lu %d is eating\n", get_current_time(), philo_id);
	usleep(context.time_to_eat * MICROS_PER_MILLI);
}

void	simulate_sleeping(t_context context, int philo_id)
{
	printf("%lu %d is sleeping\n", get_current_time(), philo_id);
	usleep(context.time_to_sleep * MICROS_PER_MILLI);
}

void	simulate_thinking(t_context context, int philo_id)
{
	(void)context;
	printf("%lu %d is thinking\n", get_current_time(), philo_id);
	usleep(1000);
}

void	simulate_dying(t_context context, int philo_id)
{
	(void)context;
	printf("%lu %d has died\n", get_current_time(), philo_id);
}

int	simulate_philosopher(t_context context)
{
	int	meals_eaten;
	int	philo_id;

	meals_eaten = 0;
	philo_id = 1;
	handle_single_philo(context, philo_id);
	while (meals_eaten < context.num_meals || context.num_meals == -1)
	{
		if (context.num_meals != -1)
			meals_eaten++;
		simulate_eating(context, philo_id);
		simulate_sleeping(context, philo_id);
		simulate_thinking(context, philo_id);
	}
	return (0);
}
