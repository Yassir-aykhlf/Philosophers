/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:09:09 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/25 14:18:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

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

/* Utilities */
void			error_exit(char *message);
int				ft_atoi(const char *str);
int				ft_strlen(const char *str);

/* Time functions */
unsigned long	get_timestamp_ms(void);
unsigned long	*get_start_time(void);
unsigned long	get_current_time(void);
void			init_start_time(void);

/* Context functions */
void			init_context(int argc, char **argv, t_context *context);

/* Simulation functions */
void			simulate_eating(t_context context, int philo_id);
void			simulate_sleeping(t_context context, int philo_id);
void			simulate_thinking(t_context context, int philo_id);
void			simulate_dying(t_context context, int philo_id);
int				simulate_philosopher(t_context context);

/* Special Cases */
void			handle_single_philo(t_context context, int philo_id);

#endif
