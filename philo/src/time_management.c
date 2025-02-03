#include "../include/philosophers.h"

unsigned long	get_time_ms(t_sim *sim)
{
	struct timeval	now;
	unsigned long	timestamp;

	gettimeofday(&now, NULL);
//	handle_mutex(&sim->time, LOCK);
	timestamp = (now.tv_sec * 1000 + now.tv_usec / 1000) - sim->start;
//	handle_mutex(&sim->time, UNLOCK);
	return (timestamp);
}

void	usleep_limit(unsigned long time_ms, t_sim *sim)
{
	unsigned long	act_start;
	unsigned long	elapsed;
	unsigned long	remaining;

	act_start = get_time_ms(sim);
	while ((get_time_ms(sim) - act_start) > time_ms)
	{
		if (!sim_active(sim))
			break ;
		elapsed = get_time_ms(sim) - act_start;
		remaining = time_ms - elapsed;
        if (remaining > 1)
            usleep((time_ms * 1000) / 2);
        else
        {
            while ((get_time_ms(sim) - act_start) > time_ms)
                ;
        }
	}
}