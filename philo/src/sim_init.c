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

static int	create_forks(t_info info, pthread_mutex_t **forks);
static int	create_philo(t_info info, t_sim *sim, t_philo **philo);
static void	start_simulation(t_info info, t_sim *sim, t_philo **philo);
static void	init_last_meal(unsigned int	n_philo, t_philo **philo,
	struct timeval start_time);

/* TODO: handle errors, function return 1 on error, 0 if everything's fine */
void	init_simulation(t_sim *sim)
{
	sim->active = 0;
	pthread_mutex_init(&sim->counter, NULL);
	pthread_mutex_init(&sim->pair, NULL);
	//pthread_mutex_init(&sim->print, NULL);
	create_forks(sim->info, &sim->forks);
	create_philo(sim->info, sim, &sim->philo);
	pthread_create(&sim->main, NULL, &main_routine, sim);
	pthread_join(sim->main, NULL);
}

static int	create_forks(t_info info, pthread_mutex_t **forks)
{
	unsigned int	i;

	i = 0;
	*forks = malloc(info.n_philo * sizeof(pthread_mutex_t));
	if (!*forks)
		return (1);
	while (i < info.n_philo)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
	return (0);
}

static int	create_philo(t_info info, t_sim *sim, t_philo **philo)
{
	unsigned int	i;

	i = 0;
	*philo = malloc(info.n_philo * sizeof(t_philo));
	if (!*philo)
		return (1);
	while (i < info.n_philo)
	{
		(*philo)[i].index = i;
		if (pthread_create(&(*philo)[i].thread, NULL, &philo_routine, sim) != 0)
		{
			write(2, "Failed to create thread\n", 24);
			return (2);
		}
		pthread_detach((*philo)[i].thread);
		i++;
	}
	start_simulation(info, sim, philo);
	return (0);
}

static void	start_simulation(t_info info, t_sim *sim, t_philo **philo)
{
	sim->active = 1;
	memset(&sim->start, 0, sizeof(struct timeval));
	gettimeofday(&sim->start, NULL);
	init_last_meal(info.n_philo, philo, sim->start);
	return ;
}

static void	init_last_meal(unsigned int	n_philo, t_philo **philo,
	struct timeval start_time)
{
	unsigned int	i;

	i = 0;
	while (i < n_philo)
		(*philo)[i].last_meal = start_time;
	return ;
}