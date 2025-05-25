#include "philo.h"

void	handle_single_philo(t_simulation sim, int philo_id)
{
    if (sim.num_philos == 1)
    {
        printf("%lu %d has taken a fork\n", get_current_time(), philo_id);
        usleep(sim.time_to_die * MICROS_PER_MILLI);
        printf("%lu %d has died\n", get_current_time(), philo_id);
        exit(EXIT_SUCCESS);
    }
}