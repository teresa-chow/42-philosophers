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
static void	assign_forks(t_sim *sim);
static void	start_simulation(t_sim *sim);

int	init_simulation(t_sim *sim)
{
	sim->active = 0;
	handle_thread(&sim->main, &main_routine, sim, CREATE);
	if (create_forks(sim) == -1)
		return (-1);
	if (create_philo(sim) == -1)
		return (err_threads(sim, &sim->philo)); //review : must free forks
	start_simulation(sim);
	handle_thread(&sim->main, NULL, NULL, JOIN);
	return (0);
}

unsigned long	get_time_ms(t_sim *sim)
{
	struct timeval	now;
	unsigned long	timestamp;

	gettimeofday(&now, NULL);
	timestamp = sim->start - (now.tv_sec * 1000 + now.tv_usec / 1000);
	return (timestamp);
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
		sim->philo[i].id = i + 1;
		sim->philo[i].full = 0;
		sim->philo[i].n_meals = 0;
		sim->philo[i].state = THINKING;
		assign_forks(sim);
		sim->philo[i].sim = sim;
		if (handle_thread(&sim->philo[i].thread, &philo_routine, &sim->philo[i], CREATE) == -1)
			return (-1);
		if (handle_thread(&sim->philo[i].thread, NULL, NULL, DETACH) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static void	assign_forks(t_sim *sim)
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

static void	start_simulation(t_sim *sim)
{
	struct timeval	now;

	handle_mutex(&sim->status, INIT);
	set_bool(&sim->status, &sim->active, 1);
	gettimeofday(&now, NULL);
	sim->start = now.tv_sec * 1000 + now.tv_usec / 1000;
	init_last_meal(sim);
	return ;
}

void	init_last_meal(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->info.n_philo)
	{
		sim->philo[i].last_meal = sim->start;
		i++;
	}
	return ;
}