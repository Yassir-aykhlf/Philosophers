/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:09:09 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/26 17:56:35 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MICROS_PER_MILLI 1000
# define MONITOR_INTERVAL 1000
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
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
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
	pthread_t		monitor_thread;
	t_philosopher	*philosophers;
}	t_simulation;

void			error_exit(char *message);
int				ft_atoi(const char *str);
int				ft_strlen(const char *str);

void			*monitor_routine(void *arg);
bool			check_philosopher_death(t_philosopher *philo);
bool			check_all_philosophers_fed(t_simulation *sim);
int				create_monitor_thread(t_simulation *sim);
int				wait_for_monitor_thread(t_simulation *sim);

unsigned long	get_timestamp_ms(void);
unsigned long	*get_start_time(void);
unsigned long	get_current_time(void);
void			init_start_time(void);

int				init_simulation(int argc, char **argv, t_simulation *sim);
int				init_philosophers(t_simulation *sim);
int				init_mutexes(t_simulation *sim);
void			validate_args(t_simulation *sim);
int				simulation_stopped(t_philosopher *philo);

int				init_forks(t_simulation *sim);
void			destroy_forks(t_simulation *sim);

int				take_forks(t_philosopher *philo);
void			put_down_forks(t_philosopher *philo);
void			philo_eat(t_philosopher *philo);
void			philo_sleep(t_philosopher *philo);
void			philo_think(t_philosopher *philo);
void			philo_die(t_philosopher *philo);
void			*philosopher_lifecycle(void *arg);
void			*philosopher_routine(void *arg);
bool			must_stop_simulation(t_philosopher *philo);
int				create_philos_threads(t_simulation *sim);
int				wait_for_philos_threads(t_simulation *sim);
int				start_simulation(t_simulation *sim);
void			destroy_simulation(t_simulation *sim);

void			handle_single_philo(t_philosopher *philo);
void			print_eat_message(t_philosopher *philo);
void			update_last_meal_time(t_philosopher *philo);
void			increase_meals_eaten(t_philosopher *philo);

#endif
