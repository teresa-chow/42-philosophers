/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:44:14 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/05 18:44:14 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	single_philo(t_sim *sim);

int	check_edge_cases(t_sim *sim)
{
	if (sim->info.n_times_to_eat == 0)
	{
		handle_mutex(&sim->print, INIT);
		print_philos_full(sim);
		handle_mutex(&sim->print, DESTROY);
		return (1);
	}
	else if (sim->info.n_philo == 1)
	{
		single_philo(sim);
		return (1);
	}
	return (0);
}

void	assign_forks(t_sim *sim)
{
	unsigned int	i;
	unsigned int	n_philo;

	i = 0;
	n_philo = sim->info.n_philo;
	while (i < n_philo)
	{
		sim->philo[i].fork1 = &sim->forks[(i + 1) % n_philo];
		sim->philo[i].fork2 = &sim->forks[i];
		i++;
	}
	return ;
}

void	monitor_sim(t_sim *sim)
{
	while (sim_active(sim))
	{
		starvation_checker(sim);
		if (!sim_active(sim))
			break ;
		philos_full_checker(sim);
		usleep(500);
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

static void	single_philo(t_sim *sim)
{
	sim->philo = malloc(sizeof(t_philo));
	if (!sim->philo)
		return ;
	sim->philo->sim = sim;
	if (handle_thread(&sim->philo[0].thread, &single_routine,
			&sim->philo[0], CREATE) == -1)
		return ;
	handle_thread(&sim->philo[0].thread, NULL, NULL, JOIN);
	free(sim->philo);
	return ;
}
