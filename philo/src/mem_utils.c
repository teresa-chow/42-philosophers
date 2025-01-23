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

void	free_forks_array(t_info info, pthread_mutex_t **forks)
{
	unsigned int	i;

	i = 0;
	while (i < info.n_philo)
	{
		pthread_mutex_destroy(forks[i]);
		i++;
	}
	free(forks);
	return ;
}

void	free_philo_array(t_info info, t_philo **philo)
{
	unsigned int	i;

	i = 0;
	while (i < info.n_philo)
	{
		free(philo[i]->thread);
		free(philo[i]);
		i++;
	}
	free(philo);
	return ;
}