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
		remaining = ((*philo)->last_meal + (*philo)->sim->info.time_to_die)
			- timestamp;
		usleep_limit(remaining, (*philo)->sim);
		change_state(philo, STARVED);
		return (1);
	}
	return (0);
}

void	starvation_checker(t_sim *sim, unsigned int i)
{
	if (sim_active(sim))
	{
		handle_mutex(&sim->philo[i].mutex, LOCK);
		if (sim->philo[i].state == STARVED)
		{
			print_state(sim, STARVED, sim->philo[i].id);
			set_bool(&sim->status, &sim->active, 0);
		}
		handle_mutex(&sim->philo[i].mutex, UNLOCK);
	}
	return ;
}

void	philos_full_checker(t_sim *sim)
{
	unsigned int i;
	bool	full;

	i = 0;
	full = 1;
	while (i < sim->info.n_philo)
	{
		if (sim->philo[i].full != 1) //data race
			full = 0;
		i++;
	}
	if (full == 1)
	{
		handle_mutex(&sim->print, LOCK);
		printf(GRN "Simulation stopped: all" NC);
		printf(GRN " philosophers have eaten the minimum amount of times.\n" NC);
		handle_mutex(&sim->print, UNLOCK);
		set_bool(&sim->status, &sim->active, 0);
	}
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
		handle_mutex(&sim->philo[i].mutex, DESTROY);
		i++;
	}
	free(sim->forks);
	if (sim->philo)
		free(sim->philo);
	handle_mutex(&sim->print, DESTROY);
	handle_mutex(&sim->status, DESTROY);
}
