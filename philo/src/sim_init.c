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
static void	start_sim(t_sim *sim);

int	init_sim(t_sim *sim)
{
	if (sim->info.n_philo == 1)
	{
		single_philo(sim->info);
		return (0);
	}
	handle_mutex(&sim->status, INIT);
	handle_mutex(&sim->print, INIT);
	set_bool(&sim->status, &sim->active, 0);
	handle_thread(&sim->main, &main_routine, sim, CREATE);
	if (create_forks(sim) == -1)
		return (err_mutexes());
	if (create_philo(sim) == -1)
		return (err_threads());
	start_sim(sim);
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
		if (handle_thread(&sim->philo[i].thread, &philo_routine, &sim->philo[i], CREATE) == -1)
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

static void	start_sim(t_sim *sim)
{
	struct timeval	now;
	unsigned int	i;

	gettimeofday(&now, NULL);
	sim->start = now.tv_sec * 1000 + now.tv_usec / 1000;
	i = 0;
	while (i < sim->info.n_philo)
	{
		handle_thread(&sim->philo[i].thread, &philo_routine, &sim->philo[i], DETACH);
		i++;
	}
	set_bool(&sim->status, &sim->active, 1);
	return ;
}