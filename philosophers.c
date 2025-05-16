#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

/* Constants */
#define MICROS_PER_MILLI 1000
#define MAX_ARGS 6
#define MIN_ARGS 5
#define USAGE "Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] \
[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"

/* Data Structures */
typedef struct s_context
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
}	t_context;

/* Utility Functions */
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

/* Time Functions */
unsigned long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * MICROS_PER_MILLI + (tv.tv_usec / MICROS_PER_MILLI));
}

unsigned long	*get_start_time(void)
{
	static unsigned long	start_time;

	return (&start_time);
}

unsigned long	get_current_time(void)
{
	return (get_timestamp_ms() - *get_start_time());
}

void	init_start_time(void)
{
	unsigned long	*start_time;

	start_time = get_start_time();
	*start_time = get_timestamp_ms();
}

/* Initialization Functions */
void	init_context(int argc, char **argv, t_context *context)
{
	context->num_philos = ft_atoi(argv[1]);
	context->time_to_die = ft_atoi(argv[2]);
	context->time_to_eat = ft_atoi(argv[3]);
	context->time_to_sleep = ft_atoi(argv[4]);
	if (argc == MAX_ARGS)
		context->num_meals = ft_atoi(argv[5]);
	else
		context->num_meals = -1;
}

/* Philosopher Actions */
void	simulate_eating(t_context context, int philo_id)
{
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

	while (meals_eaten < context.num_meals || context.num_meals == -1)
	{
		if (context.num_meals != -1)
			meals_eaten++;
		simulate_eating(context, philo_id);
		simulate_thinking(context, philo_id);
		simulate_sleeping(context, philo_id);
	}
	return (0);
}

/* Main Function */
int	main(int argc, char **argv)
{
	t_context	context;

	init_start_time();
	if (argc > MAX_ARGS || argc < MIN_ARGS)
		error_exit(USAGE);
	init_context(argc, argv, &context);
	if (context.num_philos < 1 || context.time_to_die < 0
		|| context.time_to_eat < 0 || context.time_to_sleep < 0)
		error_exit(USAGE);
	simulate_philosopher(context);
	return (0);
}
