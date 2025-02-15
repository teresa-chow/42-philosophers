/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:58:01 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/15 15:58:01 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	monitor_sim(t_sim *sim)
{
	while (sim_active(sim))
	{
		starvation_checker(sim);
		if (!sim_active(sim))
			break ;
		philos_full_checker(sim);
		if (!sim_active(sim))
			break ;
		time_checker(sim);
	}
	return ;
}

void	starvation_checker(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	if (sim_active(sim))
	{
		while (i < sim->info.n_philo)
		{
			if (get_bool(&sim->philo[i].state, &sim->philo[i].starved) == 1)
			{
				print_state(&sim->philo[i], STARVED, sim->philo[i].id);
				set_bool(&sim->status, &sim->active, 0);
				return ;
			}
			i++;
		}
	}
	return ;
}

void	philos_full_checker(t_sim *sim)
{
	unsigned int	i;
	bool			full;

	i = 0;
	full = 1;
	if (sim_active(sim))
	{
		while (i < sim->info.n_philo)
		{
			if (!get_bool(&sim->philo[i].counter, &sim->philo[i].full))
				full = 0;
			i++;
		}
		if (full == 1)
		{
			usleep(50);
			print_philos_full(sim);
			set_bool(&sim->status, &sim->active, 0);
		}
	}
	return ;
}

void	print_philos_full(t_sim *sim)
{
	handle_mutex(&sim->print, LOCK);
	printf(GRN "Simulation stopped: "
		"all philosophers have eaten the minimum amount of times.\n" NC);
	handle_mutex(&sim->print, UNLOCK);
}

void	time_checker(t_sim *sim)
{
	unsigned int	i;
	unsigned long	now;
	unsigned long	elapsed;

	if (sim_active(sim))
	{
		i = 0;
		while (i < sim->info.n_philo)
		{
			now = get_time_ms() - sim->start;
			elapsed = now
				- get_ulong(&sim->philo[i].timer, &sim->philo[i].last_meal);
			if (elapsed >= sim->info.time_to_die)
			{
				print_state(&sim->philo[i], STARVED, sim->philo[i].id);
				set_bool(&sim->status, &sim->active, 0);
				return ;
			}
			i++;
		}
	}
	return ;
}
