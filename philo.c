/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:16:50 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/15 10:12:10 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define MAX_ARGS 6
# define MIN_ARGS 5
# define USAGE "Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"

int	ft_atoi(const char *str);

int	main(int argc, char **argv)
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;

	if (argc > MAX_ARGS || argc < MIN_ARGS)
		printf(USAGE);
	else
	{
		num_philos = ft_atoi(argv[1]);
		time_to_die = ft_atoi(argv[2]);
		time_to_eat = ft_atoi(argv[3]);
		time_to_sleep = ft_atoi(argv[4]);
		if (argc == MAX_ARGS)
			num_meals = ft_atoi(argv[5]);
		else
			num_meals = -1;
	}
}
