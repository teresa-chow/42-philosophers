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

static int	create_forks(t_info info, t_fork **forks);
static int	create_philo(t_info info, t_sim *sim, t_philo **philo);
static void	start_simulation(t_info info, t_sim *sim, t_philo **philo);
static void	init_last_meal(unsigned int n_philo, t_philo **philo,
				struct timeval start_time);

int	init_simulation(t_sim *sim)
{
	sim->active = 0;
	pthread_create(&sim->main, NULL, &main_routine, sim);
	if (!create_forks(sim->info, &sim->forks))
		return (err_forks());
	if (!create_philo(sim->info, sim, &sim->philo))
		return (err_threads(sim, &sim->philo));
	pthread_join(sim->main, NULL);
	return (0);
}

static int	create_forks(t_info info, t_fork **forks)
{
	unsigned int	i;

	i = 0;
	*forks = malloc(info.n_philo * sizeof(t_fork));
	if (!*forks)
		return (0);
	while (i < info.n_philo)
	{
		pthread_mutex_init(&(*forks)[i].mutex, NULL);
		(*forks)[i].taken = 0;
		i++;
	}
	return (1);
}

static int	create_philo(t_info info, t_sim *sim, t_philo **philo)
{
	unsigned int	i;

	*philo = malloc(info.n_philo * sizeof(t_philo));
	if (!*philo)
		return (0);
	i = 0;
	while (i < info.n_philo)
	{
		(*philo)[i].state = NONE;
		(*philo)[i].index = i;
		(*philo)[i].sim = sim;
		if (pthread_create(&(*philo)[i].thread, NULL,
			&philo_routine, &(*philo)[i]) != 0)
			return (0);
		pthread_detach((*philo)[i].thread);
		i++;
	}
	start_simulation(info, sim, philo);
	return (1);
}

static void	start_simulation(t_info info, t_sim *sim, t_philo **philo)
{
	sim->active = 1;
	memset(&sim->start, 0, sizeof(struct timeval));
	gettimeofday(&sim->start, NULL);
	init_last_meal(info.n_philo, philo, sim->start);
	return ;
}

static void	init_last_meal(unsigned int n_philo, t_philo **philo,
	struct timeval start_time)
{
	unsigned int	i;

	i = 0;
	while (i < n_philo)
	{
		(*philo)[i].last_meal = start_time;
		i++;
	}
	return ;
}
