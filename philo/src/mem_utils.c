/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:46:38 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 10:46:38 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_forks_array(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->info.n_philo)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		i++;
	}
	free(sim->forks);
	return ;
}

void	free_philo_array(t_philo **philo)
{
	if (philo)
		free(*philo);
	return ;
}

// REVIEW
int	err_threads(t_sim *sim, t_philo **philo)
{
	free_forks_array(sim); //review
	free_philo_array(&(*philo)); //review
	write(2, "Failed to create threads\n", 25);
	return (-1);
}