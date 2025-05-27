/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:11:25 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/27 15:42:13 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
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

int	validate_args(t_simulation *sim)
{
	if (sim->num_philos < 1 || sim->time_to_die < 0
		|| sim->time_to_eat < 0 || sim->time_to_sleep < 0)
	{
		print_error("Invalid arguments.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	value;

	i = 1;
	if (argc < MIN_ARGS || argc > MAX_ARGS)
	{
		print_error(USAGE);
		return (EXIT_FAILURE);
	}
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		if (value <= 0)
		{
			print_error("Arguments must be positive integers.\n");
			return (EXIT_FAILURE);
		}
		if (i == 1 && value > 200)
		{
			print_error("Too many philosophers (max 200).\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
