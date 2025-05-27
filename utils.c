/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:11:25 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 15:33:44 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (0);
		str++;
	}
	return ((int)(result * sign));
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	validate_args(t_simulation *sim)
{
	if (sim->num_philos < 1 || sim->time_to_die < 0
		|| sim->time_to_eat < 0 || sim->time_to_sleep < 0)
		error_exit("Invalid arguments.\n");
}

void	check_args(int argc, char **argv)
{
	int	i;
	int	value;

	i = 1;
	if (argc < MIN_ARGS || argc > MAX_ARGS)
		error_exit(USAGE);
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		if (value <= 0)
			error_exit("Arguments must be positive integers.\n");
		if (i == 1 && value > 200)
			error_exit("Too many philosophers (max 200).\n");
		i++;
	}
}
