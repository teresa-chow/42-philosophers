/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	start_sim(t_sim *sim);

void	*main_routine(void *arg)
{
	t_sim			*sim;
	unsigned int	i;

	sim = (t_sim *)arg;
	start_sim(sim);
	i = 0;
	while (sim_active(sim))
	{
		philos_full_checker(sim);
		if (!sim_active(sim))
			break ;
		starvation_checker(sim, i);
		i++;
		if (i == sim->info.n_philo)
			i = 0;
	}
	usleep(500000);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!sim_active(philo->sim))
		usleep(50);
	if (philo->id % 2 != 0)
	{
		act_think(&philo);
		usleep(50);
	}
	while (sim_active(philo->sim))
	{
		act_eat(&philo);
		act_sleep(&philo);
		act_think(&philo);
	}
	return (NULL);
}

static void	start_sim(t_sim *sim)
{
	struct timeval	now;
	unsigned int	i;

	i = 0;
	while (i < sim->info.n_philo)
	{
		handle_thread(&sim->philo[i].thread, &philo_routine,
			&sim->philo[i], DETACH);
		i++;
	}
	gettimeofday(&now, NULL);
	sim->start = now.tv_sec * 1000 + now.tv_usec / 1000;
	set_bool(&sim->status, &sim->active, 1);
	return ;
}
