/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:09:09 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/25 17:22:09 by codespace        ###   ########.fr       */
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

typedef struct s_philosopher	t_philosopher;
typedef struct s_simulation		t_simulation;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal_time;
	pthread_t		thread;
	t_simulation	*sim;
}	t_philosopher;

typedef struct s_simulation
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	unsigned long	start_time;
	int				simulation_stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sim_mutex;
	t_philosopher	*philosophers;
}	t_simulation;

/* Utilities */
void			error_exit(char *message);
int				ft_atoi(const char *str);
int				ft_strlen(const char *str);

/* Time functions */
unsigned long	get_timestamp_ms(void);
unsigned long	*get_start_time(void);
unsigned long	get_current_time(void);
void			init_start_time(void);

/* sim functions */
int				init_simulation(int argc, char **argv, t_simulation *sim);

/* Simulation functions */
void			philo_eat(t_philosopher *philo);
void			philo_sleep(t_philosopher *philo);
void			philo_think(t_philosopher *philo);
void			philo_die(t_philosopher *philo);
void			*philosopher_lifecycle(void *arg);
void			*philosopher_routine(void *arg);
int				create_threads(t_simulation *sim);
int				wait_for_threads(t_simulation *sim);
int				start_simulation(t_simulation *sim);
void			destroy_simulation(t_simulation *sim);

/* Special Cases */
void			handle_single_philo(t_simulation sim, int philo_id);

#endif
