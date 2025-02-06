/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	create_forks(t_sim *sim);
static int	create_philo(t_sim *sim);
static void	init_philo(t_sim *sim, unsigned int i);

int	init_sim(t_sim *sim)
{
	if (check_edge_cases(sim->info))
		return (0);
	handle_mutex(&sim->status, INIT);
	handle_mutex(&sim->print, INIT);
	set_bool(&sim->status, &sim->active, 0);
	if (create_forks(sim) == -1)
		return (err_mutexes(sim));
	if (create_philo(sim) == -1)
		return (err_threads(sim));
	handle_thread(&sim->main, &main_routine, sim, CREATE);
	handle_thread(&sim->main, NULL, NULL, JOIN);
	return (0);
}

static int	create_forks(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	sim->forks = malloc(sim->info.n_philo * sizeof(t_fork));
	if (!sim->forks)
	{
		write(2, "Memory allocation failed\n", 25);
		return (-1);
	}
	while (i < sim->info.n_philo)
	{
		sim->forks[i].id = i;
		handle_mutex(&sim->forks[i].mutex, INIT);
		i++;
	}
	return (0);
}

static int	create_philo(t_sim *sim)
{
	unsigned int	i;

	sim->philo = malloc(sim->info.n_philo * sizeof(t_philo));
	if (!sim->philo)
		return (-1);
	i = 0;
	while (i < sim->info.n_philo)
	{
		init_philo(sim, i);
		if (handle_thread(&sim->philo[i].thread, &philo_routine,
				&sim->philo[i], CREATE) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static void	init_philo(t_sim *sim, unsigned int i)
{
	sim->philo[i].id = i + 1;
	sim->philo[i].full = 0;
	sim->philo[i].n_meals = 0;
	handle_mutex(&sim->philo[i].mutex, INIT);
	sim->philo[i].state = THINKING;
	assign_forks(sim);
	sim->philo[i].last_meal = 0;
	sim->philo[i].sim = sim;
}
