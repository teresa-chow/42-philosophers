/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:13:08 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/03 11:13:08 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	will_starve(t_philo **philo, unsigned long act_time_ms)
{
	unsigned long	timestamp;
	unsigned long	remaining;
	unsigned long	finish;

	if (!sim_active((*philo)->sim))
		return (0);
	timestamp = get_time_ms((*philo)->sim);
	finish = timestamp + act_time_ms;
	if ((finish - (*philo)->last_meal) > ((*philo)->sim->info.time_to_die))
	{
		remaining = ((*philo)->last_meal + (*philo)->sim->info.time_to_die) - timestamp;
		usleep_limit(remaining, (*philo)->sim);
		change_state(philo, STARVED);
		print_state((*philo)->sim, STARVED, timestamp, (*philo)->id);
		return (1);
	}
	return (0);
}

bool	starvation_checker(t_sim *sim, unsigned int i)
{
	handle_mutex(&sim->checker, LOCK);
	if (sim->philo[i].state == STARVED)
    {
		set_bool(&sim->status, &sim->active, 0);
		handle_mutex(&sim->checker, UNLOCK);
		return (1);
	}
	handle_mutex(&sim->checker, UNLOCK);
	return (0);
}

bool	sim_active(t_sim *sim)
{
	return (get_bool(&sim->status, &sim->active));
}

void	end_sim(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->info.n_philo)
	{
		handle_mutex(&sim->forks[i].mutex, DESTROY);
		i++;
	}
	free(sim->forks);
	if (sim->philo)
		free(sim->philo);
	handle_mutex(&sim->checker, DESTROY);
	handle_mutex(&sim->print, DESTROY);
	handle_mutex(&sim->status, DESTROY);
}
