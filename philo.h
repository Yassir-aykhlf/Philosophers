/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:09:09 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/15 12:06:06 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MICROS_PER_MILLI 1000
# define MAX_ARGS 6
# define MIN_ARGS 5
# define USAGE "Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] \
[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_context
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
}	t_context;

void			error_exit(char *message);
int				ft_atoi(const char *str);
int				ft_strlen(const char *str);
unsigned long	get_timestamp_ms(void);
unsigned long	*get_start_time(void);
unsigned long	get_current_time(void);
void			init_start_time(void);
void			init_context(int argc, char **argv, t_context *context);

#endif
