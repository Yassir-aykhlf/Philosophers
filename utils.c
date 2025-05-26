/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:11:25 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 20:23:55 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

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
		str++;
	}
	return (result * sign);
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

void	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < MIN_ARGS || argc > MAX_ARGS)
		error_exit(USAGE);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			error_exit("Arguments must be positive integers.\n");
		i++;
	}
}
