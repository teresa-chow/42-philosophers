/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	create_philo(t_info info, t_sim *simulation, t_philo *philo);
static void	create_forks(t_info info, pthread_mutex_t *forks);
static void	*start_routine(void *arg);

void	init_simulation(t_info info, t_sim *simulation)
{
	create_forks(info, simulation->forks);
	create_philo(info, simulation, simulation->philo);
}

static void	create_forks(t_info info, pthread_mutex_t *forks) //TODO: check return value / handle errors
{
	unsigned int	i;

	i = 0;
	forks = malloc(info.n_philo * sizeof(pthread_mutex_t));
	while (i < info.n_philo)
	{
		pthread_mutex_init(&forks[i], NULL); //TODO: pthread_mutex_destroy
		i++;
	}
}

static int	create_philo(t_info info, t_sim *simulation, t_philo *philo) //or forks instead of sim (?)
{
	unsigned int	i;

	i = 0;
	while (i < info.n_philo)
	{
		philo = malloc(info.n_philo * sizeof(t_philo)); //TODO: protect if alloc fails
		philo[i].thread_id = malloc(sizeof(pthread_t)); //TODO: protect if alloc fails
		if (pthread_create(philo[i].thread_id, NULL, &start_routine, simulation) != 0) //TO DO: free alloc'ed memory
			write(2, "Failed to create thread\n", 24);
		if (i + 1 == info.n_philo)
			simulation->active = 1;
		i++;
	}
	return (0);
}

/*
arg passed to this function must give access to forks available and times for each action (defined in t_info):
- if time_to_die has passed, change to STARVED and end simulation -- check (should one wait until all threads are created ?)
*/
static void	*start_routine(void *simulation)
{
	static int n_philo = 0;

	//
	//pthread_mutex_lock(&arg);
	printf("Routine\n");
	sleep(5);
	//acquire
	//release
	//pthread_mutex_unlock(&arg);
	return (NULL); //returning from start_routine terminates thread
}

